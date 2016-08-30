#include <stdio.h>
#include "benchmark/bm_common.h"

#include "benchmark/benchmark.h"

static char doc[] =
  "Benchmark backtrace unwinder.\n"
  "\n"
  "BM_T01      : same stack trace\n"
  "BM_T02      : different stack traces\n"
  "BM_T03      : randomized\n"
  "\n"
  "The test invokes the unwinder function in a loop.\n"
  "The number of loop iterations are follows the test name.\n"
  "\n";

static void BM_T01(benchmark::State& state) { //NOLINT
  set_runtime_pcs(runtime_pcs_backtrace);
  while (state.KeepRunning()) {
    for (int i = 0; i < ITERATION; i++) {
      l1_1();
    }
  }
}

BENCHMARK(BM_T01)->Arg(ITERATION)->Unit(benchmark::kMillisecond);

static void BM_T02(benchmark::State& state) { //NOLINT
  set_runtime_pcs(runtime_pcs_backtrace);
  while (state.KeepRunning()) {
    faux_unroll<ITERATION>::call([&] {
        l1_1();
      });
  }
}

BENCHMARK(BM_T02)->Arg(ITERATION)->Unit(benchmark::kMillisecond);

static void BM_T03(benchmark::State& state) { //NOLINT
  unsigned int seed = time(NULL);
  set_runtime_pcs(runtime_pcs_backtrace);
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); i++) {
      call_m(rand_r(&seed) % 1);
    }
  }
}

BENCHMARK(BM_T03)
->Arg(10*ITERATION)
->Arg(100*ITERATION)
->Arg(1000*ITERATION)
->Arg(10000*ITERATION)
->Unit(benchmark::kMillisecond);

int main(int argc, char **argv) {
  printf("Running %s\n", argv[0]);

  printf("%s", doc);

  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
  return 0;
}
