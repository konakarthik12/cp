#pragma once
#include "base.cpp"
#include "views.cpp"

template <int MOD = 998244353>
struct ModInt {
  int value;

  ModInt(ll v = 0) {
    value = v % MOD;
    if (value < 0) {
      value += MOD;
    }
  }
  ModInt(ModInt a, ll e) : value(1) {
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

  ModInt& operator+=(ModInt const& b) {
    value += b.value;
    if (value >= MOD) {
      value -= MOD;
    }
    return *this;
  }
  ModInt& operator-=(ModInt const& b) {
    value -= b.value;
    if (value < 0) {
      value += MOD;
    }
    return *this;
  }
  ModInt& operator*=(ModInt const& b) {
    value = (ll) value * b.value % MOD;
    return *this;
  }

  friend ModInt inverse(ModInt a) {
    return ModInt(a, MOD - 2);
  }

  ModInt& operator/=(ModInt const& b) {
    return *this *= inverse(b);
  }
  friend ModInt operator+(ModInt a, ModInt const b) {
    return a += b;
  }
  friend ModInt operator-(ModInt a, ModInt const b) {
    return a -= b;
  }
  friend ModInt operator-(ModInt const a) {
    return 0 - a;
  }
  friend ModInt operator*(ModInt a, ModInt const b) {
    return a *= b;
  }
  friend ModInt operator/(ModInt a, ModInt const b) {
    return a /= b;
  }
  friend ostream& operator<<(ostream& os, ModInt const& a) {
    return os << a.value;
  }
  friend bool operator==(ModInt const& a, ModInt const& b) {
    return a.value == b.value;
  }
  friend bool operator!=(ModInt const& a, ModInt const& b) {
    return a.value != b.value;
  }
  explicit operator int() {
    return value;
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

template <int MOD>
void __read(ModInt<MOD>& x) {
  cin >> x.value;
  x.value %= MOD;
}
