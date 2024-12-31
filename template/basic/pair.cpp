#pragma once
#include "../wrapper.hpp"

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
    swapsort(f, s);
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
