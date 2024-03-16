#pragma once
#include "base.cpp"
template <typename T1, typename T2>
void swapsort(T1& a, T2& b) {
  if (a > b) swap(a, b);
}

template <typename T>
int blen(T x) {
  return bit_width(static_cast<std::make_unsigned_t<decltype(x)>>(x));
}

template <typename T, typename F>
T min_false(T l, T h, F comp) {
  auto iter = ranges::partition_point(views::iota(l, h + 1), comp);
  return *iter;
}

template <typename T, typename F>
T max_true(T l, T h, F comp) {
  return min_false(l, h, comp) - 1;
}

template <typename T, typename F>
T min_true(T l, T h, F comp) {
  return min_false(l, h, not_fn(comp));
}

template <typename T, typename F>
T max_false(T l, T h, F comp) {
  return max_true(l, h, not_fn(comp));
}

str Yes(bool ans, str yes = "Yes", str no = "No") {
  return ans ? yes : no;
}
str YES(bool ans, str yes = "YES", str no = "NO") {
  return ans ? yes : no;
}
void exit() {
  exit(0);
}
template <typename T>
constexpr auto yes(T&& opt) {
  return optional(opt);
}

constexpr auto no() {
  return std::nullopt;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename Con>
void iota(Con& v, const typename Con::value_type start = Con::value_type(0)) {
  iota(all(v), start);
}
vpii dirs4 = vpii{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

template <size_t N>
class bits : public bitset<N> {
 public:
  using bitset<N>::bitset;

  explicit operator int() const {
    return (int) this->to_ullong();
  }
};

#ifndef LOCAL
#define assume(cond)                      \
  do {                                    \
    if (!(cond)) __builtin_unreachable(); \
  } while (0)
#else
#define sassert(cond) assert(cond)
#endif
