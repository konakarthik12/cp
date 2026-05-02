#pragma once
#include "../scaffold.cpp"

using ull = unsigned long long;
using ll = long long;
template <size_t N, bool easy_index = false>
class bitset : public std::bitset<N> {
 public:
  using std::bitset<N>::bitset;

  explicit operator int() const {
    return (int) this->to_ullong();
  }
  explicit operator ll() const {
    return (ll) this->to_ullong();
  }
  explicit operator ull() const {
    return this->to_ullong();
  }

  auto operator[](size_t index) {
    if cexp (easy_index) index--;
    return std::bitset<N>::operator[](index);
  }

  auto operator[](size_t index) const {
    if cexp (easy_index) index--;
    return std::bitset<N>::operator[](index);
  }
  auto operator<=>(const bitset& other) const {
    return this->to_ullong() <=> other.to_ullong();
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  auto operator<=>(const T& other) const {
    return static_cast<ll>(*this) <=> other;
  }

  bitset operator^(const bitset& other) const {
    std::bitset<N> result = std::operator^(*this, other);

    return bitset(result);
  }

  bitset operator+(const bitset& other) const {
    static_assert(N <= 64, "bitset size must fit in ull for addition");
    ull sum = (ull) * this + (ull) other;
    return bitset(sum);
  }
  bitset operator-(const bitset& other) const {
    static_assert(N <= 64, "bitset size must fit in ull for subtraction");
    ull diff = (ull) * this - (ull) other;
    return bitset(diff);
  }

  // performance
  // Construct from base bitset directly
  explicit bitset(const std::bitset<N>& b) : std::bitset<N>(b) {
  }

  // Move constructor from base
  explicit bitset(std::bitset<N>&& b) : std::bitset<N>(std::move(b)) {
  }

  bitset(ull value) : std::bitset<N>(value) {
  }

  void input() {
    ull x;
    std::cin >> x;
    *this = bitset<N, easy_index>(x);
  }

  bitset& operator++() {
    *this = *this + bitset(1ULL);
    return *this;
  }
  bitset& operator--() {
    *this = *this - bitset(1ULL);
    return *this;
  }
  bitset operator++(int) {
    bitset tmp = *this;
    *this = *this + bitset(1ULL);
    return tmp;
  }
  bitset operator--(int) {
    bitset tmp = *this;
    *this = *this - bitset(1ULL);
    return tmp;
  }
  // TODO: operator << and >>
  void debug() const {
    std::stringstream ss;
    ss << std::bitset<N>(*this);
    ss << " (" << (ull) * this << ')';
    auto s = ss.str();

    debug_all(s);
  }
  // TODO: count return ans

  // TODO: convert to bool
};

template <size_t N, bool easy_index, typename T>
  requires std::integral<T> || std::floating_point<T>
auto operator<=>(const T& lhs, const bitset<N, easy_index>& rhs) {
  return lhs <=> (ull) (rhs);
}

template <int N>
using witset = bitset<N, true>;
