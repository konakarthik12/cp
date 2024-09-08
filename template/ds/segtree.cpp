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

//template <typename Node, bool easy_index = true>
//struct LazySegtree {
//  using Merge = function<Node(const Node&, const Node&)>;
//  Merge merge;
//  int n;
//  int h;
//  wec<Node> t;
//  wec<Node> d;
//
//  LazySegtree(Merge merge) : merge(merge) {
//  }
//  LazySegtree(Merge merge, int n) : merge(merge) {
//    init(n);
//  }
//
//  template <typename Cont>
//  LazySegtree(Merge merge, Cont& a) : merge(merge) {
//    init(sz(a));
//    build(a);
//  }
//
//  void init(int _n) {
//    n = _n;
//    h = blen(n);
//    t.assign(2 * n - 1);
//    d.assign(n, -1);
//  }
//
//  void init_set(int p, Node v) {
//    if cexp (easy_index) p--;
//    t[p + n] = v;
//  }
//
//  Node get(int p) {
//    if cexp (easy_index) p--;
//    return t[p + n];
//  }
//
//  void calc(int p, int k) {
//    if (d[p] == 0) t[p] = merge(t[p << 1], t[p << 1 | 1]);
//    else t[p] = d[p] * k;
//  }
//
//  void apply(int p, Node v, int k) {
//    deb("apply", p, v);
//    t[p] = v * k;
//    if (p < n) d[p] = v;
//  }
//
//  //  void build() {
//  //    for (int i = n - 1; i > 0; i--) t[i] = merge(t[i << 1], t[i << 1 | 1]);
//  //  }
//  //
//  //  void build(int p) {
//  //    while (p > 1) p >>= 1, t[p] = merge(t[p << 1], t[p << 1 | 1]) + d[p];
//  //  }
//
//  void build(int l, int r) {
//    int k = 2;
//    for (l += n, r += n-1; l > 1; k <<= 1) {
//      l >>= 1, r >>= 1;
//      for (int i = r; i >= l; --i) calc(i, k);
//    }
//  }
//
//  template <typename Cont>
//  void build(Cont& a) {
//    init(sz(a));
//    int i = n;
//    for (int x: a) t[i++] = x;
//    build();
//  }
//
//  void push(int p) {
//    deb("push", p);
//    for (int s = h; s > 0; --s) {
//      int i = p >> s;
//      if (i > 0 && d[i] != 0) {
//        apply(i << 1, d[i]);
//        apply(i << 1 | 1, d[i]);
//        d[i] = 0;
//      }
//    }
//  }
//
//  void update(int l, int r, int v) {
//    deb("update", l, r);
//    if cexp (easy_index) l--;
//    l += n;
//    r += n;
//
//    int l0 = l, r0 = r;
//    for (; l < r; l >>= 1, r >>= 1) {
//      if (l & 1) apply(l++, v);
//      if (r & 1) apply(--r, v);
//    }
//
//    build(l0);
//    build(r0 - 1);
//  }
//
//  Node query(int l, int r) {
//    deb("query", l, r);
//    if cexp (easy_index) l--;
//    l += n, r += n;
//    deb(l, r);
//    push(l);
//    push(r - 1);
//    Node res = {};
//    for (; l < r; l >>= 1, r >>= 1) {
//      if (l & 1) res = merge(res, t[l++]);
//      if (r & 1) res = merge(res, t[--r]);
//    }
//    return res;
//  }
//  Node prefix(int r) {
//    const int l = easy_index ? 1 : 0;
//    return query(l, r);
//  }
//
//  Node suffix(int l) {
//    return query(l, n);
//  }
//  Node whole() {
//    return t.front();
//  }
//};


// const int N = 2e5;

// struct Node {
//   int t = 0, p = 0, v = 0;

//   operator bool() {
//     return t == 0 && p == 0 && v == 0;
//   }
// };

// void debug(Node& node) {
//   debug(tuple{"Node", node.t, node.p, node.v});
// }

// Node merge(const Node& a, const Node& b) {
//   if (a.t > b.t) {
//     int time = a.t - b.t;
//     int bv1 = b.p + b.v * time;
//     return {a.t, a.p + bv1, a.v + b.v};
//   } else if (b.t > a.t) {
//     int time = b.t - a.t;
//     int av1 = a.p + a.v * time;
//     return {b.t, av1 + b.p, a.v + b.v};
//   } else {
//     return {a.t, a.p + b.p, a.v + b.v};
//   }
// }

// struct Lazy {
//   int t_s = 0, t = 0, p = 0, v = 0;

//   operator bool() {
//     return t_s = 0 && t == 0 && p == 0 && v == 0;
//   }
// };

// struct NewVal {
//   int t, v;
// };

// Lazy merge_lazy(const Lazy& a, const Lazy& b) {
//   // dssert(a.t_s >= b.t);
//   // int time = a.t_s - b.t;
//   // return {a.t, b.p + b.v * time + a.p, a.v};
// }

// Node push_lazy(const Lazy& p, const Node& c) {
//   dssert(p.t_s >= c.t);
//   int time = p.t_s - c.t;
//   return {p.t, c.p + c.v * time + p.p, p.v};
// }

// Node t[2 * N];
// Lazy d[N];
// int n, h;

