#pragma once
#include "../base.cpp"
#include "../deb.cpp"
template <typename Node, bool easy_index = true>
struct RecurSegtree {
  using Merge = std::function<const Node(const Node&, const Node&)>;
  Merge merge;
  int n;

  vec<Node> t;

  template <typename Cont>
  RecurSegtree(Merge merge, Cont arr) : merge(merge),
                                        n(arr.sz()),
                                        t(4 * n) {
    build(arr);
  }
  template <typename Cont>
  void build(Cont& a) {
    n = a.sz();
    t.assign(4 * n);
    build(a, 1, 1, a.sz());
  }

  template <typename Cont>
  void build(Cont& a, int v, int tl, int tr) {

    if (tl == tr) {
      t[v] = Node(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }
  }

  void assign(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
      t[v] = Node(val);
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) assign(v * 2, tl, tm, pos, val);
      else assign(v * 2 + 1, tm + 1, tr, pos, val);
      t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }
  }

  Node query(int v, int tl, int tr, int l, int r) {
    if (r < l) return Node();
    if (l == tl && r == tr) {
      return t[v];
    }
    int tm = (tl + tr) / 2;
    Node left = query(v * 2, tl, tm, l, min(r, tm));
    Node right = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    return merge(left, right);
  }

  Node query(int l, int r) {
    if cexp (easy_index) l--;
    if cexp (easy_index) r--;
    return query(1, 0, n - 1, l, r);
  }
  void assign(int idx, int v) {
    if cexp (easy_index) idx--;

    return assign(1, 0, n - 1, idx, v);
  }
};

template <typename Node, bool easy_index = true>
struct Segtree {
  using Merge = function<Node(const Node&, const Node&)>;
  Merge merge;
  int n;
  wec<Node> t;

  Segtree(Merge merge = std::plus()) : merge(merge) {
  }
  Segtree(Merge merge, int n) : merge(merge) {
    init(n);
  }

  Segtree(Merge merge, int n, int v) : merge(merge) {
    init(n, v);
  }
  template <typename Cont>
  Segtree(Merge merge, Cont& a) : merge(merge) {
    build(a);
  }

  void init(int _n) {
    n = _n;
    t.assign(2 * n - 1);
  }
  void init(int _n, int v) {
    n = _n;
    t.assign(2 * n - 1, v);
    build();
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
    init(a.sz());
    int i = n;
    for (int x: a) t[i++] = x;
    build();
  }

  void assign(int p, Node v) {
    if cexp (easy_index) p--;
    dssert(p >= 0 && p < n);
    for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = merge(t[p], t[p ^ 1]);
  }
  void inc(int p, Node v) {
    if cexp (easy_index) p--;
    dssert(p >= 0 && p < n);
    for (t[p += n] += v; p > 1; p >>= 1) t[p >> 1] = merge(t[p], t[p ^ 1]);
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
