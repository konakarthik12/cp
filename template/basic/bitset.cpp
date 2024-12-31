#pragma once
#include "../scaffold.cpp"

template <size_t N, bool easy_index = false>
class bitset : public std::bitset<N> {
 public:
  using std::bitset<N>::bitset;

  explicit operator int() const {
    return (int) this->to_ullong();
  }
  explicit operator long long() const {
    return (long long) this->to_ullong();
  }

  auto operator[](size_t index) {
    if cexp (easy_index) index--;
    return std::bitset<N>::operator[](index);
  }

  auto operator[](size_t index) const {
    if cexp (easy_index) index--;
    return std::bitset<N>::operator[](index);
  }
  bool operator<(const bitset& other) const {
    return this->to_ullong() < other.to_ullong();
  }
};
