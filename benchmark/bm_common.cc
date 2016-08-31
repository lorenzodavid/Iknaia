#include "bm_common.h"

// Global
Tracewinder *tracewinder;
bool use_tracewinder = false;

runtime_pcs current_runtime_pcs = runtime_pcs_libunwind;

void set_runtime_pcs(runtime_pcs new_runtime_pcs) {
  current_runtime_pcs = new_runtime_pcs;
  use_tracewinder = false;
}

void set_runtime_pcs(Tracewinder *p) {
  tracewinder = p;
  use_tracewinder = true;
}

int get_current_runtime_pcs(uintptr *pcbuf, int buffers) {
  if (use_tracewinder) {
    return tracewinder->runtime_pcs_tracewinder(pcbuf, buffers);
  } else {
    return current_runtime_pcs(pcbuf, buffers);
  }
}

// Layer 1
void l1_7() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}

void l1_6() {
  l1_7();
  // avoid tail call optimizations
  asm volatile("mfence" : : : "memory");
}

void l1_5() {
  l1_6();
  // avoid tail call optimizations
  asm volatile("mfence" : : : "memory");
}

void l1_4() {
  l1_5();
  // avoid tail call optimizations
  asm volatile("mfence" : : : "memory");
}

void l1_3() {
  l1_4();
  // avoid tail call optimizations
  asm volatile("mfence" : : : "memory");
}

void l1_2() {
  l1_3();
  // avoid tail call optimizations
  asm volatile("mfence" : : : "memory");
}

void l1_1() {
  l1_2();
  // avoid tail call optimizations
  asm volatile("mfence" : : : "memory");
}


void f1() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f2() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f3() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f4() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f5() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f6() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f7() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f8() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f9() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f10() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f11() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f12() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f13() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f14() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f15() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f16() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f17() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f18() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f19() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f20() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f21() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f22() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f23() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f24() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f25() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f26() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f27() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f28() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f29() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f30() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f31() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f32() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f33() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f34() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f35() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f36() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f37() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f38() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f39() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f40() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f41() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f42() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f43() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f44() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f45() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f46() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f47() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f48() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f49() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f50() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f51() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f52() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f53() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f54() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f55() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f56() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f57() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f58() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f59() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f60() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f61() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f62() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f63() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f64() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f65() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f66() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f67() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f68() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f69() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f70() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f71() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f72() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f73() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f74() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f75() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f76() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f77() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f78() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f79() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f80() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f81() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f82() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f83() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f84() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f85() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f86() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f87() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f88() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f89() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f90() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f91() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f92() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f93() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f94() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f95() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f96() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f97() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f98() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f99() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}
void f100() {
  uintptr pcbuf[100];
  get_current_runtime_pcs(pcbuf, sizeof pcbuf / sizeof pcbuf[0]);
}

typedef void (*f)();

f m[100] = {
  f1, f2, f3, f4, f5,
  f6, f7, f8, f9, f10,
  f11, f12, f13, f14, f15,
  f16, f17, f18, f19, f20,
  f21, f22, f23, f24, f25,
  f26, f27, f28, f29, f30,
  f31, f32, f33, f34, f35,
  f36, f37, f38, f39, f40,
  f41, f42, f43, f44, f45,
  f46, f47, f48, f49, f50,
  f51, f52, f53, f54, f55,
  f56, f57, f58, f59, f60,
  f61, f62, f63, f64, f65,
  f66, f67, f68, f69, f70,
  f71, f72, f73, f74, f75,
  f76, f77, f78, f79, f80,
  f81, f82, f83, f84, f85,
  f86, f87, f88, f89, f90,
  f91, f92, f93, f94, f95,
  f96, f97, f98, f99, f100
};

void call_m(int idx) {
  m[idx]();
}
