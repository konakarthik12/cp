#pragma once
#include "../scaffold.cpp"

struct Bool {
  // why does c++ specialize vector<bool> :pepehands:
  bool v;
  Bool() : v() {
  }
  Bool(bool value) : v(value) {
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


