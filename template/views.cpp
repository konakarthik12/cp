#pragma once
#include "entry.cpp"

template <typename V>
  requires HasIter<V>
struct custom_adjacent_pairwise_view : public ranges::view_base {
  //  using T = remove_reference_t<V>::value_type;

  V& data;

  custom_adjacent_pairwise_view(V& input_data) : data(input_data) {
  }
  custom_adjacent_pairwise_view(const custom_adjacent_pairwise_view& other) : data(other.data) {
    // You may need to perform a deep copy of 'data' if necessary.
  }
  custom_adjacent_pairwise_view& operator=(custom_adjacent_pairwise_view&& other) noexcept {
    if (this != &other) {  // Check for self-assignment
      data = std::move(other.data);
    }
    return *this;
  }

  class custom_iterator {
   private:
    using base_iterator = decltype(begin(declval<V&>()));
    base_iterator iter;
    //    custom_iterator base_ = custom_adjacent_pairwise_view(data);

   public:
    using T = decltype(*iter);
    using value_type = pair<T, T>;
    using difference_type = int;
    using iterator_category = random_access_iterator_tag;
    using reference = value_type;
    using pointer = value_type*;

    custom_iterator() : iter() {
    }

    custom_iterator(base_iterator it) : iter(it) {
    }
    custom_iterator(custom_iterator const& other) : iter(other.iter) {
    }

    custom_iterator& operator++() {

      ++iter;
      return *this;
    }
    custom_iterator& operator--() {

      --iter;
      return *this;
    }

    custom_iterator operator++(int) {
      custom_iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    custom_iterator operator--(int) {

      custom_iterator tmp = *this;
      --(*this);
      return tmp;
    }
    auto operator-(custom_iterator& other) {
      return std::distance(*this, other);
    }

    auto operator+=(int n) {
      iter += n;
      return *this;
    }
    pair<T, T> operator*() const {
      return {*iter, *next(iter)};
    }

    bool operator==(const custom_iterator& other) const {
      return iter == other.iter;
    }
    auto base() {
      return this;
    }
  };

  custom_iterator begin() {

    return custom_iterator(data.begin());
  }
  //
  custom_iterator end() {
    auto hmm = custom_iterator(std::prev(data.end()));
    return hmm;
  }
  auto base() {
    return this;
  }
};

struct pairwise_tag {};
inline cexp pairwise_tag pairwise{};

template <typename T>
  requires HasIter<T>
auto operator|(T&& data, pairwise_tag) {
  return custom_adjacent_pairwise_view<T>(data);
}

auto rview = views::reverse;
