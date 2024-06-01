#pragma once
#include "base.cpp"
template <typename T1, typename T2>
void swapsort(T1& a, T2& b) {
  if (a > b) swap(a, b);
}

template <typename T>
int blen(T x) {
  if (x == 0) return 1;
  return bit_width(static_cast<make_unsigned_t<decltype(x)>>(x));
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

template <typename T, typename F>
T min_false(T l, T h, F comp, T d) {
  T ans = min_false(l, h + 1, comp);
  if (ans == h + 1) return d;
  return ans;
}

template <typename T, typename F>
T max_true(T l, T h, F comp, T d) {
  T ans = max_true(l, h + 1, comp);
  if (ans == h + 1) return d;
  return ans;
}

template <typename T, typename F>
T min_true(T l, T h, F comp, T d) {
  T ans = min_true(l, h + 1, comp);
  if (ans == h + 1) return d;
  return ans;
}

template <typename T, typename F>
T max_false(T l, T h, F comp, T d) {
  T ans = max_false(l, h + 1, comp);
  if (ans == h + 1) return d;
  return ans;
}

str Yes(bool ans) {
  return ans ? "Yes" : "No";
}
str YES(bool ans) {
  return ans ? "YES" : "NO";
}
void exit() {
  exit(0);
}
template <typename T>
cexp auto yes(T&& opt) {
  return optional(opt);
}

cexp auto no() {
  return nullopt;
}
wi invperm(const wi& arr) {
  wi ans(sz(arr));
  for (int i = 1; i <= sz(arr); i++) {
    ans[arr[i]] = i;
  }
  return ans;
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename Con>
void iota(Con& v, const typename Con::value_type start = typename Con::value_type(0)) {
  iota(all(v), start);
}
template <typename Con>
void iota(Con& v, const typename Con::value_type start, const typename Con::value_type end) {
  v.resize(end - start + 1);
  iota(v, start);
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

template <class F>
struct y_comb {
  F f;

  template <class... Args>
  decltype(auto) operator()(Args&&... args) const {
    return f(*this, std::forward<Args>(args)...);
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
