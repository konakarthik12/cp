#pragma once
#include "../scaffold.cpp"

template <size_t N>
class bitset : public std::bitset<N> {
 public:
  using std::bitset<N>::bitset;

  explicit operator int() const {
    return (int) this->to_ullong();
  }
  explicit operator long long() const {
    return (long long) this->to_ullong();
  }
};

