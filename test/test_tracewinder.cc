#include <stdio.h>
#include <stdlib.h>

#include "runtime_callers.h"

#include <gtest/gtest.h>

void basic_test() {
  // Get the tracewinder
  Tracewinder *p;
  p = Tracewinder::instance();
  // Enable cache
  p->enable_cache();
  p->enable_debug_mode();

  uintptr pcbuf1[100];
  uintptr pcbuf2[100];
  int n1, n2;

  n1 = p->runtime_pcs_tracewinder(pcbuf1, sizeof pcbuf1 / sizeof pcbuf1[0]);
  n2 = runtime_pcs_libunwind(pcbuf2, sizeof pcbuf2 / sizeof pcbuf2[0]);

  ASSERT_EQ(n1, n2);

  for (int i = 0; i < n1; i++) {
    ASSERT_EQ(pcbuf1[i], pcbuf2[i]);
  }
}

TEST(TestTracewinder, basic) {
  for (int i = 0; i < 100; i++) {
    basic_test();
  }
}

int main(int ac, char ** av) {
  printf("Running %s\n", av[0]);
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
