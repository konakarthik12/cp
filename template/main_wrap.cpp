#define pragma once

#include "base.cpp"
#include "concepts.cpp"
#include "input.cpp"
#include "output.cpp"

template <typename Func>
  requires requires(Func func) {
    { std::invoke_result_t<Func>() } -> std::same_as<void>;
  }
void call_print(Func func) {
  std::invoke(func);
}

template <typename Func>
  requires requires(Func func) {
    { std::invoke_result_t<Func>() } -> std::movable;
  }
void call_print(Func func) {
  auto result = std::invoke(func);
  println(result);
}

template <typename Func>
  requires requires(Func func, int t) {
    { std::invoke_result_t<Func, int>() } -> std::same_as<void>;
  }
void call_print(Func func, int t) {
  std::invoke(func, t);
}

template <typename Func>
  requires requires(Func func, int t) {
    { std::invoke_result_t<Func, int>() } -> std::movable;
  }
void call_print(Func func, int t) {
  auto result = std::invoke(func, t);
  println(result);
}

template <class F>
struct y_comb {
  F f;

  template <class... Args>
  decltype(auto) operator()(Args&&... args) const {
    return f(*this, std::forward<Args>(args)...);
  }
};

template <typename Func>
  requires requires(Func func) {
    { std::invoke_result_t<Func>() };
  }
void handle_solve(Func func) {
  call_print(func);
}

template <typename Func, typename... Args>
  requires requires(Func func) {
    { std::invoke_result_t<Func, int>() };
  }
void handle_solve(Func func) {
  int qrs;
  read(qrs);
  for (int i = 0; i < qrs; i++) {
    call_print(func, i);
  }
}

#include "include_wrap.cpp"

#ifndef NO_MAIN

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(15);
#ifndef EDITOR
  handle_solve(solve);
#endif
  cout.flush();
  return 0;
}

#endif
