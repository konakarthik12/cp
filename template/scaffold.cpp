#pragma once
#include "entry.h"

#define all(x) std::begin(x), std::end(x)
#define rall(x) rbegin(x), rend(x)

#define cexp constexpr

template <typename T>
cexp auto sz(const T& container) -> int {
  return std::size(container);
}

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

// Helper for custom is_integral_v that can be specialized for Bool
template <typename T>
struct is_integral_helper : std::is_integral<T> {};

// Custom is_integral_v that uses the helper (can be specialized later for Bool)
template <typename T>
inline constexpr bool is_integral_v = is_integral_helper<std::remove_cv_t<std::remove_reference_t<T>>>::value;
