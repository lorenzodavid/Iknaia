#include "test_common.h"

#include <gtest/gtest.h>

void runtime_error_dump(uintptr pcbuf[100][100], int * pcbuf_n,
                         uint32_t *idx) {
  for (uint32_t i = 0; i < 2; i++) {
    fprintf(stdout, "pcbuf with idx %u has %d reported pcs\n", idx[i], pcbuf_n[idx[i]]);
    for (uint32_t j = 0; j < (uint32_t)pcbuf_n[idx[i]]; j++) {
      fprintf(stdout, "pc %lx\n", pcbuf[idx[i]][j]);
    }
  }
}

int test_runtime_pcs() {
  Tracewinder *p;
  p = Tracewinder::instance();
  p->enable_cache();
  p->enable_debug_mode();

  uint32_t i, j, k;
  runtime_pcs r[] = {
    runtime_pcs_libunwind,
    runtime_pcs_libunwind_builtin_cache,
    // runtime_pcs_backtrace
    // runtime_pcs_frameptr
  };
  const uint32_t N = (sizeof r / sizeof r[0]) + 1;
  uintptr pcbuf[N][100];
  int pcbuf_n[N];

  // Test all runtime_pcs functions
  for (i = 0; i < N - 1; i++) {
    pcbuf_n[i] = r[i](pcbuf[i], sizeof pcbuf[i] / sizeof pcbuf[i][0]);
  }
  // Call pcs_tracewinder
  pcbuf_n[i] = p->runtime_pcs_tracewinder(pcbuf[i],
                                         sizeof pcbuf[i] / sizeof pcbuf[i][0]);

  // Compare results
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      // Get only the upper triangular part of the matrix
      if (i > j) {
        // reported the same number of pcs
        if (pcbuf_n[i] == pcbuf_n[j]) {
          for (k = 0; k < (uint32_t)pcbuf_n[i]; k++) {
            if (pcbuf[i][k] != pcbuf[j][k]) {
              fprintf(stderr, "Error: pc mismatch between runtime_pcs function.\n");
              fprintf(stderr, "       runtime_pcs func %d reported %lx.\n", i, pcbuf[i][k]);
              fprintf(stderr, "       runtime_pcs func %d reported %lx.\n", j, pcbuf[j][k]);
              uint32_t idx[2] = {i, j};
              runtime_error_dump(pcbuf, pcbuf_n, idx);
              return -1;
            }
          }
        } else {
          fprintf(stderr, "Error: mismatch between reported number of pcs.\n");
          fprintf(stderr, "       runtime_pcs func %d reported %d.\n", i, pcbuf_n[i]);
          fprintf(stderr, "       runtime_pcs func %d reported %d.\n", j, pcbuf_n[j]);
          uint32_t idx[2] = {i, j};
          runtime_error_dump(pcbuf, pcbuf_n, idx);
          return -1;
        }
      }
    }
  }
  return 0;
}

TEST(TestCommon, basic) {
  for (int i = 0; i < 100; i++) {
    ASSERT_EQ(test_runtime_pcs(), 0);
  }
}

int main(int ac, char ** av) {
  printf("Running %s\n", av[0]);
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
