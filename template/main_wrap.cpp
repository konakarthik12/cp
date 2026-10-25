#pragma once

#include "concepts.cpp"
#include "input.cpp"
#include "output.cpp"
#include "deb.cpp"
#include "keyboard.cpp"
int test_cases = -1;
int test_case;
template <typename Res>
void handle_print(optional<Res>& res) {
  if (res) {
    println("YES");
    println(*res);
  } else {
    println("NO");
  }
}
template <typename Res>
void handle_print(optional<Res>&& res) {
  handle_print(res);
}
template <typename Res>
void handle_print(Res&& res) {
  println(res);
}
template <typename Func>
  requires requires(Func func) {
    { invoke_result_t<Func>() } -> same_as<void>;
  }
void call_print(Func func) {
  invoke(func);
}

template <typename Func>
  requires requires(Func func) {
    { invoke_result_t<Func>() } -> movable;
  }
void call_print(Func func) {
  auto result = invoke(func);
  handle_print(result);
}

template <typename Func>
  requires requires(Func func, int t) {
    { invoke_result_t<Func, int>() } -> same_as<void>;
  }
void call_print(Func func, int t) {
  invoke(func, t);
}

template <typename Func>
  requires requires(Func func, int t) {
    { invoke_result_t<Func, int>() } -> movable;
  }
void call_print(Func func, int t) {
  auto result = invoke(func, t);
  handle_print(result);
}

template <typename Func>
  requires requires(Func func) {
    { invoke_result_t<Func>() };
  }
void handle_solve(Func func) {
  call_print(func);
}

template <typename Func, typename... Args>
  requires requires(Func func) {
    { invoke_result_t<Func, int>() };
  }
void handle_solve(Func func) {
  read(test_cases);
  for (test_case = 1; test_case <= test_cases; test_case++) {
    call_print(func, test_case);
  }
}

void init_main() {
  cin.tie(0)->sync_with_stdio(false);
#ifdef LOCAL
  cin.exceptions(ios_base::failbit);
#endif
  cout << fixed << setprecision(15);
}

template <typename T = void>
void init() {
}

// ********************************************** ACTUAL CODE STARTS HERE **********************************************
#include "include_wrap.cpp"
// **********************************************  ACTUAL CODE ENDS HERE  **********************************************

#ifndef NO_MAIN

int main() {
  init_main();
#ifndef EDITOR
  init();
  handle_solve(solve);
#endif
  return 0;
}

#endif
