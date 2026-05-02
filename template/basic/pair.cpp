#pragma once
#include "../wrapper.hpp"
#include "../concepts.cpp"

template <typename T1, typename T2>
struct pr {
  T1 f;
  T2 s;
  pr() : f(T1()), s(T2()) {
  }

  pr(T1 f, T2 s) : f(f), s(s) {
  }
  pr(std::pair<T1, T2> p) : f(p.first), s(p.second) {
  }

  void sort() {
    if (f > s) swap(f, s);
  }
  pr<T1, T2> sorted() const {
    pr<T1, T2> x = *this;
    x.sort();
    return x;
  }

  void rsort() {
    if (f < s) swap(f, s);
  }
  auto sum() {
    return f + s;
  }
  auto min() {
    return std::min(f, s);
  }
  auto max() {
    return std::max(f, s);
  }

  pr<T1, T2> operator+(const pr<T1, T2>& other) const {
    return {f + other.f, s + other.s};
  }
  void operator+=(const pr<T1, T2>& other) {
    f += other.f;
    s += other.s;
  }
};

template <class T1, class T2>
bool operator<(const pr<T1, T2>& x, const pr<T1, T2>& y) {
  return tie(x.f, x.s) < tie(y.f, y.s);
}
template <class T1, class T2>
bool operator>(const pr<T1, T2>& x, const pr<T1, T2>& y) {
  return tie(x.f, x.s) > tie(y.f, y.s);
}
template <class T1, class T2>
bool operator==(const pr<T1, T2>& x, const pr<T1, T2>& y) {
  return tie(x.f, x.s) == tie(y.f, y.s);
}
struct pr_fview_tag {};
inline cexp pr_fview_tag fview{};

template <typename R>
  requires HasIter<R>
auto operator|(R&& data, pr_fview_tag) {
  return std::forward<R>(data) | views::transform([](auto& p) -> auto& { return p.f; });
}

struct pr_sview_tag {};
inline cexp pr_sview_tag sview{};

template <typename R>
  requires HasIter<R>
auto operator|(R&& data, pr_sview_tag) {
  return std::forward<R>(data) | views::transform([](auto& p) -> auto& { return p.s; });
}