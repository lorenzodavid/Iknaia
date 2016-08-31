#include <stdio.h>
#include "benchmark/bm_common.h"

#include "benchmark/benchmark.h"

static char doc[] =
  "Benchmark tracewinder.\n"
  "The benchmark shows results for uncached libunwind\n"
  "and cached-enabled libunwind.\n"
  "\n"
  "BM_T01      : same stack trace\n"
  "BM_T02      : different stack traces\n"
  "BM_T03      : randomized\n"
  "\n"
  "The test invokes the unwinder function in a loop.\n"
  "The number of loop iterations are follows the test name.\n"
  "\n";

static void BM_T01_cached(benchmark::State& state) { //NOLINT
  set_runtime_pcs(runtime_pcs_libunwind_builtin_cache);
  while (state.KeepRunning()) {
    for (int i = 0; i < ITERATION; i++) {
      l1_1();
    }
  }
  flush_libunwind_builtin_cache();
}

BENCHMARK(BM_T01_cached)->Arg(ITERATION)->Unit(benchmark::kMillisecond);

static void BM_T02_cached(benchmark::State& state) { //NOLINT
  set_runtime_pcs(runtime_pcs_libunwind_builtin_cache);
  while (state.KeepRunning()) {
    faux_unroll<ITERATION>::call([&] {
        l1_1();
      });
  }
  flush_libunwind_builtin_cache();
}

BENCHMARK(BM_T02_cached)->Arg(ITERATION)->Unit(benchmark::kMillisecond);

static void BM_T03_cached(benchmark::State& state) { //NOLINT
  unsigned int seed = time(NULL);
  set_runtime_pcs(runtime_pcs_libunwind_builtin_cache);
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); i++) {
      call_m(rand_r(&seed) % 1);
    }
  }
  flush_libunwind_builtin_cache();
}

BENCHMARK(BM_T03_cached)
->Arg(10*ITERATION)
->Arg(100*ITERATION)
->Arg(1000*ITERATION)
->Arg(10000*ITERATION)
->Unit(benchmark::kMillisecond);

static void BM_T01_uncached(benchmark::State& state) { //NOLINT
  set_runtime_pcs(runtime_pcs_libunwind);
  while (state.KeepRunning()) {
    for (int i = 0; i < ITERATION; i++) {
      l1_1();
    }
  }
}

BENCHMARK(BM_T01_uncached)->Arg(ITERATION)->Unit(benchmark::kMillisecond);

static void BM_T02_uncached(benchmark::State& state) { //NOLINT
  set_runtime_pcs(runtime_pcs_libunwind);
  while (state.KeepRunning()) {
    faux_unroll<ITERATION>::call([&] {
        l1_1();
      });
  }
}

BENCHMARK(BM_T02_uncached)->Arg(ITERATION)->Unit(benchmark::kMillisecond);

static void BM_T03_uncached(benchmark::State& state) { //NOLINT
  unsigned int seed = time(NULL);
  set_runtime_pcs(runtime_pcs_libunwind);
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); i++) {
      call_m(rand_r(&seed) % 1);
    }
  }
}

BENCHMARK(BM_T03_uncached)
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
