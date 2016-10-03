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
    res = applyStat<double, r_numeric_traits, Sum>(x.begin(), x.end());
    res = applyStat<double, r_numeric_traits, Prod>(x1.begin(), x1.end());
    res = applyStat<double, r_numeric_traits, Mean>(x.begin(), x.end());
  }
}
*/

static void BM_fun(benchmark::State &state) {
  std::vector<double> x(N);
  std::iota(std::begin(x), std::end(x), 1);
  std::vector<double> x1(N, 1.0);
  double res;
  while (state.KeepRunning()) {
    res = Sum<double, r_numeric_traits>(x.begin(), x.end());
    res = Prod<double, r_numeric_traits>(x1.begin(), x1.end());
    res = Mean<double, r_numeric_traits>(x.begin(), x.end());
  }
}

// BENCHMARK(BM_class);
BENCHMARK(BM_fun);

BENCHMARK_MAIN();
