#pragma once
#include "../base.cpp"

template <typename T>
struct DSU {
  wi p;
  wec<T> d;
  DSU(int n) : d(n) {
    p.iota(n);
  }

  DSU(int n, wec<T> data) : d(data) {
    p.iota(n);
  }

  int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
  }

  int join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return a;
    if (d[b] > d[a]) swap(a, b);
    p[b] = a;
    d[a] += d[b];
    return a;
  }
};

template <>
struct DSU<void> : DSU<int> {
  wi p;
  wi s;

  DSU(int n) : DSU<int>(n, wi(n)) {
  }
};

DSU(int n) -> DSU<void>;
