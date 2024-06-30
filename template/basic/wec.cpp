#pragma once
#include "bool.cpp"
#include "con.cpp"

template <typename V>
struct wec : public Con<std::vector<NotBool_t<V>>> {
  using T = NotBool_t<V>;
  using Con<std::vector<typename NotBool<V>::type>>::Con;

  T& operator[](size_t index) {
    return this->v[index - 1];
  }

  const T& operator[](size_t index) const {
    return this->v[index - 1];
  }
};
