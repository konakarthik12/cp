#pragma once
#include "../scaffold.cpp"

struct Bool {
  // why does c++ specialize vector<bool> :pepehands:
  bool v;
  Bool() : v() {
  }
  Bool(bool value) : v(value) {
  }
  Bool& operator=(const bool value) {
    v = value;
    return *this;
  }
  operator bool() const {
    return v;
  }

  bool* operator&() {
    return &v;
  }
  const bool* operator&() const {
    return &v;
  }
  friend istream& operator>>(istream& in, Bool& b) {
    char c;
    in >> c;
    b.v = c == '1';
    return in;
  }
  friend ostream& operator<<(ostream& os, const Bool& b) {
    os << b.v;
    return os;
  }

  Bool& operator|=(const Bool& other) {
    v |= other.v;
    return *this;
  }

  Bool& operator|=(bool value) {
    v |= value;
    return *this;
  }
};

template <typename T>
struct NotBool {
  using type = T;
};

template <>
struct NotBool<bool> {
  using type = Bool;
};

template <typename T>
using NotBool_t = NotBool<T>::type;

template <>
struct is_integral_helper<Bool> : std::true_type {};

template <>
struct is_integral_helper<const Bool> : std::true_type {};

template <>
struct std::common_type<Bool, long long> {
  using type = long long;
};

template <>
struct std::common_type<long long, Bool> {
  using type = long long;
};

template <>
struct sum_type<Bool> {
  using type = int;
};
