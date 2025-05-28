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

  bitset operator^(const bitset& other) const {
    std::bitset<N> result = std::operator^(*this, other);

    return bitset(result);
  }

  // performance
  // Construct from base bitset directly
  explicit bitset(const std::bitset<N>& b) : std::bitset<N>(b) {
  }

  // Move constructor from base
  explicit bitset(std::bitset<N>&& b) : std::bitset<N>(std::move(b)) {
  }

  // Construct from unsigned long long
  explicit bitset(unsigned long long value) : std::bitset<N>(value) {
  }
};

template <int N>
using witset = bitset<N, true>;
