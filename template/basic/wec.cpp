#pragma once
#include "bool.cpp"
#include "con.cpp"
#include "../wrapper.h"

template <typename V>
struct wec : public Con<vector<typename NotBool<V>::type>> {
  using T = NotBool<V>::type;
  using Con<vector<typename NotBool<V>::type>>::Con;

  T& operator[](size_t index) {
    return this->v[index - 1];
  }

  const T& operator[](size_t index) const {
    return this->v[index - 1];
  }
};
