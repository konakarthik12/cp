#pragma once
#include "bool.cpp"
#include "con.cpp"

template <typename V>
struct wec : public vec<V> {
  using T =  vec<V>::T;

  using vec<V>::vec;

  T& operator[](size_t index) {
    return this->v[index - 1];
  }

  const T& operator[](size_t index) const {
    return this->v[index - 1];
  }
};
