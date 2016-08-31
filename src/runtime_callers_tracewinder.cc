#include "runtime_callers.h"

#include <stdio.h>
#include <stdlib.h>
#include <libunwind.h>

void  map_node_free(void *node) {
  free(node);
}

int map_node_cmp(void *a, void *b) {
  // printf("Comparing 0x%lx with 0x%lx\n",
  //     ((map_node *)a)->ip,
  //     ((map_node *)b)->ip);
  return ((map_node *)a)->ip - ((map_node *)b)->ip;
}

Tracewinder* Tracewinder::instance_ = NULL;

Tracewinder::Tracewinder()
  : activity_counter_(0),
    ip_offset_(0),
    frame_skip_(2),
    cache_hit_cnt_(0),
    cache_miss_cnt_(0),
    debug_mode_(false) {

  // enable libunwind builtin cache
  if (unw_set_caching_policy(unw_local_addr_space, UNW_CACHE_NONE)) {
    fprintf(stderr, "Unable to set libunwind policy.\n");
    exit(-1);
  }
  // enable tracewinder cache as well
  enable_cache();
  // initialize the cache map
  stack_unwind_map_ = hashmap_init(map_node_cmp, map_node_free);
}

Tracewinder::~Tracewinder() { }

void Tracewinder::enable_cache() {
  cache_enable_ = true;
}
void Tracewinder::disable_cache() {
  cache_enable_ = false;
}

void Tracewinder::enable_debug_mode() {
  debug_mode_ = true;
}
void Tracewinder::disable_debug_mode() {
  debug_mode_ = false;
}

