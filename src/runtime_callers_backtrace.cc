#include "runtime_callers.h"

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

int runtime_pcs_backtrace(uintptr *pcbufs,  int buffers) {
  return backtrace((void **)pcbufs, buffers);
}
