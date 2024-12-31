#pragma once
#include "../scaffold.cpp"
#include "pair.cpp"

template <typename T, typename Comp = less<T>>
struct set {
  std::set<T, Comp> v;
  using value_type = T;
  set() {
  }

  set(const std::set<T>& v) : v(v) {
  }

  set(const set& s) : v(s.v) {
  }

  set(set&& s) : v(std::move(s.v)) {
  }

  set(initializer_list<T> initList) {
    for (const auto& value: initList) v.insert(value);
  }

  set& operator=(const set& s) {
    v = s.v;
    return *this;
  }

  set& operator=(set&& s) {
    v = std::move(s.v);
    return *this;
  }

  auto begin() const {
    return v.begin();
  }
  auto end() const {
    return v.end();
  }

  auto front() {
    return *v.begin();
  }

  auto back() {
    return *v.rbegin();
  }

  auto front() const {
    return *v.begin();
  }

  auto back() const {
    return *v.rbegin();
  }

  T rf() {
    T x = *v.begin();
    v.erase(v.begin());
    return x;
  }

  T rb() {
    auto iter = prev(v.end());
    T x = *iter;
    v.erase(iter);
    return x;
  }

  template <typename... Args>
  auto insert(Args&&... args) {
    return v.insert(std::forward<Args>(args)...);
  }
  template <typename... Args>
  auto emplace(Args&&... args) {
    return v.emplace(std::forward<Args>(args)...);
  }
  template <typename U>
  auto erase(U&& x) {
    return v.erase(std::forward<U>(x));
  }

  int sz() const {
    return v.size();
  }

  auto contains(T x) const {
    return v.contains(x);
  }

  explicit operator bool() const {
    return !v.empty();
  }

  auto find(T x) {
    return v.find(x);
  }

  auto clear() {
    return v.clear();
  }

  auto lower_bound(T x) {
    return v.lower_bound(x);
  }
  auto upper_bound(T x) {
    return v.upper_bound(x);
  }
  auto near(T x) {
    auto iter = v.lower_bound(x);
    if (iter == v.end()) return *prev(iter);
    if (iter == v.begin()) return *iter;
    return min(*prev(iter), *iter, Comp());
  }

  pr<T&, T&> near_lr(T x) {
    auto cur = *v.upper_bound(x);
    auto prv = *prev(cur);
    return pr{prv, cur};
  }
  auto ge(T x) {
    return *v.lower_bound(x);
  }

  auto gr(T x) {
    return *v.upper_bound(x);
  }

  auto ls(T x) {
    auto iter = v.lower_bound(x);
    return *prev(iter);
  }

  auto le(T x) {
    auto iter = v.upper_bound(x);
    return *prev(iter);
  }
};
