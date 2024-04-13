#pragma once
#include "bool.cpp"

template <typename V>
struct wec {
  using T = NotBool<V>::type;
  vector<T> v;

  wec() : v(1) {
  }
  explicit wec(int size) : v(size + 1) {
  }
  explicit wec(int size, T init) : v(size + 1, init) {
  }

  wec(initializer_list<V> initList) : v(initList.size() + 1) {
    auto it = v.begin() + 1;
    for (const auto& value: initList) {
      *it++ = value;
    }
  }

  T& operator[](size_t index) {
    return v[index];
  }

  const T& operator[](size_t index) const {
    return v[index];
  }

  auto end() {
    return v.end();
  }

  int size() const {
    return v.size() - 1;
  }
  void reserve(int size) {
    v.reserve(size + 1);
  }

  void resize(int size) {
    v.resize(size + 1);
  }
  void assign(int size, int x = T()) {
    v.assign(size + 1, x);
  }
  auto begin() {
    return v.begin() + 1;
  }

  auto begin() const {
    return v.begin() + 1;
  }

  auto end() const {
    return v.end();
  }
  T& front() {
    return v[1];
  }
  T& back() {
    return v.back();
  }

  void pb(const T& value) {
    v.push_back(value);
  }

  template <typename... Args>
  auto eb(Args&&... args) {
    return v.emplace_back(std::forward<Args>(args)...);
  }
  template <typename... Args>
  auto insert(Args&&... args) {
    return v.insert(std::forward<Args>(args)...);
  }

  void pop_back() {
    v.pop_back();
  }

  void clear() {
    v.resize(1);
  }
  auto operator<=>(const wec&) const = default;

  wec operator+(const wec& other) const {
    wec result = *this;
    result.insert(result.end(), other.begin(), other.end());
    return result;
  }

  using value_type = T;
};
