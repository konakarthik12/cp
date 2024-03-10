#pragma once
#include "base.cpp"
#include "pr.cpp"
template <const unsigned long N>
void debug(ostream& out, typename bitset<N>::reference v) {
  out << (bool) v;
}

template <const unsigned long N>
void debug(ostream& out, bitset<N> b) {
  out << b;
}
void debug(ostream& out, char i) {
  out << i;
}
void debug(ostream& out, int i) {
  out << i;
}
void debug(ostream& out, uint i) {
  out << i;
}
void debug(ostream& out, ll i) {
  out << i;
}
void debug(ostream& out, ull i) {
  out << i;
}
void debug(ostream& out, string s) {
  out << s;
}

template <typename T, typename V>
void debug(ostream& out, pair<T, V> const& p) {

  out << '(' << p.first << ", " << p.second << ')';
}

template <typename T, typename V>
void debug(ostream& out, pr<T, V> const& p) {
  out << '(' << p.f << ", " << p.s << ')';
}

template <typename T, typename V, typename U>
void debug(ostream& out, priority_queue<T, V, U> p) {
  vector<T> v;
  while (!p.empty()) {
    v.pb(p.top());
    p.pop();
  }
  debug(out, v);
}
template <typename Container>
  requires HasValueType1D<Container>
void debug(ostream& os, Container v) {
  os << '[';
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      os << ", ";
    }
    debug(os, *it);
  }
  os << ']';
}

template <typename Container>
  requires HasValueType2D<Container>
void debug(ostream& out, Container v) {
  out << "\n[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      out << ",\n ";
    }
    debug(out, *it);
  }
  out << ']';
}

void debug_all(ostream&) {
}
template <typename Arg, typename... Args>
void debug_all(ostream& out, Arg&& arg, Args&&... args) {
  debug(out, arg);
  if (sizeof...(args) > 0) {
    out << ", ";
  }
  debug_all(out, args...);
}
#ifdef __JETBRAINS_IDE__
#define LOCAL
#endif
#ifdef LOCAL
#include "execinfo.h"
#define deb(...) logger(cerr, __LINE__, false, #__VA_ARGS__, ##__VA_ARGS__);
#define deb_n(...) logger(cerr, __LINE__, true, #__VA_ARGS__, ##__VA_ARGS__);
template <typename... Args>
void logger(ostream& out, int line, bool nest, string vars, Args&&... values) {
  if (vars.size() == 0) {
    out << "\n";
    return;
  }
  if (nest) {
    void* callstack[20];
    int frames = backtrace(callstack, 20);
    for (int i = 4; i < frames; i++) {
      out << "  ";
    }
  }
  out << "\033[30;1m" << line << ": ";
  out << vars << " = ";
  debug_all(out, values...);
  //  logger(out, line, nest, vars, forward<Args>(values)...)
  //  (..., (out << delim << values, delim = ", "));
  out << "\033[0m\n";
}
#define dssert(...) assert(__VA_ARGS__);
__attribute__((unused)) const bool prod = false;
#else
__attribute__((unused)) const bool prod = true;
#define dssert(...) (void) 0;
#define deb(...) (void) 0;
#endif
