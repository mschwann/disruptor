#include "1p1c.h"
#include "mpmc.h"

// Register the function as a benchmark
BENCHMARK(BM_mpmc_pushpop)->ThreadRange(1, 32);
BENCHMARK(BM_1pc1c_pushpop);

BENCHMARK_MAIN();