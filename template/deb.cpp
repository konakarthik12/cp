#pragma once
#include "base.cpp"

ostream* dout = &cerr;

template <const unsigned long N>
void debug(typename bitset<N>::reference v) {
  *dout << (bool) v;
}

template <const unsigned long N>
void debug(bitset<N> b) {
  *dout << b;
}
template <typename T>
enable_if_t<Printable<T>::value> debug(T x) {
  *dout << x;
}

template <typename T, typename V>
void debug(pair<T, V> const& p) {
  *dout << '(';
  debug(p.first);
  *dout << ", ";
  debug(p.second);
  *dout << ')';
}

template <typename T, typename V>
void debug(pr<T, V> const& p) {
  *dout << '(';
  debug(p.f);
  *dout << ", ";
  debug(p.s);
  *dout << ')';
}

template <typename T, typename V, typename U>
void debug(pqueue<T, V, U> p) {
  vec<T> v;
  while (!p.empty()) {
    v.pb(p.top());
    p.pop();
  }
  debug(dout, v);
}
template <typename Container>
enable_if_t<HasValueType1D<Container>::value && !Printable<Container>::value> debug(Container v) {
  *dout << '[';
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      *dout << ", ";
    }
    debug(*it);
  }
  *dout << ']';
}

template <typename Container>
enable_if_t<HasValueType2D<Container>::value> debug(Container v) {
  *dout << "\n[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      *dout << ",\n ";
    }
    debug(*it);
  }
  *dout << ']';
}

void debug_all() {
}
template <typename Arg, typename... Args>
void debug_all(Arg&& arg, Args&&... args) {
  debug(arg);
  if (sizeof...(args) > 0) {
    *dout << ", ";
  }
  debug_all(args...);
}
#ifdef __JETBRAINS_IDE__
#define LOCAL
#endif
#ifdef LOCAL
#include "execinfo.h"
#define deb(...) logger(__LINE__, false, #__VA_ARGS__, ##__VA_ARGS__);
#define deb_n(...) logger(__LINE__, true, #__VA_ARGS__, ##__VA_ARGS__);
template <typename... Args>
void logger(int line, bool nest, str vars, Args&&... values) {
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
  //  logger(*dout, line, nest, vars, forward<Args>(values)...)
  //  (..., (*dout << delim << values, delim = ", "));
  *dout << "\033[0m\n";
}
#define dssert(...) assert(__VA_ARGS__);
__attribute__((unused)) const bool prod = false;
#else
__attribute__((unused)) const bool prod = true;
#define dssert(...) (void) 0;
#define deb(...) (void) 0;
#endif