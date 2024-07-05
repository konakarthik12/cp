#pragma once

#include "../scaffold.cpp"

template <typename T, typename Comp = less<T>>
struct mset {
  std::set<T, Comp> v;

  mset() {
  }

  mset(const std::multiset<T>& v) : v(v) {
  }

  mset(const mset& s) : v(s.v) {
  }

  mset(mset&& s) : v(std::move(s.v)) {
  }

  mset& operator=(const mset& s) {
    v = s.v;
    return *this;
  }

  mset& operator=(mset&& s) {
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

  void rf() {
    v.erase(v.begin());
  }

  void rb() {
    v.erase(std::prev(v.end()));
  }

  auto insert(T x) {
    return v.insert(x);
  }
  template <typename U>
  auto erase(U&& x) {
    return v.erase(std::forward<U>(x));
  }

  auto erase_one(T x) {
    auto it = v.find(x);
    if (it != v.end()) {
      v.erase(it);
      return true;
    }
    return false;
  }

  int size() const {
    return v.size();
  }

  auto contains(T x) const {
    return v.contains(x);
  }

  explicit operator bool() const {
    return !v.empty();
  }

};