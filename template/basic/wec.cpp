#pragma once
#include "bool.cpp"
#include "con.cpp"
#include "vec.cpp"
#include "../deb_raw.cpp"

template <typename V>
struct wec : vec<V, 1> {
  using T = vec<V, 1>::T;
  using C = vec<V, 1>::Con;
  using vec<V, 1>::vec;
};
