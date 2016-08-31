#include <stdio.h>
#include "common.h"
#include "runtime_callers.h" // for current_runtime_pcs initialization

#pragma once

#define NOINLINE       __attribute__((noinline))

typedef int (*runtime_pcs)(uintptr *, int);

void runtime_error_dump(uintptr pcbuf[100][100], int * pcbuf_n,
			uint32_t *idx);

bool fetch_compare_traces();

// functions for sanity testing
/*
  a --> b --> c --> f --> g(recursive)
   \     \       /
    \-> d---> e -
*/
bool a();
