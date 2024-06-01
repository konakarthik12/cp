#pragma once
#include "../misc.cpp"
template <typename Func>
wwi build_sparse(wi arr, Func merge) {
  int n = sz(arr);
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

template <typename Node>
struct Sparse {
  using Merge = std::function<const Node(const Node&, const Node&)>;
  Merge merge;
  int n, w;
  vv<Node> table;
  Sparse() {
  }
  template <typename T>
  Sparse(vec<T> arr, Merge merge) : merge(merge) {
    init(arr);
  }

  template <typename T>
  void init(vec<T>& arr, Merge _merge) {
    merge = _merge;
    n = sz(arr), w = blen(n);
    table = vv<Node>(w, vec<Node>(n));
    for (int i = 0; i < n; i++) table[0][i] = Node(arr[i]);

    for (int h = 1; h < w; h++) {
      int hw = 1 << (h - 1);
      for (int i = 0; i + hw < n; i++) {
        table[h][i] = merge(table[h - 1][i], table[h - 1][i + hw]);
      }
    }
  }
  Node query(int l, int r) {
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

template <typename Node>
struct FastSparse : Sparse<Node> {
  using Sparse<Node>::Sparse;
  using Sparse<Node>::table;
  Node query(int l, int r) {
    int i = blen(r - l + 1) - 1;
    int fw = 1 << i;
    return merge(table[i][l], table[i][r - fw + 1]);
  }
};
