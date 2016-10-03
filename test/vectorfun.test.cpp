#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <random>
#include <vector>
#include <catch.hpp>
#include <vectorfun/single.series.stats.hpp>
#include <vectorfun/cross.series.stats.hpp>
#include <numeric.traits.hpp>

using namespace vectorfun;

TEST_CASE("single series summary stats.") {

  std::vector<double> x{1, 2, 3, 4, 5};
  std::vector<double> x_with_na{1, 2, 3, 4, 5, r_numeric_traits<double>::NA()};
  std::vector<double> x_with_neg{1, 2, -3, 4, 5};
  std::vector<double> x1s(10, 1.);
  std::vector<double> xneg1s(10, -1.);
  std::vector<double> x0s(10, 0.);
  std::vector<double> x100(10, 100.);
  std::vector<double> x1000(1000);
  std::iota(x1000.begin(), x1000.end(), 1);
  std::vector<double> x1neg1(100);
  std::generate(x1neg1.begin(), x1neg1.end(), [] {
    static int n(0);
    return ++n % 2 == 0 ? -1. : 1.;
  });

  SECTION("sum") {
    REQUIRE((Sum<double, r_numeric_traits>(x.begin(), x.end())) ==
            Approx(15.0));
    REQUIRE((r_numeric_traits<double>::ISNA(
        Sum<double, r_numeric_traits>(x_with_na.begin(), x_with_na.end()))));
  }

  SECTION("prod") {
    REQUIRE((Prod<double, r_numeric_traits>(x.begin(), x.end())) ==
            Approx(std::accumulate(x.begin(), x.end(), 1,
                                   std::multiplies<double>())));
    REQUIRE((r_numeric_traits<double>::ISNA(
        Prod<double, r_numeric_traits>(x_with_na.begin(), x_with_na.end()))));
  }

  SECTION("mean") {
    REQUIRE((Mean<double, r_numeric_traits>(x100.begin(), x100.end())) ==
            Approx(100.0));
    REQUIRE((r_numeric_traits<double>::ISNA(
        Mean<double, r_numeric_traits>(x_with_na.begin(), x_with_na.end()))));
  }

  SECTION("stdev") {
    REQUIRE((Stdev<double, r_numeric_traits>(x100.begin(), x100.end())) ==
            Approx(0.0));
    REQUIRE((Stdev<double, r_numeric_traits>(x1000.begin(), x1000.end())) ==
            Approx(288.8194));
    REQUIRE((r_numeric_traits<double>::ISNA(
        Stdev<double, r_numeric_traits>(x_with_na.begin(), x_with_na.end()))));
  }

  SECTION("open/close") {
    REQUIRE((OpenValue(x.begin(), x.end())) == *x.begin());
    REQUIRE((CloseValue(x.begin(), x.end())) == *x.rbegin());
  }

  SECTION("min/max") {
    REQUIRE((Max<r_numeric_traits>(x.begin(), x.end())) == Approx(5.0));
    REQUIRE((r_numeric_traits<double>::ISNA(
        Max<r_numeric_traits>(x_with_na.begin(), x_with_na.end()))));

    REQUIRE((Min<r_numeric_traits>(x.begin(), x.end())) == Approx(1.0));
    REQUIRE((Min<r_numeric_traits>(x_with_neg.begin(), x_with_neg.end())) ==
            Approx(-3.0));
    REQUIRE((r_numeric_traits<double>::ISNA(
        Min<r_numeric_traits>(x_with_na.begin(), x_with_na.end()))));
  }

  SECTION("rsi") {
    REQUIRE((Rsi<double, r_numeric_traits>(x1s.begin(), x1s.end())) ==
            Approx(100.0));
    REQUIRE((Rsi<double, r_numeric_traits>(xneg1s.begin(), xneg1s.end())) ==
            Approx(0.0));
    REQUIRE((r_numeric_traits<double>::ISNA(
        Rsi<double, r_numeric_traits>(x0s.begin(), x0s.end()))));

    REQUIRE((Rsi<double, r_numeric_traits>(x1neg1.begin(), x1neg1.end())) ==
            Approx(50.0));
  }
}

TEST_CASE("cross series summary stats.") {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  size_t N{1000};
  std::vector<double> x(N), y(N);
  for (size_t i = 0; i < x.size(); ++i) {
    x[i] = dis(gen);
    y[i] = dis(gen);
  }

  // std::generate(x.begin(), x.end(), std::rand);
  // std::generate(y.begin(), y.end(), std::rand);

  SECTION("cov") {
    std::cout << Cov<double, r_numeric_traits>(x.begin(), x.end(), y.begin(),
                                               y.end())
              << std::endl;
  }
}
