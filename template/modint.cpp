#pragma once
#include "base.cpp"
#include "math.cpp"

template <typename T, typename ValueType = int>
struct ModIntBase {
  ValueType value = 0;

  bool operator==(const T& b) const {
    return value == b.value;
  }
  bool operator!=(const T& b) const {
    return value != b.value;
  }
  explicit operator int() const {
    return (int) value;
  }
  friend T operator+(T a, T const b) {
    return a += b;
  }
  friend T operator++(T& a) {
    return a += 1;
  }
  friend T operator--(T& a) {
    return a -= 1;
  }
  friend T operator++(T& a, int) {
    T b = a;
    a += 1;
    return b;
  }
  friend T operator--(T& a, int) {
    T b = a;
    a -= 1;
    return b;
  }

  friend T operator-(T a, T const b) {
    return a -= b;
  }
  friend T operator*(T a, T const b) {
    return a *= b;
  }
  friend T operator/(T a, T const b) {
    assert(b != 0);
    return a /= b;
  }
  friend T operator-(T const a) {
    return 0 - a;
  }
  friend ostream& operator<<(ostream& os, T const& a) {
    return os << a.value;
  }
};

template <int MOD = 998244353>
struct ModInt : public ModIntBase<ModInt<MOD>> {
  using ModIntBase<ModInt<MOD>>::value;

  ModInt(ll v = 0) {
    value = v % MOD;
    if (value < 0) value += MOD;
  }

  template <typename E>
  ModInt(ModInt a, E e) {
    value = 1;
    while (e) {
      if (e & 1) *this *= a;
      a *= a;
      e >>= 1;
    }
  }

  ModInt& operator+=(const ModInt& b) {
    value += b.value;
    if (value >= MOD) value -= MOD;
    return *this;
  }

  ModInt& operator-=(const ModInt& b) {
    value -= b.value;
    if (value < 0) value += MOD;
    return *this;
  }

  ModInt& operator*=(const ModInt& b) {
    value = (ll) value * b.value % MOD;
    return *this;
  }

  ModInt& operator/=(const ModInt& b) {
    return *this *= b.inverse();
  }

  ModInt inverse() const {
    return ModInt(*this, MOD - 2);
  }

  friend istream& operator>>(istream& is, ModInt& m) {
    is >> m.value;
    m.value %= MOD;
    return is;
  }
};

struct DynModInt : public ModIntBase<DynModInt> {
  static int mod;

  DynModInt(ll v = 0) {
    value = v % mod;
    if (value < 0) value += mod;
  }

  DynModInt(DynModInt a, ll e) {
    value = 1;
    while (e) {
      if (e & 1) {
        *this *= a;
      }
      a *= a;
      e >>= 1;
    }
  }

  DynModInt(ll a, ll e) : DynModInt(DynModInt(a), e) {
  }

  DynModInt& operator+=(const DynModInt& b) {
    value += b.value;
    if (value >= mod) {
      value -= mod;
    }
    return *this;
  }
  DynModInt& operator-=(const DynModInt& b) {
    value -= b.value;
    if (value < 0) {
      value += mod;
    }
    return *this;
  }
  DynModInt& operator*=(const DynModInt& b) {
    value = (ll) value * b.value % mod;
    return *this;
  }
  DynModInt& operator/=(const DynModInt& b) {
    return *this *= b.inverse();
  }
  DynModInt inverse() const {
    return DynModInt(*this, this->mod - 2);
  }
  friend istream& operator>>(istream& is, DynModInt& m) {
    is >> m.value;
    m.value %= m.mod;
    return is;
  }
  explicit operator ll() {
    return value;
  }
};
int DynModInt::mod = 998244353;

struct ModUll : public ModIntBase<ModUll, ull> {
  using ModIntBase<ModUll, ull>::value;

  ModUll() {
  }

  ModUll(ull v) {
    value = v;
  }

  ModUll(ll v) {
    value = (ull) v;
  }

  ModUll(int v) {
    value = (ull) v;
  }

  template <typename E>
  ModUll(ModUll a, E e) {
    value = 1;
    while (e) {
      if (e & 1) *this *= a;
      a *= a;
      e >>= 1;
    }
  }

  ModUll& operator+=(const ModUll& b) {
    value += b.value;  // Natural overflow wraps around
    return *this;
  }

  ModUll& operator-=(const ModUll& b) {
    value -= b.value;  // Natural underflow wraps around
    return *this;
  }

  ModUll& operator*=(const ModUll& b) {
    value *= b.value;  // Natural overflow wraps around
    return *this;
  }

  // Division is disabled
  ModUll& operator/=(const ModUll& b) = delete;

  explicit operator ull() const {
    return value;
  }
  explicit operator ll() const {
    return (ll) value;
  }

  friend istream& operator>>(istream& is, ModUll& m) {
    is >> m.value;
    return is;
  }
};

struct ModDouble {
  ld value;

  ModDouble(ll v = 0) : value(v) {
  }
  ModDouble(ll a, ld e) : value(powl(a, e)) {
  }
  ModDouble(ModDouble a, ld e) : value(powl(a.value, e)) {
  }

  ModDouble& operator+=(ModDouble const& b) {
    value += b.value;
    return *this;
  }
  ModDouble& operator-=(ModDouble const& b) {
    value -= b.value;
    return *this;
  }
  ModDouble& operator*=(ModDouble const& b) {
    value = (ld) value * b.value;
    return *this;
  }

  ModDouble& operator/=(ModDouble const& b) {
    value = (ld) value / b.value;
    return *this;
  }
  friend ModDouble operator+(ModDouble a, ModDouble const b) {
    return a += b;
  }
  friend ModDouble operator-(ModDouble a, ModDouble const b) {
    return a -= b;
  }
  friend ModDouble operator-(ModDouble const a) {
    return 0 - a;
  }
  friend ModDouble operator*(ModDouble a, ModDouble const b) {
    return a *= b;
  }
  friend ModDouble operator/(ModDouble a, ModDouble const b) {
    return a /= b;
  }
  friend ostream& operator<<(ostream& os, ModDouble const& a) {
    return os << a.value;
  }
  friend bool operator==(ModDouble const& a, ModDouble const& b) {
    return a.value == b.value;
  }
  friend bool operator!=(ModDouble const& a, ModDouble const& b) {
    return a.value != b.value;
  }
  explicit operator ld() const {
    return value;
  }
  explicit operator int() const {
    return (int) value;
  }
};

struct ModFrac : Frac {

  // Frac value;
  //
  ModFrac() : Frac(0) {
  }
  ModFrac(ll v) : Frac(v) {
  }
  ModFrac(Frac v) : Frac(v) {
  }
  ModFrac(Frac a, int e) : Frac(1) {

    for (int i = 0; i < e; i++) {
      *this *= a;
    }

    for (int i = 0; i < -e; i++) {
      *this /= a;
    }
  }
};
