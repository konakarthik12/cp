#pragma once
#include "concepts.cpp"
#include "scaffold.cpp"
ostream* dout = &cerr;
template <typename Container>
  requires(HasValueType1D<Container> && HasIter<Container> && !Printable<Container>)
void debug(Container v);

template <typename T>
concept Debuggable = requires(T t) {
  { t.debug() } -> std::same_as<void>;
};

template <typename T>
  requires (Printable<T> && !Debuggable<T>)
void debug(T x) {
  *dout << x;
}


template <Debuggable T>
void debug(T& x) {
  x.debug();
}

void debug_all() {
}

template <typename Arg, typename... Args>
void debug_all(Arg&& arg, Args&&... args);
#ifdef __JETBRAINS_IDE__
#define LOCAL
#endif
#ifdef LOCAL
// #define BACKWARD_HAS_BFD 1
// #include "lib/backward.hpp"
#include "execinfo.h"
#define deb(...) logger(__LINE__, false, #__VA_ARGS__, ##__VA_ARGS__);
#define deb_n(...) logger(__LINE__, true, #__VA_ARGS__, ##__VA_ARGS__);
template <typename... Args>
void logger(int line, bool nest, string vars, Args&&... values) {
  if (vars.size() == 0) {
    *dout << "\n";
    return;
  }
  if (nest) {
    void* callstack[20];
    int frames = backtrace(callstack, 20);
    for (int i = 4; i < frames; i++) {
      *dout << "  ";
    }
  }
  *dout << "\033[30;1m" << line << ": ";
  *dout << vars << " = ";
  debug_all(values...);
  *dout << "\033[0m\n";
}
#ifndef NO_MAIN
#include <cpptrace/cpptrace.hpp>
void dssert(bool res, string msg = "") {
  if (res) return;
  if (msg.size() > 0) {
    cerr << msg << "\n";
  }
  cpptrace::generate_trace().print();
  exit(0);
  // std::cout << std::stacktrace::current();
}
#endif
// #define dssert(...) pssert(__VA_ARGS__);
__attribute__((unused)) const bool prod = false;
#else
__attribute__((unused)) const bool prod = true;
#define dssert(...) (void) 0;
#define deb(...) (void) 0;
#endif
