#pragma once

#include "concepts.cpp"
#include "input.cpp"
#include "output.cpp"
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
void handle_print(Res& res) {
  println(res);
}


template <typename Func>
enable_if_t<is_same_v<invoke_result_t<Func>, void>> call_print(Func func) {
  std::invoke(func);
}

template <typename Func>
enable_if_t<!is_same_v<invoke_result_t<Func>, void>> call_print(Func func) {
  auto result = std::invoke(func);
  handle_print(result);
}

template <typename Func>
enable_if_t<is_same_v<invoke_result_t<Func, int>, void>> call_print(Func func, int t) {
  std::invoke(func, t);
}

template <typename Func>
enable_if_t<!is_same_v<invoke_result_t<Func, int>, void>> call_print(Func func, int t) {
  auto result = std::invoke(func, t);
  handle_print(result);
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
enable_if_t<is_invocable_v<Func>, void> handle_solve(Func func) {
  call_print(func);
}

// Second handle_solve function
template <typename Func, typename = void>
enable_if_t<is_invocable_v<Func, int>> handle_solve(Func func) {
  int qrs;
  read(qrs);
  for (int i = 0; i < qrs; i++) {
    call_print(func, i);
  }
}

void init_main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(ios_base::failbit);
  cout << fixed << setprecision(15);
}

// ********************************************** ACTUAL CODE STARTS HERE **********************************************
#include "include_wrap.cpp"
// **********************************************  ACTUAL CODE ENDS HERE  **********************************************

#ifndef NO_MAIN

int main() {
  init_main();
#ifndef EDITOR
  handle_solve(solve);
#endif
  cout.flush();
  return 0;
}

#endif
