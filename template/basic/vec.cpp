#pragma once
#include "bool.cpp"
#include "con.cpp"

template <typename V>
struct vec : public Con<NotBool_t<V>, std::vector> {
  using T = NotBool_t<V>;
  using C = Con<T, std::vector>;
  using Con<NotBool_t<V>, std::vector>::Con;
};
