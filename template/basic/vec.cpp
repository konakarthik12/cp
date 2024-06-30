#pragma once
#include "bool.cpp"
#include "con.cpp"

template <typename V>
struct vec : public Con<std::vector<NotBool_t<V>>> {
  using T = NotBool<V>::type;
  using Con<std::vector<NotBool_t<V>>>::Con;
};
