#pragma once

#include "../base.cpp"
template <typename Container>
constexpr int get_presum_offset_v = 0;

template <typename T, template <class, class...> class C, int offset>
constexpr int get_presum_offset_v<list<T, C, offset>> = offset;

template <typename T, const int offset = 0>
// fix template caide inline
struct PreSum {
  vec<T> pre{0};

  template <typename Container>
    requires requires { typename Container::value_type; }
  explicit PreSum(const Container& arr) {
    pre.reserve(arr.sz() + 1);
    int size = 1;
    for (const auto& x: arr) {
      pre.pb(pre.back() + static_cast<T>(x));
      size++;
      assert(pre.sz() == size);
    }

    assert(pre.sz() == arr.sz() + 1);
  }

  T query(const int l, int r) {
    if (r < l) return T();
    return pre[r - offset + 1] - pre[l - offset];
  }

  T prefix(int r) {
    return query(offset, r);
  }
  // TODO: add suffix
  // T suffix(int l) {
  // return query(l, pre.sz());
  // }
};
template <HasValueType Container>
PreSum(const Container&)
    -> PreSum<sum_v<typename Container::value_type>, get_presum_offset_v<remove_cv_t<Container>>>;
