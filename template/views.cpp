#pragma once
#include "wrapper.h"
template <typename T>
struct custom_adjacent_pairwise_view : public ranges::view_base {
  vector<T>& data;

  custom_adjacent_pairwise_view(vector<T>& input_data) : data(input_data) {
  }

  class iterator {
   private:
    using base_iterator = decltype(begin(declval<vector<T>&>()));
    base_iterator iter;

   public:
    iterator(base_iterator it) : iter(it) {
    }

    pair<T, T> operator*() const {
      return {*iter, *next(iter)};
    }

    iterator& operator++() {
      ++iter;
      return *this;
    }

    bool operator!=(const iterator& other) const {
      return iter != other.iter;
    }
  };

  iterator begin() {
    return iterator(data.begin());
  }

  iterator end() {
    return iterator(data.end() - 1);  // stop one element before the end
  }
};

template <typename T>
auto custom_adjacent_pairwise(vector<T>& data) {
  return custom_adjacent_pairwise_view<T>(data);
}
struct pairwise_tag {};
inline constexpr pairwise_tag pairwise{};

template <typename T>
auto operator|(vector<T>& data, pairwise_tag) {
  return custom_adjacent_pairwise_view<T>(data);
}
