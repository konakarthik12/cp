#pragma once
#include "entry.h"
#define all(x) std::begin(x), std::end(x)
#define rall(x) rbegin(x), rend(x)

#define cexp constexpr

constexpr int blen(unsigned long long x) {
  if (x == 0) return 1;
  return bit_width(x);
}
template <const unsigned long N>
constexpr int blen(std::bitset<N> x) {
  if (x == 0) return 1;
  return bit_width(x);
}

template <class Iter>
int idist(Iter a, Iter b) {
  return distance(a, b);
}

template <typename T>
struct is_integral_helper : std::is_integral<T> {};

template <typename T>
inline constexpr bool is_integral_v = is_integral_helper<std::remove_cv_t<std::remove_reference_t<T>>>::value;

template <typename T>
struct sum_type {
  using type = T;
};

template <>
struct sum_type<int> {
  using type = long long;
};

template <>
struct sum_type<bool> {
  using type = int;
};

template <typename T>
using sum_v = typename sum_type<T>::type;
