#pragma once
#include "../wrapper.h"

template <typename T1, typename T2>
struct pr {
  T1 f;
  T2 s;
  pr() : f(T1()), s(T2()) {
  }

  pr(T1 f, T2 s) : f(f), s(s) {
  }
  pr(pair<T1, T2> spair) : f(spair.first), s(spair.second) {
  }

  void sort() {
    swapsort(f, s);
  }
  auto sum() {
    return f + s;
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
