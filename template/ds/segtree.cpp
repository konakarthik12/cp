#pragma once
#include "../base.cpp"
#include "../deb.cpp"
template <typename Node>
struct RecurSegtree {
  using Merge = std::function<const Node(const Node&, const Node&)>;
  Merge merge;
  int n;
  vec<Node> t;

  template <typename Cont>
  RecurSegtree(Merge merge, Cont arr) : merge(merge),
                                        n(sz(arr)),
                                        t(4 * n) {
    build(arr, 1, 0, sz(arr) - 1);
  }
  template <typename Cont>
  void build(Cont& a, int v, int tl, int tr) {
    n = sz(a);
    t.assign(4 * n);
    if (tl == tr) {
      t[v] = Node(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }
  }

  void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
      t[v] = Node(val);
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) update(v * 2, tl, tm, pos, val);
      else update(v * 2 + 1, tm + 1, tr, pos, val);
      t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }
  }

  Node query(int v, int tl, int tr, int l, int r) {
    if (r < l) return Node();
    if (l == tl && r == tr) {
      return t[v];
    }
    int tm = (tl + tr) / 2;
    return merge(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }
  Node query(int l, int r) {
    return query(1, 0, n - 1, l, r);
  }
  void update(int idx, int v) {
    return update(1, 0, n - 1, idx, v);
  }
};

template <typename Node, bool easy_index = true>
struct Segtree {
  using Merge = function<Node(const Node&, const Node&)>;
  Merge merge;
  int n;
  wec<Node> t;

  Segtree(Merge merge) : merge(merge) {
  }
  Segtree(Merge merge, int n) : merge(merge) {
    init(n);
  }

  template <typename Cont>
  Segtree(Merge merge, Cont& a) : merge(merge) {
    build(a);
  }

  void init(int _n) {
    n = _n;
    t.assign(2 * n - 1);
  }

  void init_set(int p, Node v) {
    if cexp (easy_index) p--;
    t[p + n] = v;
  }

  Node get(int p) {
    if cexp (easy_index) p--;
    return t[p + n];
  }

  void build() {
    for (int i = n - 1; i > 0; i--) t[i] = merge(t[i << 1], t[i << 1 | 1]);
  }

  template <typename Cont>
  void build(Cont& a) {
    init(sz(a));
    int i = n;
    for (int x: a) t[i++] = x;
    build();
  }

  void update(int p, Node v) {
    if cexp (easy_index) p--;
    dssert(p >= 0 && p < n);
    for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = merge(t[p], t[p ^ 1]);
  }

  Node query(int l, int r) {
    if cexp (easy_index) l--;
    Node res = {};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = merge(res, t[l++]);
      if (r & 1) res = merge(res, t[--r]);
    }
    return res;
  }
  Node prefix(int r) {
    const int l = easy_index ? 1 : 0;
    return query(l, r);
  }

  Node suffix(int l) {
    return query(l, n);
  }
  Node whole() {
    return t.front();
  }
};
