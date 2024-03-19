#pragma once
#include "base.cpp"
#include "concepts.cpp"

template <typename T>
  enable_if_t<Printable<T>::value> __print(T x) {
  cout << x;
}
void println() {
  __print('\n');
}

template <typename Arg, typename... Args>
void print(Arg&& arg, Args&&... args) {
  __print(arg);
  if cexp (sizeof...(args) > 0) {
    __print(' ');
    print(args...);
  }
}

template <typename Container>
enable_if_t<HasIter<Container>::value> printsp(Container v) {
  for (auto iter = v.begin(); iter != v.end(); iter++) {
    __print(*iter);
    __print(' ');
  }
}

template <typename Container>
enable_if_t<(!Printable<Container>::value && HasIter<Container>::value)> println(Container v) {
  for (auto iter = v.begin(); iter != v.end(); iter++) {
    __print(*iter);
    if (next(iter) != v.end()) __print(' ');
  }
  __print('\n');
}

template <typename... Args>
void printsp(Args&&... args) {
  print(args...);
  print(' ');
}
template <typename... Args>
void println(Args&&... args) {
  print(args...);
  print('\n');
}

void flush() {
  cout.flush();
}
