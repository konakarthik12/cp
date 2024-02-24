#pragma once
#include "concepts.cpp"
#include "pr.cpp"
#include "wrapper.h"
using ll = long long;

using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

using pii = pr<int, int>;
using pdd = pr<double, double>;
using pcc = pr<char, char>;
using pci = pr<char, char>;
using pll = pr<ll, ll>;
using pill = pr<int, ll>;
using plli = pr<ll, int>;
using mii = map<int, int>;
using mll = map<ll, ll>;
using mill = map<int, ll>;
using mipii = map<int, pii>;
using mlli = map<ll, int>;
using mci = map<char, int>;
template <class T, class Compare = less<T>>
using pqueue = priority_queue<T, vector<T>, Compare>;
template <class T>
using vec = vector<T>;
using vi = vec<int>;
using mivi = map<int, vi>;
using vd = vec<double>;
using vll = vec<ll>;
using vpill = vec<pill>;
template <class T>
using vv = vec<vec<T>>;
template <class T>
using vvv = vec<vv<T>>;
using vvi = vv<int>;
using vvd = vv<double>;
using vvvi = vvv<int>;
using vvll = vv<ll>;
using vvc = vv<char>;
using vpii = vec<pii>;
using vpll = vec<pll>;
using vvpii = vv<pii>;
using vipll = vec<pll>;
using vvpll = vv<pll>;
using vc = vec<char>;
using vs = vec<string>;
using vpcc = vec<pcc>;
using str = string;
template <class T>
using mset = multiset<T>;
template <class T>
using uset = unordered_set<T>;
class Bool {
 public:
  Bool() : m_value() {
  }
  Bool(bool value) : m_value(value) {
  }

  operator bool() const {
    return m_value;
  }

  bool* operator&() {
    // the following operators are to allow bool* b = &v[0]; (v is a vector here).
    return &m_value;
  }
  const bool* operator&() const {
    return &m_value;
  }
  friend istream& operator>>(istream& in, Bool& b) {
    char c;
    in >> c;
    b.m_value = c == '1';
    return in;
  }
  friend std::ostream& operator<<(std::ostream& os, const Bool& b) {
    os << b.m_value;
    return os;
  }

 private:
  bool m_value;
};

using vb = vec<Bool>;
using vvb = vv<Bool>;

#define sz(x) (int) size(x)
#define pb(x) push_back(x);
#define eb(...) emplace_back(__VA_ARGS__);
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define fir first
#define sec second
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
