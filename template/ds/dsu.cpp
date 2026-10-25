#pragma once
#include "../base.cpp"

template <typename T_raw = void>
struct DSU {
  wi p;
  int cnt;
  using T = std::conditional_t<is_void_v<T_raw>, int, T_raw>;
  wec<T> d;
  DSU(int n) : cnt(n) {
    p.iota(n);
    if cexp (is_void_v<T_raw>) {
      d.assign(n, 1);
    } else {
      d.assign(n);
    }
  }

  DSU(wec<T> data) : d(data) {
    cnt = d.sz();
    p.iota(d.sz());
  }

  int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
  }

  T& get(int x) {
    return d[find(x)];
  }

  int join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return a;
    cnt--;
    if (d[a] < d[b]) swap(a, b);
    p[b] = a;
    d[a] += d[b];
    return a;
  }

  bool same(int a, int b) {
    a = find(a);
    b = find(b);
    return a == b;
  }
  wi unique() {
    wi arr;
    for (int i = 1; i <= p.sz(); i++) {
      if (p[i] == i) {
        arr.pb(i);
      }
    }
    return arr;
  }

  wwi groups() {
    map<int, wi> groups_map;
    for (int i = 1; i <= p.sz(); i++) {
      groups_map[find(i)].pb(i);
    }

    wwi groups;
    for (auto members: groups_map | views::values) groups.eb(members);
    return groups;
  }
  void debug() {

    debug_all(groups());
  }
};
