#pragma once
#include "../base.cpp"
template <typename Func>
wwi build_sparse(wi arr, Func merge) {
  int n = arr.sz();
  int w = blen(n);
  wwi table(w, wi(n));
  table[0] = arr;
  for (int h = 1; h < w; h++) {
    int hw = 1 << (h - 1);
    for (int i = 1; i <= n; i++) {
      table[h][i] = merge(table[h - 1][i], table[h - 1][i + hw]);
    }
  }
}

template <typename Node, bool easy_index = true>
struct Sparse {
  using Merge = std::function<const Node(const Node&, const Node&)>;
  Merge merge;
  int n, w;
  vv<Node> table;
  Sparse(Merge merge) : merge(merge) {
  }

  template <typename Cont>
  Sparse(Merge merge, Cont arr) : merge(merge) {
    init(arr);
  }

  template <typename Cont>
  void init(Cont& arr) {
    n = arr.sz(), w = blen(n);
    table = vv<Node>(w, vec<Node>(n));
    int cur = 0;
    for (auto iter = arr.begin(); iter != arr.end(); iter++) table[0][cur++] = *iter;
    for (int h = 1; h < w; h++) {
      int hw = 1 << (h - 1);
      for (int i = 0; i + hw < n; i++) {
        table[h][i] = merge(table[h - 1][i], table[h - 1][i + hw]);
      }
    }
  }
  Node query(int l, int r) {
    if (easy_index) {
      l--;
      r--;
    }
    Node sum = Node();
    for (int i = w - 1; i >= 0; i--) {
      if ((1 << i) <= r - l + 1) {
        sum = merge(sum, table[i][l]);
        l += 1 << i;
      }
    }
    return sum;
  }
};

template <typename Node, bool easy_index = true>
struct FastSparse : Sparse<Node, easy_index> {
  using Sparse<Node>::Sparse;
  using Sparse<Node>::table;
  Node query(int l, int r) {
    if (r < l) return Node();
    if (easy_index) {
      l--;
      r--;
    }
    int i = blen(r - l + 1) - 1;
    int fw = 1 << i;
    return this->merge(table[i][l], table[i][r - fw + 1]);
  }
};
