#pragma once
#include <iterator>

namespace vectorfun {

template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Sum(T beg, T end) {
  typedef typename std::iterator_traits<T>::value_type VT;
  RT ans{0};
  for (; beg != end; ++beg) {
    if (NUMERIC_TRAITS<VT>::ISNA(*beg)) {
      return NUMERIC_TRAITS<RT>::NA();
    }
    ans += *beg;
  }
  return ans;
}

template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Prod(T beg, T end) {
  typedef typename std::iterator_traits<T>::value_type VT;
  RT ans{1};
  for (; beg != end; ++beg) {
    if (NUMERIC_TRAITS<VT>::ISNA(*beg)) {
      return NUMERIC_TRAITS<RT>::NA();
    }
    ans *= *beg;
  }
  return ans;
}

template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Mean(T beg, T end) {
  return Sum<RT, NUMERIC_TRAITS>(beg, end) /
         static_cast<RT>(std::distance(beg, end));
}

template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Stdev(T beg, T end) {
  typedef typename std::iterator_traits<T>::value_type VT;
  RT ans{0}, xmean{Mean<RT, NUMERIC_TRAITS>(beg, end)};
  const typename std::iterator_traits<T>::difference_type len{
      std::distance(beg, end)};

  if (NUMERIC_TRAITS<VT>::ISNA(xmean)) {
    return NUMERIC_TRAITS<RT>::NA();
  }
  for (; beg != end; ++beg) {
    if (NUMERIC_TRAITS<VT>::ISNA(*beg)) {
      return NUMERIC_TRAITS<RT>::NA();
    }
    RT diff{*beg - xmean};
    ans += diff * diff;
  }
  return std::sqrt(ans / (static_cast<RT>(len) - 1.0));
};

// reduced form (return type is always std::iterator_traits<T>::value_type
template <template <typename> class NUMERIC_TRAITS, typename T>
typename std::iterator_traits<T>::value_type Min(T beg, T end) {
  typedef typename std::iterator_traits<T>::value_type VT;
  VT ans{*beg};
  for (; beg != end; ++beg) {
    if (NUMERIC_TRAITS<VT>::ISNA(*beg)) {
      return NUMERIC_TRAITS<VT>::NA();
    }
    ans = *beg < ans ? *beg : ans;
  }
  return ans;
}

template <template <typename> class NUMERIC_TRAITS, typename T>
typename std::iterator_traits<T>::value_type Max(T beg, T end) {
  typedef typename std::iterator_traits<T>::value_type VT;
  VT ans{*beg};
  for (; beg != end; ++beg) {
    if (NUMERIC_TRAITS<VT>::ISNA(*beg)) {
      return NUMERIC_TRAITS<VT>::NA();
    }
    ans = *beg > ans ? *beg : ans;
  }
  return ans;
}

// these do not need to know about numeric traits
template <typename T>
typename std::iterator_traits<T>::value_type OpenValue(T beg, T end) {
  return *beg;
}
template <typename T>
typename std::iterator_traits<T>::value_type CloseValue(T beg, T end) {
  return *--end;
}

// ranks from 1 to N
template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Rank(T beg, T end) {
  typedef typename std::iterator_traits<T>::value_type VT;
  RT ans{1};
  VT value{*--end};
  for (; beg != end; ++beg) {
    if (NUMERIC_TRAITS<VT>::ISNA(*beg)) {
      return NUMERIC_TRAITS<RT>::NA();
    }
    ans += value > *beg ? 1 : 0;
  }
  return ans;
}

template <typename RT, template <typename> class NUMERIC_TRAITS, typename T>
RT Rsi(T beg, T end) {
  typedef typename std::iterator_traits<T>::value_type VT;
  size_t pos_count{0}, neg_count{0};
  RT pos_sum{0}, neg_sum{0};
  for (; beg != end; ++beg) {
    if (NUMERIC_TRAITS<VT>::ISNA(*beg)) {
      return NUMERIC_TRAITS<RT>::NA();
    } else {
      RT x = *beg;
      if (x > 0) {
        ++pos_count;
        pos_sum += x;
      } else if (x < 0) {
        ++neg_count;
        neg_sum += -x;
      }
    }
  }

  if (pos_sum == 0 && neg_sum == 0) {
    return NUMERIC_TRAITS<RT>::NA();
  } else if (neg_sum == 0) {
    return 100.0;
  } else if (pos_sum == 0) {
    return 0.0;
  }

  RT avg_gain{pos_sum / static_cast<RT>(pos_count)},
      avg_loss{neg_sum / static_cast<RT>(neg_count)}, rs{avg_gain / avg_loss};
  return 100.0 - 100.0 / (1.0 + rs);
}

} // namespace vectorfun
