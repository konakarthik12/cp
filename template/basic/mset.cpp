#pragma once
#include "set.cpp"

template <typename T, typename Comp = less<T>>
struct mset : set<T, Comp, std::multiset> {
  using Base = set<T, Comp, std::multiset>;
  using Base::Base;
  using Base::operator=;

  // multiset-specific methods
  template <typename U>
  auto erase_all(U&& x) {
    return this->v.erase(std::forward<U>(x));
  }

  bool erase_one(const T& x) {
    auto it = this->v.find(x);
    if (it == this->v.end()) return false;
    this->v.erase(it);
    return true;
  }
  auto erase() = delete;
  
  auto contains(T x) const {
    return this->v.contains(x);
  }
  // Override near() for multiset-specific behavior
  auto near(T x) {
    auto iter = this->v.lower_bound(x);
    if (iter == this->v.end()) return *prev(iter);
    if (iter == this->v.begin()) return *iter;
    T a = *prev(iter);
    T b = *iter;
    return abs(a - x) < abs(b - x) ? a : b;
  }
};
