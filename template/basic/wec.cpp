#pragma once
#include "bool.cpp"

template <typename V>
struct wec : public Con<vector<typename NotBool<V>::type>> {
  using T = NotBool<V>::type;
  using C = Con<vector<T>>;

  wec() : C(1) {
  }
  explicit wec(int size) : C(size + 1) {
  }
  explicit wec(int size, T init) : C(size + 1, init) {
  }

  wec(initializer_list<V> initList) : C(initList.size() + 1) {
    auto it = this->v.begin() + 1;
    for (const auto& value: initList) {
      *it++ = value;
    }
  }

  int size() const {
    return this->v.size() - 1;
  }
  bool empty() const {
    return this->v.size() == 1;
  }
  void reserve(int size) {
    this->v.reserve(size + 1);
  }

  void resize(int size) {
    this->v.resize(size + 1);
  }
  void assign(int size, int x = T()) {
    this->v.assign(size + 1, x);
  }
  auto begin() {
    return this->v.begin() + 1;
  }

  auto begin() const {
    return this->v.begin() + 1;
  }

  T& front() {
    return this->v[1];
  }



  void clear() {
    this->v.resize(1);
  }

  wec operator+(const wec& other) const {
    wec result = *this;
    result.insert(result.end(), other.begin(), other.end());
    return result;
  }

  explicit operator bool() const {
    return this->v.size() > 1;
  }
};
