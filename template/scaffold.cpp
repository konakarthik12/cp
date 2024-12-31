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

template <class Iter>
int idist(Iter a, Iter b) {
  return distance(a, b);
}
