#include <stdio.h>
#include "common.h"
#include "runtime_callers.h" // for current_runtime_pcs initialization

#pragma once

#define NOINLINE       __attribute__((noinline))

typedef int (*runtime_pcs)(uintptr *, int);

#define ITERATION 800

void set_runtime_pcs(runtime_pcs new_runtime_pcs);
void set_runtime_pcs(Tracewinder *p);

void l1_1();
void call_m(int idx);

template <unsigned N> struct faux_unroll {
  template <typename F> static void call(F const& f) {
    f();
    faux_unroll<N-1>::call(f);
  }
};

template <> struct faux_unroll<0u> {
  template <typename F> static void call(F const& f) {
    f();
  }
};
