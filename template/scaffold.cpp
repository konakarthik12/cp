#pragma once
#include "entry.h"

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define cexp constexpr
template <typename T>
cexp auto sz(const T& container) -> int {
  return std::size(container);
}
