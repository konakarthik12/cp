#pragma once
#include "../entry.cpp"
#include "con.cpp"
#include "bool.cpp"
#include "wec.cpp"

template <typename T>
struct stack : public wec<T> {
  using wec<T>::wec;

  void push(T value) {
    this->pb(value);
  }
  auto pop() {
    return this->rb();
  }



  auto& top() {
    return this->v.back();
  }

  auto& top() const {
    return this->v.back();
  }



};
