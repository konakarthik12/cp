#pragma once
#include "base.cpp"
//
// template <typename T>
// struct widen_pre {
//  using type = T;
//};

// template <>
// struct widen_pre<Bool> {
//   using type = int;
// };

template <typename T>
  requires integral<T>
struct widen_pre_t {
  using type = long long;
};

template <class T>
using widen_pre = widen_pre_t<T>::type;

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

template <typename C>
auto sum(const C& c) {
  if cexp (is_integral_v<typename C::value_type>) return reduce(all(c), 0LL);
  else return reduce(all(c), typename C::value_type(0));
}

template <class C, typename T>
void fill(C& vec, T value) {
  fill(all(vec), value);
}

template <class In, class Replace>
struct replace_first_type;
template <template <class...> class Z, class T0, class... Ts, class Replace>
struct replace_first_type<Z<T0, Ts...>, Replace> {
  using type = Z<Replace, Ts...>;
};

template <class In, class Replace>
using replace_first = typename replace_first_type<In, Replace>::type;

template <typename T>
void reserve(T& v, size_t s) {
  cexp bool HasReserve = requires {
    { v.reserve(s) };
  };

  if cexp (HasReserve) {
    v.reserve(s);
  }
}

template <typename Cont, typename Op,
          typename I = invoke_result_t<Op, typename Cont::value_type, typename Cont::value_type>>
  requires invocable<Op, I, I>
auto prefix_arr(Cont& v, Op op, I i = {}) {
  using T = Cont::value_type;
  using ReplaceI = decltype(op(T{}, T{}));

  replace_first<Cont, ReplaceI> p;
  reserve(p, size(v) + 1);
  I cur = i;
  p.pb(cur);

  for (auto x: v) {
    cur = op(cur, x);
    p.pb(cur);
  }

  return p;
}

template <typename Cont,
          typename I = conditional_t<is_integral_v<typename Cont::value_type>, long long, typename Cont::value_type>>
  requires(!invocable<I, typename Cont::value_type, typename Cont::value_type>)
auto prefix_arr(Cont& v, I i = {}) {
  return prefix_arr(v, std::plus<I>{}, i);
}

template <typename Cont, typename Op>
auto pref_arr(Cont& v, Op op) {
  using T = Cont::value_type;
  using ReplaceI = decltype(op(T{}, T{}));

  replace_first<Cont, ReplaceI> p;
  reserve(p, size(v));
  auto iter = begin(v);

  p.pb(*iter);

  for (auto it = next(iter); it != end(v); ++it) {
    p.pb(op(p.back(), *it));
  }
  return p;
}

template <typename T = void, typename Cont>
auto pref_arr(Cont& v) {
  using W = conditional_t<is_void_v<T>, widen_pre<typename Cont::value_type>, T>;
  return pref_arr(v, std::plus<W>{});
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
  requires HasIter<T>
auto min(T& arr) {
  return *min_element(all(arr));
}

template <typename T>
  requires HasIter<T>
auto max(T& arr) {
  return *max_element(all(arr));
}
