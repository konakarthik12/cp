#pragma once
#ifdef PREPROCESS
#include "alias.pre.cpp"
#else
#include "basic/vec.cpp"
#include "basic/wec.cpp"
#include "pr.cpp"
#include "wrapper.h"

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

using si = set<int>;
template <typename T>
using opt = optional<T>;

template <class T, class Compare = less<T> >
using pqueue = priority_queue<T, vector<T>, Compare>;

template <class T>
using vv = vec<vec<T> >;
template <class T>
using vvv = vec<vv<T> >;
using vvvi = vvv<int>;
using vvll = vv<ll>;
using str = string;
template <class T>
using mset = multiset<T>;
template <class T>
using uset = unordered_set<T>;

template <typename T>
using ww = wec<wec<T> >;
using wwi = ww<int>;

#define GENERATE_SINGLE(LEFT, RIGHT) \
  using v##LEFT = vec<RIGHT>;        \
  using vv##LEFT = vv<RIGHT>;        \
  using w##LEFT = wec<RIGHT>;

GENERATE_SINGLE(i, int)
GENERATE_SINGLE(ll, ll)
GENERATE_SINGLE(c, char)
GENERATE_SINGLE(d, double)
GENERATE_SINGLE(b, bool)
GENERATE_SINGLE(s, str)

#define GENERATE_AB(LEFT, RIGHT_A, RIGHT_B) \
  using m##LEFT = map<RIGHT_A, RIGHT_B>;    \
  using p##LEFT = pr<RIGHT_A, RIGHT_B>;

GENERATE_AB(ii, int, int)
GENERATE_AB(dd, double, double)
GENERATE_AB(cc, char, char)
GENERATE_AB(ll, ll, ll)

GENERATE_AB(ill, int, ll)
GENERATE_AB(lli, ll, int)
GENERATE_AB(ci, char, int)

using mivi = map<int, vi>;
using mipii = map<int, pii>;

using vpll = vec<pll>;
using vpill = vec<pill>;

using vipll = vec<pill>;
using vvpll = vv<pll>;

using vpii = vec<pii>;
using vpcc = vec<pcc>;

using vvpii = vv<pii>;
using wpii = wec<pii>;
using wwpii = ww<pii>;
#endif
