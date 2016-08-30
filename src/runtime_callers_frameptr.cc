#include "runtime_callers.h"

#include <stdio.h>
#include <stdlib.h>

int
unwind_is_valid_frame__(const uintptr frame, const uintptr stack_top, const uintptr stack_bottom) {
  return (frame > stack_bottom) && (frame < stack_top - 2 * sizeof (uintptr));
}

int
unwind_is_aligned__(const uintptr ptr, const uintptr alignment) {
#ifdef USE_FIBER
  return (ptr & (alignment - 1)) == 0;
#else
  return (ptr & (alignment)) == 0;
#endif
}

size_t
fast_unwind_stack__(int frame_skip,
                    const uintptr pc, const uintptr bp,
                    const uintptr stack_top, const uintptr stack_bottom,
                    uintptr *trace_buffer, const size_t max_depth) {
  const uintptr kPageSize = 0x1000;

  // skip the first PC for compatibility with the visualization used by the fiber subsystem
  size_t size = 0;
  int cnt = 0;

  if (stack_top < 4096)
    // Sanity check for stack top.
    return size;

  // interpret bp as an address, so we can access the value at its
  // location (the BP of the caller, saved by the prologue of the
  // callee) and the value at bp + 8, that is the pc the callee will return to
  // (i.e. the next instruction to be executed in the caller function)
  uintptr *frame = (uintptr *)bp;
  // Lowest possible address that makes sense as the next frame pointer.
  // Goes up as we walk the stack.
  uintptr bottom = stack_bottom;
  // Avoid infinite loop when frame == frame[0] by using frame > prev_frame.
  while (unwind_is_valid_frame__((uintptr)frame, stack_top, bottom) &&
         unwind_is_aligned__((uintptr)frame, sizeof(*frame)) &&
         size < max_depth) {
    uintptr pc1 = frame[1];
    // Let's assume that any pointer in the 0th page (i.e. <0x1000 on i386 and
    // x86_64) is invalid and stop unwinding here.
    if (pc1 < kPageSize)
      break;

    // store the PC we have just fetched; the '-1' decrement is needed
    // for compatibility with the fiber library, that expect a ptr to last
    // insn executed in the caller, not the return address
    if (cnt >= frame_skip)
#ifdef USE_FIBER
      trace_buffer[size++] = pc1 - 1;
#else
      trace_buffer[size++] = pc1;
#endif
    cnt++;

    bottom = (uintptr) frame;
    frame = (uintptr *) frame[0];
  }

  return size;
}

size_t runtime_callers_frameptr(size_t skip, uintptr *pcbuf, size_t m) {
  return fast_unwind_stack__(skip,
                             (uintptr) __builtin_return_address(1), // pc
                             (uintptr) __builtin_frame_address(1), // bp
                             0xffffffffffff,  // stack top (highest address)
                             0x0, // stack bottom (lowest address)
                             pcbuf, m);
}


int runtime_pcs_frameptr(uintptr *pcbufs, int buffers) {
  return runtime_callers_frameptr (1, pcbufs, buffers);
}
