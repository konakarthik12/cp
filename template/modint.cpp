#pragma once
#include "base.cpp"

template <typename T>
struct ModIntBase {
  int value;

  bool operator==(const T& b) const {
    return value == b.value;
  }
  bool operator!=(const T& b) const {
    return value != b.value;
  }
  explicit operator int() const {
    return value;
  }
  friend T operator+(T a, T const b) {
    return a += b;
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
    if (value < 0) {
      value += MOD;
    }
  }
  ModInt(ModInt a, ll e) {
    value = 1;
    while (e) {
      if (e & 1) {
        *this *= a;
      }
      a *= a;
      e >>= 1;
    }
  }

  ModInt(ll a, ll e) : ModInt(ModInt(a), e) {
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

struct ModDouble {
  ld value;

  ModDouble(ll v = 0) : value(v) {
  }
  ModDouble(ll a, ld e) : value(powl(a, e)) {
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
  explicit operator ld() {
    return value;
  }
};
