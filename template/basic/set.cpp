#pragma once
#include "../concepts.cpp"
#include "con.cpp"
#include "pair.cpp"
template <typename T, typename Comp = less<T>, template <typename, typename> class SetType = std::set>
struct set {
  SetType<T, Comp> v;
  using value_type = T;
  set() {
  }

  set(const SetType<T, Comp>& v) : v(v) {
  }

  set(const set& s) : v(s.v) {
  }

  set(set&& s) : v(std::move(s.v)) {
  }

  set(initializer_list<T> initList) {
    for (const auto& value: initList) v.insert(value);
  }
  template <typename Iter>
    requires input_iterator<Iter>
  set(Iter start, Iter end) : v(start, end) {
  }

  template <HasIter Container>
  explicit set(const Container& cnt) : v(cnt.begin(), cnt.end()) {
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
  auto erase(const T& x) {
    return v.erase(x);
  }

  template <typename U>
  auto erase(U&& x) {
    return v.erase(std::forward<U>(x));
  }

  int sz() const {
    return v.size();
  }

  auto has(T x) const {
    return v.contains(x);
  }

  explicit operator bool() const {
    return !v.empty();
  }

  auto merge(set<T>& u) {
    return v.merge(std::forward<SetType<T, Comp>>(u.v));
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

  auto operator==(const set<T>& other) const {
    return this->v == other.v;
  }
};
