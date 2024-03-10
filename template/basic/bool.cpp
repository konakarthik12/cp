#pragma once
#include "../wrapper.h"
struct Bool {
  // why does c++ specialize vector<bool> :pepehands:
  bool m;
  Bool() : m() {
  }
  Bool(bool value) : m(value) {
  }

  operator bool() const {
    return m;
  }

  bool* operator&() {
    return &m;
  }
  const bool* operator&() const {
    return &m;
  }
  friend istream& operator>>(istream& in, Bool& b) {
    char c;
    in >> c;
    b.m = c == '1';
    return in;
  }
  friend std::ostream& operator<<(std::ostream& os, const Bool& b) {
    os << b.m;
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