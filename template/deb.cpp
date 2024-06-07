#pragma once
#include "base.cpp"
ostream& dout = cerr;

template <typename Container>
  requires(HasValueType1D<Container> && !Printable<Container>)
void debug(Container v);
template <typename T, typename V>
void debug(pr<T, V> const& p);

template <const unsigned long N>
void debug(typename bitset<N>::reference v) {
  dout << (bool) v;
}

template <const unsigned long N>
void debug(bitset<N> b) {
  dout << b;
}
template <typename T>
  requires Printable<T>
void debug(T x) {
  dout << x;
}

template <typename T, typename V>
void debug(pair<T, V> const& p) {
  dout << '(';
  debug(p.first);
  dout << ", ";
  debug(p.second);
  dout << ')';
}

template <typename T, typename V>
void debug(pr<T, V> const& p) {
  dout << '(';
  debug(p.f);
  dout << ", ";
  debug(p.s);
  dout << ')';
}

template <size_t Index = 0, typename... Ts>
void tuple_debug(const tuple<Ts...>& t) {
  if constexpr (Index < sizeof...(Ts)) {
    if (Index != 0) dout << ", ";
    debug(get<Index>(t));
    tuple_debug<Index + 1>(dout, t);
  }
}

template <typename... Ts>
void debug(const tuple<Ts...>& t) {
  dout << "(";
  tuple_debug(t);
  dout << ")";
}

template <typename T, typename V, typename U>
void debug(priority_queue<T, V, U> p) {
  vector<T> v;
  while (!p.empty()) {
    v.pb(p.top());
    p.pop();
  }
  debug(v);
}

template <typename Container>
  requires(HasValueType1D<Container> && !Printable<Container>)
void debug(Container v) {
  dout << '[';
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      dout << ", ";
    }
    debug(*it);
  }
  dout << ']';
}

template <typename Container>
  requires HasValueType2D<Container>
void debug(Container v) {
  dout << "\n[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      dout << ",\n ";
    }
    debug(*it);
  }
  dout << ']';
}

void debug_all() {
}
template <typename Arg, typename... Args>
void debug_all(Arg&& arg, Args&&... args) {
  debug(arg);
  if (sizeof...(args) > 0) {
    dout << ", ";
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
void logger(int line, bool nest, string vars, Args&&... values) {
  if (vars.size() == 0) {
    dout << "\n";
    return;
  }
  if (nest) {
    void* callstack[20];
    int frames = backtrace(callstack, 20);
    for (int i = 4; i < frames; i++) {
      dout << "  ";
    }
  }
  dout << "\033[30;1m" << line << ": ";
  dout << vars << " = ";
  debug_all(values...);
  //  logger(dout, line, nest, vars, forward<Args>(values)...)
  //  (..., (dout << delim << values, delim = ", "));
  dout << "\033[0m\n";
}
#define dssert(...) assert(__VA_ARGS__);
__attribute__((unused)) const bool prod = false;
#else
__attribute__((unused)) const bool prod = true;
#define dssert(...) (void) 0;
#define deb(...) (void) 0;
#endif
