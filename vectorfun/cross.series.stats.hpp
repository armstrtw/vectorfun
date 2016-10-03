#pragma once

#include <iterator>

namespace vectorfun {

template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Cov(T xbeg, T xend, T ybeg, T yend) {
  RT ans{0}, xmean{Mean<RT, NUMERIC_TRAITS>(xbeg, xend)},
      ymean{Mean<RT, NUMERIC_TRAITS>(ybeg, yend)};
  typename std::iterator_traits<T>::difference_type len{
      std::distance(xbeg, xend)};

  if (std::distance(xbeg, xend) != std::distance(ybeg, yend) ||
      NUMERIC_TRAITS<RT>::ISNA(xmean) || NUMERIC_TRAITS<RT>::ISNA(ymean)) {
    return NUMERIC_TRAITS<RT>::NA();
  }
  for (; xbeg != xend; ++xbeg, ++ybeg) {
    ans += (*xbeg - xmean) * (*ybeg - ymean);
  }
  return ans / static_cast<RT>(len - 1);
}

template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Cor(T xbeg, T xend, T ybeg, T yend) {
  RT xsd{Stdev<RT, NUMERIC_TRAITS>(xbeg, xend)},
      ysd{Stdev<RT, NUMERIC_TRAITS>(ybeg, yend)},
      xycov{Cov<RT, NUMERIC_TRAITS>(xbeg, xend, ybeg, yend)};
  if (NUMERIC_TRAITS<RT>::ISNA(xycov)) {
    return NUMERIC_TRAITS<RT>::NA();
  }
  return xycov / (xsd * ysd);
}

} // namespace vectorfun
