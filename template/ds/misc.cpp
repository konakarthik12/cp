#pragma once

#include "../base.cpp"
template <typename T, typename V = T>
struct FunStack {
  using Comp = std::function<V(const T&, const T&)>;
  Comp op;
  stack<pr<T, T>> st;
  FunStack(Comp op) : op(op) {
  }

  void push(T x) {
    if (st.empty()) st.emplace(x, x);
    else st.emplace(x, op(st.top().s, x));
  }

  T pop() {
    T top = st.top().f;
    st.pop();
    return top;
  }

  V score() {
    return st.top().s;
  }
  operator bool() {
    return st.size() > 0;
  }
  int size() const {
    return st.size();
  }
};

template <typename T, typename V = T>
struct FunQueue {
  using Comp = std::function<V(const T&, const T&)>;
  Comp op;

  FunStack<T> s1, s2;

  FunQueue(Comp op) : op(op), s1(op), s2(op) {};

  void push(T x) {
    s1.push(x);
  }

  T pop() {
    if (!s2) {
      while (s1) s2.push(s1.pop());
    }
    return s2.pop();
  }

  V score() {
    if (!s1) return s2.score();
    if (!s2) return s1.score();
    return op(s1.score(), s2.score());
  }
  int size() const {
    return s1.size() + s2.size();
  }
};
