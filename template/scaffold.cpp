#pragma once
#include "entry.cpp"


#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define cexp constexpr
template <typename T>
cexp auto sz(const T& container) -> decltype(std::size(container)) {
  return std::size(container);
}