#pragma once
#include "bool.cpp"
#include "con.cpp"

template <typename V, const int offset = 0>
struct vec : Con<NotBool_t<V>, std::vector, offset> {
  using T = NotBool_t<V>;
  using C = Con<T, std::vector, offset>;
  using Con<NotBool_t<V>, std::vector, offset>::Con;
};