size_t Tracewinder::plum_unwind_stack__(const uintptr ip, const uintptr sp,
                                       const uintptr stack_top, const uintptr stack_bottom,
                                       uintptr *trace_buffer, const size_t max_depth) {

  struct map_node * map_node;
  hashmap_node * hashmap_node;

  uint32_t cnt = 0;
  /* Lookup in the Cache */
  if (cache_enable_) {
      // First check in local cache to see if the stack can be
      // unwound. this will abort Even if one layer fails.
      uintptr cur_ip = ((uintptr)ip + ip_offset_);
      uintptr cur_sp = (uintptr)sp;
      bool found = false;
      while (true) {
        lookup_node_.ip = cur_ip;
        hashmap_node = hashmap_find(stack_unwind_map_,
                                    get_hash_pointer((const void *)cur_ip, 0),
                                    &lookup_node_);
        if (hashmap_node == NULL) {
          break;
        } else {
          // lookup succeded, we already recorded this IP
          map_node = (struct map_node *)hashmap_node_get_data(hashmap_node);

          if (cnt >= frame_skip_) {
            trace_buffer[cnt - frame_skip_] = (uint64_t)cur_ip;
          }
          ++cnt;

          // check for terminating call-stack terminator (delta == 0)
          if (map_node->delta == 0) {
            found = true;
            break;
          }
          // Here we should do more checking.
          // What if we got a wrong delta?
          // ip_ptr would point somewhere in the stack. Doing so may
          // crash the program.
          uint64_t* ip_ptr = (uint64_t *)(cur_sp + map_node->delta - 8);
          if (ip_ptr == 0) {
            found = true;
            break;
          }
#ifdef USE_FIBER
          cur_ip = (uintptr)(*ip_ptr - 1);
#else
          cur_ip = (uintptr)*ip_ptr;
#endif
          cur_sp = cur_sp + map_node->delta;
        }
      }
      if (found) {
        cache_hit_cnt_++;
        return (cnt - frame_skip_);
      }
  }

  /* Cache Miss
   * Let's unwind using DWARF symbols
   */
  unw_cursor_t cursor;
  unw_context_t uc;
  unw_word_t unwind_ip, unwind_sp;
  unw_word_t prev_sp = 0, prev_ip;
  int delta = 0;

  cnt = 0;
  cache_miss_cnt_++;
  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);

  while (unw_step(&cursor) > 0) {
    // Get IP and SP of the given call stack
    unw_get_reg(&cursor, UNW_REG_IP, &unwind_ip);
    unw_get_reg(&cursor, UNW_REG_SP, &unwind_sp);

    // Compute the IP offset if not already done
    // The IP offset should always be constant
#ifdef USE_FIBER
    if (!ip_offset_) {
      ip_offset_ = (uint32_t)unwind_ip - 1 - (uint32_t)ip;
    } else if (!cnt  && (uint32_t)ip_offset_ != ((uint32_t)unwind_ip - 1 - (uint32_t)ip)) {
      fprintf(stderr, "ERROR - Detected a change in ip offset %d %ld\n",
              ip_offset_, ((uint32_t)unwind_ip - (uint32_t)ip));
      ip_offset_ = (uint32_t)unwind_ip - 1 - (uint32_t)ip;
    }
#else
    if (!ip_offset_) {
      ip_offset_ = (uint32_t)unwind_ip - (uint32_t)ip;
    } else if (!cnt  && (uint32_t)ip_offset_ != ((uint32_t)unwind_ip - (uint32_t)ip)) {
      fprintf(stderr, "ERROR - Detected a change in ip offset %d %u\n",
              ip_offset_, ((uint32_t)unwind_ip - (uint32_t)ip));
      ip_offset_ = (uint32_t)unwind_ip - (uint32_t)ip;
    }
#endif

#ifdef USE_FIBER
    // adjust ip for signal code.
    int ip_before_insn = 0;
    ip_before_insn = unw_is_signal_frame(&cursor);
    if (!ip_before_insn)
      --unwind_ip;
#endif

    // Cache it
    // Skip the first iteration, as we cache f<n> at the f<n-1>
    // iteration
    if (cache_enable_ && prev_sp) {
      delta = unwind_sp - prev_sp;

      // Let's lookup in the map
      lookup_node_.ip = prev_ip;
      hashmap_node = hashmap_find(stack_unwind_map_,
                                  get_hash_pointer((const void *)prev_ip, 0),
                                  &lookup_node_);
      if (hashmap_node == NULL) {
        // lookup failed, let's insert the new record in the map
        map_node = (struct map_node *)malloc(sizeof(struct map_node));
        map_node->ip = prev_ip;
        map_node->delta = delta;
        hashmap_node = hashmap_node_init(map_node);
        hashmap_insert(stack_unwind_map_,
                       hashmap_node,
                       get_hash_pointer((const void *)prev_ip, 0));
      } else {
        // lookup succeded, we already recorded this IP
        map_node = (struct map_node *)hashmap_node_get_data(hashmap_node);
        if ((uint32_t)map_node->delta != (uint32_t)delta) {
          if (map_node->delta) {
            fprintf(stderr, "Delta change mismatch {ip=%lx : delta=%d}.\n"
                    "New recorded delta = %d\n",
                    prev_ip, map_node->delta, delta);
          }
          // delta was 0, update it with the new value
          map_node->delta = delta;
        }
      }
    }


    if (cnt >= frame_skip_)
      trace_buffer[cnt - frame_skip_] = (uint64_t) unwind_ip;
    cnt++;

    if (cnt >= (max_depth + frame_skip_))
      break;

    // Update IP and SP
    prev_ip = unwind_ip;
    prev_sp = unwind_sp;
  }

  // The delta for the last entry of the stack chain is arbitrary set to 0
  if (cache_enable_) {
    lookup_node_.ip = prev_ip;
    hashmap_node = hashmap_find(stack_unwind_map_,
                                get_hash_pointer((const void *)prev_ip, 0),
                                &lookup_node_);
    if (hashmap_node == NULL) {
      map_node = (struct map_node *)malloc(sizeof(struct map_node));
      map_node->ip = prev_ip;
      map_node->delta = 0;
      hashmap_node = hashmap_node_init(map_node);
      hashmap_insert(stack_unwind_map_,
                     hashmap_node,
                     get_hash_pointer((const void *)prev_ip, 0));
    } else {
      map_node = (struct map_node *)hashmap_node_get_data(hashmap_node);
      map_node->delta = 0;
    }
  }

  /*
   * WARNING: *debug_mode*
   * In debug_mode, we will add this extra check.  We will print out
   * if the caching routine produces a different result than the
   * DWARF-unwinder.
   * In case you use debug_mode, you will get worst performance than
   * with a DWARF-unwinder only solution.
   */

  // ...

  return (cnt - frame_skip_);
}

int Tracewinder::runtime_pcs_tracewinder(uintptr *pcbufs, int buffers) {
  register void* sp asm("sp");
 selflabel:
  return plum_unwind_stack__((uintptr)&&selflabel,
                             (uintptr)sp,
                             0xffffffffffff,  // stack top (highest address)
                             0x0, // stack bottom (lowest address)
                             pcbufs, buffers);
}
