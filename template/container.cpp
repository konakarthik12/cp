#pragma once
#include "base.cpp"
#include "views.cpp"
using lll = __int128;
template <typename T>
using expand_ll = std::common_type<ll, T>::type;

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

template <typename NewT1, typename T>
struct ReplaceFirst;

template <typename NewT1, template <typename, auto...> class Template, typename OldT1, auto... Rest>
struct ReplaceFirst<NewT1, Template<OldT1, Rest...>> {
  using type = Template<NewT1, Rest...>;
};

template <typename NewT1, typename T>
using replace_first = typename ReplaceFirst<T, NewT1>::type;

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

  vec<ReplaceI> p;
  reserve(p, v.sz() + 1);
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
  reserve(p, v.sz());
  auto iter = begin(v);

  p.pb(*iter);

  for (auto it = next(iter); it != end(v); ++it) {
    p.pb(op(p.back(), *it));
  }
  return p;
}

template <typename T = void, typename Cont>
auto pref_arr(Cont& v) {
  using W = conditional_t<is_void_v<T>, expand_ll<typename Cont::value_type>, T>;
  return pref_arr(v, std::plus<W>{});
}

template <typename Cont, typename Op, typename T = typename Cont::value_type,
          typename I = std::invoke_result_t<Op, T, T>>
  requires std::invocable<Op, T, T>
auto difference_arr(Cont& v, Op op) {
  using ReplaceI = I;

  replace_first<Cont, ReplaceI> d;
  reserve(d, v.sz() - 1);
  if (v.sz() < 2) return d;  // return empty if fewer than 2 elements

  for (int i = 2; i <= v.sz(); ++i) {
    d.pb(op(v[i], v[i - 1]));
  }

  return d;
}

template <typename Cont, typename I = typename Cont::value_type>
  requires(!std::invocable<I, typename Cont::value_type, typename Cont::value_type>)
auto difference_arr(Cont& v, I = {}) {
  return difference_arr(v, std::minus<I>{});
}
template <typename Cont, typename Op>
auto diff_arr(Cont& v, Op op) {
  using T = Cont::value_type;
  using ReplaceI = decltype(op(T{}, T{}));

  replace_first<Cont, ReplaceI> d;
  if (v.empty()) return d;

  d.reserve(v.sz());
  d.pb(v.front());
  for (auto [a, b]: v | pairwise) d.pb(op(b, a));

  return d;
}
template <typename T = void, typename Cont>
auto diff_arr(Cont& v) {
  using W = conditional_t<is_void_v<T>, typename Cont::value_type, T>;
  return diff_arr(v, std::minus<W>{});
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

template <typename Cont>
auto mismatch(Cont& a, Cont& b) {
  return std::mismatch(all(a), all(b));
}
