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

  void debug() {
    map<int, wi> groups;
    for (int i = 1; i <= p.sz(); i++) {
      groups[find(i)].pb(i);
    }

    wwi debug_groups;
    for (auto members: groups | views::values) debug_groups.eb(members);

    debug_all(debug_groups);
  }
};
