#pragma once
#include "../base.cpp"

template <typename T>
struct PreSum {
  vec<T> pre{0};
  const int offset;
  template <typename T1>
  PreSum(const wec<T1>& arr) : offset(0) {
    pre.reserve(arr.sz() + 1);
    for (int x: arr) pre.pb(pre.back() + x);
  }
  template <typename T1>
  PreSum(const vec<T1>& arr) : offset(1) {
    pre.reserve(arr.sz() + 1);
    for (const T1& x: arr) pre.pb(pre.back() + x);
  }

  T query(int l, int r) {
    l += offset;
    r += offset;
    return pre[r] - pre[l - 1];
  }

  T prefix(int r) {
    return query(0, r);
  }
};
