#pragma once
#include "base.cpp"

template <class Iter>
int idist(Iter a, Iter b) {
  return distance(a, b);
}
template <class Cont>
void dedupe(Cont& vec) {
  vec.erase(unique(all(vec)), vec.end());
}
template <class Cont, class Predicate>
void dedupe(Cont& vec, Predicate p) {
  vec.erase(unique(all(vec), p), vec.end());
}
template <class Cont>
void sort(Cont& vec) {
  sort(all(vec));
}
template <class Cont, class Comp>
void sort(Cont& vec, Comp comp) {
  sort(all(vec), comp);
}

template <class Cont>
void rsort(Cont& vec) {
  sort(vec, greater());
}

template <class Con, class Comp>
void sort_by(Con& vec, Comp key) {
  using T = Con::value_type;
  sort(all(vec), [&](T a, T b) { return key(a) < key(b); });
}

template <class Con, class Comp>
void rsort_by(Con& vec, Comp key) {
  using T = Con::value_type;
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
template <typename Cont>
ll sum(Cont& c) {
  return reduce(all(c), 0LL);
}

template <class Cont, typename T>
void fill(Cont& vec, T value) {
  fill(all(vec), value);
}

template <typename Cont>
vll prefix_sum(Cont& arr) {
  vll prefixs(sz(arr) + 1);
  inclusive_scan(all(arr), prefixs.begin() + 1, plus(), 0LL);
  return prefixs;
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

template <typename T>
T min(vec<T>& arr) {
  return *min_element(all(arr));
}

template <typename T>
T max(vec<T>& arr) {
  return *max_element(all(arr));
}