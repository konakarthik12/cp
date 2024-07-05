#pragma once
#include "../scaffold.cpp"

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

  void rf() {
    v.erase(v.begin());
  }

  void rb() {
    v.erase(std::prev(v.end()));
  }

  template<typename ...Args>
  auto insert(Args&&... args) {
    return v.insert(std::forward<Args>(args)...);
  }
  template <typename U>
  auto erase(U&& x) {
    return v.erase(std::forward<U>(x));
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

  auto find(T x) {
    return v.find(x);
  }

  auto clear() {
    return v.clear();
  }

};