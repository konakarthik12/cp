#pragma once
#include "../base.cpp"

template <typename F>
struct merge_traits {};
template <typename R, typename A, typename B>
struct merge_traits<std::function<R(A, B)>> {
  using node_type = std::remove_cvref_t<R>;
  using in_type = std::remove_cvref_t<A>;
};

template <bool easy_index, typename Node, typename In, typename MergeFunc>
struct Sparse {
  MergeFunc merge;
  int n, w;
  vv<Node> table;
  Sparse(MergeFunc merge) : merge(merge) {
  }

  template <typename Cont>
  Sparse(MergeFunc merge, Cont arr) : merge(merge) {
    init(arr);
  }

  template <typename Cont>
  void init(Cont& arr) {
    n = arr.sz(), w = blen(n);
    table = vv<Node>(w, vec<Node>(n));
    int cur = 0;
    for (auto iter = arr.begin(); iter != arr.end(); iter++)
      table[0][cur++] = merge(*iter, *iter);  // lift In to Node via merge(In, In)
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

template <typename Node, typename In = Node, typename MergeFunc = std::function<const Node(const Node&, const Node&)>>
using SparseT = Sparse<true, Node, In, MergeFunc>;
template <typename Node, typename In = Node, typename MergeFunc = std::function<const Node(const Node&, const Node&)>>
using Sparse0 = Sparse<false, Node, In, MergeFunc>;

template <typename R, typename A, typename B>
Sparse(std::function<R(A, B)>)
    -> Sparse<true, typename merge_traits<std::function<R(A, B)>>::node_type,
              typename merge_traits<std::function<R(A, B)>>::in_type, std::function<R(A, B)>>;

template <typename R, typename A, typename B, typename Cont>
Sparse(std::function<R(A, B)>, Cont)
    -> Sparse<true, typename merge_traits<std::function<R(A, B)>>::node_type,
              typename merge_traits<std::function<R(A, B)>>::in_type, std::function<R(A, B)>>;

template <bool easy_index, typename Node, typename In, typename MergeFunc>
struct FastSparse : Sparse<easy_index, Node, In, MergeFunc> {
  using Sparse<easy_index, Node, In, MergeFunc>::Sparse;
  using Sparse<easy_index, Node, In, MergeFunc>::table;
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
// TODO: get cursor to clean this up

template <typename Node, typename In = Node, typename MergeFunc = std::function<const Node(const Node&, const Node&)>>
using FastSparseT = FastSparse<true, Node, In, MergeFunc>;
template <typename Node, typename In = Node, typename MergeFunc = std::function<const Node(const Node&, const Node&)>>
using FastSparse0 = FastSparse<false, Node, In, MergeFunc>;

template <typename R, typename A, typename B>
FastSparse(std::function<R(A, B)>)
    -> FastSparse<true, typename merge_traits<std::function<R(A, B)>>::node_type,
                  typename merge_traits<std::function<R(A, B)>>::in_type, std::function<R(A, B)>>;

template <typename R, typename A, typename B, typename Cont>
FastSparse(std::function<R(A, B)>, Cont)
    -> FastSparse<true, typename merge_traits<std::function<R(A, B)>>::node_type,
                  typename merge_traits<std::function<R(A, B)>>::in_type, std::function<R(A, B)>>;

template <typename Merge, typename Cont>
  requires HasIter<Cont> && requires(Merge m, typename Cont::value_type a, typename Cont::value_type b) {
    { m(a, b) };
  }
FastSparse(Merge, Cont)
    -> FastSparse<true,
                  std::remove_cvref_t<
                      std::invoke_result_t<Merge, const typename Cont::value_type&, const typename Cont::value_type&>>,
                  typename Cont::value_type, Merge>;

template <typename Merge, typename Cont>
  requires HasIter<Cont> && requires(Merge m, typename Cont::value_type a, typename Cont::value_type b) {
    { m(a, b) };
  }
Sparse(Merge, Cont)
    -> Sparse<true,
              std::remove_cvref_t<
                  std::invoke_result_t<Merge, const typename Cont::value_type&, const typename Cont::value_type&>>,
              typename Cont::value_type, Merge>;
