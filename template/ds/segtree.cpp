#pragma once

template <typename Node>
struct Segtree {
  using Merge = std::function<const Node(const Node&, const Node&)>;
  Merge merge;
  int n;
  vec<Node> t;

  template <typename Cont>
  Segtree(Cont arr, Merge merge) : merge(merge),
                                   n(sz(arr)),
                                   t(4 * n) {
    build(arr, 1, 0, sz(arr) - 1);
  }
  template <typename Cont>
  void build(Cont& a, int v, int tl, int tr) {
    deb(v, tl, tr);
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
    deb("update", v, tl, tr, pos, val);
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
