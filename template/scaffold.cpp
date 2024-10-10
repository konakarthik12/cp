#pragma once
#include "entry.h"

#define all(x) std::begin(x), std::end(x)
#define rall(x) rbegin(x), rend(x)

#define cexp constexpr

template <typename T>
cexp auto sz(const T& container) -> int {
  return std::size(container);
}

template <typename T>
constexpr int blen(T x) {
  if (x == 0) return 1;
  return bit_width(make_unsigned_t<T>(x));
}