#pragma once
#include "bool.cpp"
#include "con.cpp"

template <typename V>
struct vec : public Con<vector<typename NotBool<V>::type>> {
  using T = NotBool<V>::type;
  using Con<vector<typename NotBool<V>::type>>::Con;
};
