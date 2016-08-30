#include <stdio.h>
#include "common.h"
#include "runtime_callers.h" // for current_runtime_pcs initialization

#pragma once

#define NOINLINE       __attribute__((noinline))

typedef int (*runtime_pcs)(uintptr *, int);
