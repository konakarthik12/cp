#pragma once
#include "../concepts.cpp"
#include "con.cpp"
#include "pair.cpp"

// Helper to create set-like container type for Con
template <typename T, typename Comp = less<T>>
struct SetContainer {
  template <typename U, typename... Args>
  using type = std::set<U, Comp>;
};

template <typename T, typename Comp = less<T>, template <typename, typename> class SetType = std::set>
struct set : Con<T, SetType, 0, Comp> {
  using Base = Con<T, SetType, 0, Comp>;
  using value_type = T;

  set() {
  }

  set(const SetType<T, Comp>& v) {
    this->v = v;
  }

  set(const set& s) {
    this->v = s.v;
  }

  set(set&& s) {
    this->v = std::move(s.v);
  }

  set(initializer_list<T> initList) {
    for (const auto& value: initList) this->v.insert(value);
  }

  template <typename Iter>
    requires input_iterator<Iter>
  set(Iter start, Iter end) : Base(start, end) {
  }

  template <HasIter Container>
  explicit set(const Container& cnt) : Base(cnt) {
  }

  set& operator=(const set& s) {
    this->v = s.v;
    return *this;
  }

  set& operator=(set&& s) {
    this->v = std::move(s.v);
    return *this;
  }

  auto front() {
    return *this->v.begin();
  }

  auto back() {
    return *this->v.rbegin();
  }

  auto front() const {
    return *this->v.begin();
  }

  auto back() const {
    return *this->v.rbegin();
  }

  T rf() {
    T x = *this->v.begin();
    this->v.erase(this->v.begin());
    return x;
  }

  T rb() {
    auto iter = prev(this->v.end());
    T x = *iter;
    this->v.erase(iter);
    return x;
  }

  template <typename... Args>
  auto ps(Args&&... args) {
    return this->v.insert(std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto em(Args&&... args) {
    return this->v.emplace(std::forward<Args>(args)...);
  }

  auto erase(const T& x) {
    return this->v.erase(x);
  }

  template <typename U>
  auto erase(U&& x) {
    return this->v.erase(std::forward<U>(x));
  }

  auto has(T x) const {
    return this->v.contains(x);
  }

  auto merge(set<T, Comp, SetType>& u) {
    return this->v.merge(std::forward<SetType<T, Comp>>(u.v));
  }

  auto find(T x) {
    return this->v.find(x);
  }

  auto lower_bound(T x) {
    return this->v.lower_bound(x);
  }

  auto upper_bound(T x) {
    return this->v.upper_bound(x);
  }

  auto near(T x) {
    auto iter = this->v.lower_bound(x);
    if (iter == this->v.end()) return *prev(iter);
    if (iter == this->v.begin()) return *iter;
    return min(*prev(iter), *iter, Comp());
  }

  pr<T&, T&> near_lr(T x) {
    auto cur = *this->v.upper_bound(x);
    auto prv = *prev(cur);
    return pr{prv, cur};
  }

  auto ge(T x) {
    return *this->v.lower_bound(x);
  }

  auto gr(T x) {
    return *this->v.upper_bound(x);
  }

  auto ls(T x) {
    auto iter = this->v.lower_bound(x);
    return *prev(iter);
  }

  auto le(T x) {
    auto iter = this->v.upper_bound(x);
    return *prev(iter);
  }
};
