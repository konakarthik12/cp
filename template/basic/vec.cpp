#pragma once
#include "bool.cpp"

template <typename V>
struct vec {
  using T = NotBool<V>::type;
  vector<T> v;

  vec() : v() {
  }
  explicit vec(int size) : v(size) {
  }
  explicit vec(int size, T init) : v(size, init) {
  }
  vec(initializer_list<V> initList) : v(initList.size()) {
    auto it = v.begin();
    for (const auto& value: initList) {
      *it++ = value;
    }
  }

  template <typename... Args>
  vec(Args... args) : v{args...} {
  }

  T& operator[](size_t index) {
    return v[index];
  }

  const T& operator[](size_t index) const {
    return v[index];
  }
  auto begin() {
    return v.begin();
  }

  auto end() {
    return v.end();
  }

  T& front() {
    return v.front();
  }

  T& back() {
    return v.back();
  }
  int size() const {
    return v.size();
  }
  void reserve(int size) {
    v.reserve(size);
  }

  void resize(int size) {
    v.resize(size);
  }
  void assign(int size, int x = T()) {
    v.assign(size, x);
  }

  auto begin() const {
    return v.begin();
  }

  auto end() const {
    return v.end();
  }

  void pb(const T& element) {
    v.push_back(element);
  }

  template <typename... Args>
  auto eb(Args&&... args) {
    return v.emplace_back(std::forward<Args>(args)...);
  }

  void pop_back() {
    v.pop_back();
  }

  void clear() {
    v.clear();
  }

  auto operator<=>(const vec&) const = default;

  using value_type = T;
};
