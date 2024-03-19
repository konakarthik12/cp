#pragma once
#include "base.cpp"

template <class Iter>
int idist(Iter a, Iter b) {
  return distance(a, b);
}

template <class Cont>
void rsort(Cont& vec) {
  sort(vec, greater());
}

template <class Con, class Comp>
void sort_by(Con& vec, Comp key) {
  using T = typename Con::value_type;
  sort(all(vec), [&](T a, T b) { return key(a) < key(b); });
}

template <class Con, class Comp>
void rsort_by(Con& vec, Comp key) {
  using T = typename Con::value_type;
  sort(all(vec), [&](T a, T b) { return key(a) > key(b); });
}

template <class Cont>
void reverse(Cont& vec) {
  reverse(all(vec));
}

template <class Cont>
void erase_all(Cont& vec, char c) {
  vec.erase(remove(all(vec), c), vec.end());
}

template <typename C>
auto sum(const C& c) {
  if cexp (is_integral_v<typename C::value_type>) return reduce(all(c), 0LL);
  else return reduce(all(c), typename C::value_type(0));
}

template <class C, typename T>
void fill(C& vec, T value) {
  fill(all(vec), value);
}

template <typename Out = ll, typename Cont>
vec<Out> prefix_sum(Cont& arr) {
  vec<Out> prefixs(sz(arr) + 1);
  inclusive_scan(all(arr), prefixs.begin() + 1, plus(), Out(0));
  return prefixs;
}

template <typename Cont>
  requires is_integral_v<typename Cont::value_type>
Cont pref_arr(Cont& arr) {
  Cont prefixs(sz(arr));
  inclusive_scan(all(arr), prefixs.begin(), plus(), 0LL);
  return prefixs;
}

template <typename Cont>
  requires(!is_integral_v<typename Cont::value_type>)
Cont pref_arr(Cont& arr) {
  Cont prefixs(sz(arr));
  inclusive_scan(all(arr), prefixs.begin(), plus(), typename Cont::value_type(0));
  return prefixs;
}

template <typename Cont>
Cont diff_arr(Cont& arr) {
  Cont diff(sz(arr));
  adjacent_difference(all(arr), diff.begin());
  return diff;
}

template <typename Cont, typename T>
pr<T, T> minmax(Cont& arr) {
  auto [l, r] = minmax_element(all(arr));
  return {*l, *r};
}

template <typename T, typename F>
pr<T, T> minmax(vec<T>& arr, F comb) {
  auto [l, r] = minmax_element(all(arr), comb);
  return {*l, *r};
}

//template <typename T>
//  requires HasIter<T>
//auto min(T& arr) {
//  return *min_element(all(arr));
//}
//
//template <typename T>
//  requires HasIter<T>
//auto max(T& arr) {
//  return *max_element(all(arr));
//}
