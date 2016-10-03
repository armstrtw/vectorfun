#include <algorithm>
#include <random>
#include <vector>
#include <vectorfun/single.series.stats.hpp>
#include <vectorfun/cross.series.stats.hpp>
#include <numeric.traits.hpp>
#include <benchmark/benchmark.h>

using namespace vectorfun;

size_t N{100000};

/*
static void BM_class(benchmark::State &state) {
  std::vector<double> x(N);
  std::iota(std::begin(x), std::end(x), 1);
  std::vector<double> x1(N, 1.0);
  double res;
  while (state.KeepRunning()) {
    res = applyStat<double, RNT, Sum>(x.begin(), x.end());
    res = applyStat<double, RNT, Prod>(x1.begin(), x1.end());
    res = applyStat<double, RNT, Mean>(x.begin(), x.end());
  }
}
*/

static void BM_fun(benchmark::State &state) {
  std::vector<double> x(N);
  std::iota(std::begin(x), std::end(x), 1);
  std::vector<double> x1(N, 1.0);
  double res;
  while (state.KeepRunning()) {
    res = Sum<double, RNT>(x.begin(), x.end());
    res = Prod<double, RNT>(x1.begin(), x1.end());
    res = Mean<double, RNT>(x.begin(), x.end());
  }
}

// BENCHMARK(BM_class);
BENCHMARK(BM_fun);

BENCHMARK_MAIN();
