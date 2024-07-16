#pragma once
#include "base.cpp"
#include "concepts.cpp"
template <typename T1, typename T2>
void swapsort(T1& a, T2& b) {
  if (a > b) swap(a, b);
}

template <typename T>
constexpr int blen(T x) {
  if (x == 0) return 1;
  return bit_width(static_cast<make_unsigned_t<decltype(x)>>(x));
}

template <typename T, typename V>
  requires Numeric<V>
T mode(map<T, V> items) {
  T mode = items.begin()->first;
  V max_count = items.begin()->second;
  for (auto [item, count]: items) {
    if (count > max_count) {
      max_count = count;
      mode = item;
    }
  }
  return mode;
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
auto nopt = nullopt;
cexp auto no() {
  return nopt;
}
wi invperm(const wi& arr) {
  wi ans(sz(arr));
  for (int i = 1; i <= sz(arr); i++) {
    ans[arr[i]] = i;
  }
  return ans;
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vpii dirs4 = vpii{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

template <class F>
struct y_comb {
  F f;

  template <class... Args>
  decltype(auto) operator()(Args&&... args) const {
    return f(*this, std::forward<Args>(args)...);
  }
};

struct YoN : Bool {
  using Bool::Bool;
  friend std::ostream& operator<<(std::ostream& os, const YoN& b) {
    os << ((bool) b ? "YES" : "NO");
    return os;
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
