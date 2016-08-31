#include "runtime_callers.h"

#include <stdio.h>
#include <stdlib.h>
#include <libunwind.h>

int runtime_pcs_libunwind(uintptr *pcbufs, int buffers) {
  unw_cursor_t cursor;
  unw_context_t uc;
  unw_word_t ip;
  int i = 0;
  int cnt = 0;
  int frame_skip = 1;

  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);
  if (unw_set_caching_policy(unw_local_addr_space, UNW_CACHE_NONE)) {
    fprintf(stderr, "Unable to set libunwind policy.\n");
    exit(-1);
  }
  while (unw_step(&cursor) > 0 && i < buffers) {
    unw_get_reg(&cursor, UNW_REG_IP, &ip);
    if (cnt >= frame_skip)
      pcbufs[i++] = ip;
    cnt++;
  }
  return i;
}

/* libunwind */
int runtime_pcs_libunwind_builtin_cache(uintptr *pcbufs, int buffers) {
  unw_cursor_t cursor;
  unw_context_t uc;
  unw_word_t ip;
  int i = 0;
  int cnt = 0;
  int frame_skip = 1;

  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);
  if (unw_set_caching_policy(unw_local_addr_space, UNW_CACHE_GLOBAL)) {
    fprintf(stderr, "Unable to set libunwind policy.\n");
    exit(-1);
  }
  while (unw_step(&cursor) > 0 && i < buffers) {
    unw_get_reg(&cursor, UNW_REG_IP, &ip);
    if (cnt >= frame_skip)
      pcbufs[i++] = ip;
    cnt++;
  }
  return i;
}

void flush_libunwind_builtin_cache() {
  unw_flush_cache(unw_local_addr_space, 0, 0);
}
