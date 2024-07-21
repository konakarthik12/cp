#pragma once
#ifdef PREPROCESS
#include "alias.pre.cpp"
#else
#include "basic/all.cpp"
#include "scaffold.cpp"

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

using str = std::string;

template <class T, class Compare = less<T>, class Container = std::vector<T>>
using pqueue = std::priority_queue<T, Container, Compare>;

template <typename T>
using vv = vec<vec<T>>;
template <typename T>
using vw = vec<wec<T>>;

template <typename T>
using wv = wec<vec<T>>;

template <typename T>
using ww = wec<wec<T>>;

#define GENERATE_SINGLE(LEFT, RIGHT) \
  using v##LEFT = vec<RIGHT>;        \
  using w##LEFT = wec<RIGHT>;        \
  using vv##LEFT = vv<RIGHT>;        \
  using vw##LEFT = vw<RIGHT>;        \
  using wv##LEFT = wv<RIGHT>;        \
  using ww##LEFT = ww<RIGHT>;

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
GENERATE_AB(bb, bool, bool)

GENERATE_AB(ill, int, ll)
GENERATE_AB(lli, ll, int)
GENERATE_AB(ci, char, int)
GENERATE_AB(ic, int, char)

GENERATE_SINGLE(pii, pii)

using mpii = map<pii, pii>;
using mivi = map<int, vi>;
using mipii = map<int, pii>;

using vpll = vec<pll>;
using vpill = vec<pill>;

using vipll = vec<pill>;
using vvpll = vv<pll>;
template <typename T>
using www = wec<ww<T>>;
using wwwi = www<int>;
using vpcc = vec<pcc>;

template <typename T>
using opt = std::optional<T>;
using si = set<int>;
using msi = mset<int>;

using spii = set<pii>;
#endif
