#pragma once
#include "../concepts.cpp"

template <typename C>
struct Con {
  using T = C::value_type;
  using value_type = T;
  C v;

  Con() {
  }
  explicit Con(int size) : v(size) {
  }
  explicit Con(int size, T init) : v(size, init) {
  }
  template <typename Container>
    requires HasIter<Container>
  explicit Con(Container cnt) : v(cnt.begin(), cnt.end()) {
  }
  Con(initializer_list<T> initList) : v(initList.size()) {
    auto it = v.begin();
    for (const auto& value: initList) {
      *it++ = value;
    }
  }

  auto begin() const {
    return this->v.begin();
  }

  auto end() const {
    return this->v.end();
  }

  T& front() {
    return this->v.front();
  }

  T& back() {
    return this->v.back();
  }
  int size() const {
    return this->v.size();
  }

  bool empty() const {
    return this->v.empty();
  }
  explicit operator bool() const {
    return !this->empty();
  }
  T& operator[](size_t index) {
    return this->v[index];
  }

  const T& operator[](size_t index) const {
    return this->v[index];
  }

  void reserve(int size) {
    this->v.reserve(size);
  }

  void resize(int size) {
    this->v.resize(size);
  }
  void assign(int size, T x = T()) {
    this->v.assign(size, x);
  }

  void pb(const T& element) {
    this->v.push_back(element);
  }

  template <typename... Args>
  auto& eb(Args&&... args) {
    return this->v.emplace_back(std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto& insert(Args&&... args) {
    return this->v.insert(std::forward<Args>(args)...);
  }

  void rb() {
    this->v.pop_back();
  }

  void clear() {
    this->v.clear();
  }

  bool operator==(const Con& other) const {
    return this->v == other.v;
  }
  auto operator<=>(const Con& other) const {
    return this->v <=> other.v;
  }
};
