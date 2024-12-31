#pragma once
#include "bool.cpp"
#include "con.cpp"
#include "../deb.cpp"


template <typename V>
struct wec : public vec<V> {
  using T = vec<V>::T;
  using C = vec<V>::Con;
  using vec<V>::vec;

  T& operator[](size_t index) {
    dssert(index >= 1 && <= this->v.size());
    return this->v[index - 1];
  }

  const T& operator[](size_t index) const {
    dssert(index >= 1 && <= this->v.size());

    return this->v[index - 1];
  }

  void iota(int a, int b) {
    this->resize(b - a + 1);
    std::iota(this->v.begin(), this->v.end(), a);
  }

  void iota(int n) {
    iota(1, n);
  }
};
