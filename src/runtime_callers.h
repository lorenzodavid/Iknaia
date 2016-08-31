#include "common.h"
#include "hashmap.h"

#include <stdint.h>
#include <stdlib.h>

#pragma once

int runtime_pcs_libunwind(uintptr *pcbufs, int buffers);
int runtime_pcs_libunwind_builtin_cache(uintptr *pcbufs, int buffers);

void flush_libunwind_builtin_cache();

int runtime_pcs_backtrace(uintptr *pcbufs, int buffers);
int runtime_pcs_frameptr(uintptr *pcbufs, int buffers);

// Haven't found a better solution
#ifdef __cplusplus
extern "C" {
#endif
  // Map: { Key: IP,
  //        Value: Delta }
  // IP identifies the entry point of a function `f()'
  // Delta is the difference between the `base pointer' of function
  // `f()' to a generic callee.
  //
  // The assumption is that any caller of `f()' will _likely_ place
  // its `base pointer' at a constant delta in the stack.
  typedef struct map_node {
    uintptr ip;
    int delta;
  } map_node;
#ifdef __cplusplus
}
#endif

class Tracewinder {
 public:
  Tracewinder();
  ~Tracewinder();
  static inline Tracewinder* instance() {
    if (instance_ == NULL)
      instance_ = new Tracewinder();
    return instance_;
  }
  void enable_cache();
  void disable_cache();
  void enable_debug_mode();
  void disable_debug_mode();
  int runtime_pcs_tracewinder(uintptr *pcbufs,
                              int buffers);
 private:
  size_t plum_unwind_stack__(const uintptr pc,
                             const uintptr bp,
                             const uintptr stack_top,
                             const uintptr stack_bottom,
                             uintptr *trace_buffer,
                             const size_t max_depth);
  // Thou shalt have no other tracewinder before me.
  static Tracewinder *instance_;
  // Caching Map {Key: IP, Value: Delta}
  hashmap * stack_unwind_map_;
  // Just for internal usage
  map_node lookup_node_;

  uint64_t activity_counter_;
  uint32_t ip_offset_;
  uint32_t frame_skip_;
  // Caching related stuff
  bool cache_enable_;
  uint64_t cache_hit_cnt_;
  uint64_t cache_miss_cnt_;
  // Debug mode
  bool debug_mode_;
};
