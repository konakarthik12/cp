#pragma once
#include "concepts.cpp"
#include "wrapper.h"
//
//template <typename V>
////  requires HasIter<V>
//struct custom_adjacent_pairwise_view : public ranges::view_base {
//  using T = typename V::value_type;
//  V& data;
//
//  custom_adjacent_pairwise_view(V& input_data) : data(input_data) {
//  }
//
//  class iterator {
//   private:
//    using base_iterator = decltype(declval<V&>().begin());
//    base_iterator iter;
//
//   public:
//    iterator(base_iterator it) : iter(it) {
//    }
//
//    pair<T, T> operator*() const {
//      return {*iter, *next(iter)};
//    }
//
//    iterator& operator++() {
//      ++iter;
//      return *this;
//    }
//
//    bool operator!=(const iterator& other) const {
//      return iter != other.iter;
//    }
//  };
//
//  iterator begin() {
//    return iterator(data.begin());
//  }
//
//  iterator end() {
//    return iterator(prev(data.end()));
//  }
//};
//
//template <typename T>
//  requires HasIter<T>
//auto custom_adjacent_pairwise(T& data) {
//  return custom_adjacent_pairwise_view<T>(data);
//}
//struct pairwise_tag {};
//inline constexpr pairwise_tag pairwise{};
//
//template <typename T>
//  requires HasIter<T>
//auto operator|(T& data, pairwise_tag) {
//  return custom_adjacent_pairwise_view<T>(data);
//}
