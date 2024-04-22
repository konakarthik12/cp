#pragma once
#include "../concepts.cpp"
#include "bool.cpp"

template <typename V>
struct vec {
  using T = NotBool<V>::type;
  using value_type = T;

  vector<T> v;

  vec() {
  }
  explicit vec(int size) : v(size) {
  }
  explicit vec(int size, T init) : v(size, init) {
  }
  template <typename Container>
    requires HasIter<Container>
  explicit vec(Container cnt) : v(cnt.begin(), cnt.end()) {
  }
  vec(initializer_list<V> initList) : v(initList.size()) {
    auto it = v.begin();
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
  void assign(int size, T x = T()) {
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
  template <typename... Args>
  auto insert(Args&&... args) {
    return v.insert(std::forward<Args>(args)...);
  }

  void pop_back() {
    v.pop_back();
  }

  void clear() {
    v.clear();
  }

  bool operator==(const vec& other) const {
    return this->v == other.v;
  }
  auto operator<=>(const vec& other) const {
    return this->v <=> other.v;
  }
};
