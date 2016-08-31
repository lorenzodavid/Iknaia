#include "test_common.h"

#include <alloca.h>

#include <gtest/gtest.h>

TEST(TestCommon, basic) {
  for (int i = 0; i < 100; i++) {
    ASSERT_EQ(fetch_compare_traces(), true);
  }
}


bool run_sanity_test() {
  return a();
}

TEST(TestCommon, sanity_test) {
  for (int i = 0; i < 100; i++) {
    ASSERT_EQ(run_sanity_test(), true);
  }
}

bool run_alloca_sanity_test(int i) {
  if ( i % 4 )
    void *p = alloca(500);
  return a();
}

TEST(TestCommon, alloca_sanity_test) {
  for (int i = 0; i < 100; i++) {
    ASSERT_EQ(run_alloca_sanity_test(i), true);
  }
}

int main(int ac, char ** av) {
  printf("Running %s\n", av[0]);
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
