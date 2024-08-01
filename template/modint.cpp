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
    return a /= b;
  }
  friend T operator-(T const a) {
    return 0 - a;
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
  istream& operator>>(istream& is) {
    is >> value;
    value %= MOD;
    return is;
  }
};

struct DynModInt : public ModIntBase<DynModInt> {
  int mod;

  DynModInt(int mod, ll v = 0) : mod(mod) {
    value = v % mod;
    if (value < 0) {
      value += mod;
    }
  }

  DynModInt(DynModInt a, ll e) : mod(a.mod) {
    value = 1;
    while (e) {
      if (e & 1) {
        *this *= a;
      }
      a *= a;
      e >>= 1;
    }
  }

  DynModInt(ll a, ll e, int mod) : DynModInt(DynModInt(mod, a), e) {
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
  istream& operator>>(istream& is) {
    is >> value;
    value %= mod;
    return is;
  }
};

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
    value = (ll) value * b.value;
    return *this;
  }

  ModDouble& operator/=(ModDouble const& b) {
    value = (ll) value / b.value;
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
