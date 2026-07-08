#pragma once
#ifdef PREPROCESS
#include "alias.pre.cpp"
#else
#include "basic/all.cpp"

using ll = long long;
using lll = __int128;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

using strvw = std::string_view;

template <typename T>
using vv = vec<vec<T>>;
template <typename T>
using vw = vec<wec<T>>;

template <typename T>
using wv = wec<vec<T>>;

template <typename T>
using ww = wec<wec<T>>;
template <typename T>
using wvv = wec<vv<T>>;

template <typename T>
using vww = vec<ww<T>>;

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
GENERATE_SINGLE(s, str_raw<1>)

#define GENERATE_AB(LEFT, RIGHT_A, RIGHT_B)         \
  using m##LEFT = map<RIGHT_A, RIGHT_B>;            \
  using um##LEFT = umap<RIGHT_A, RIGHT_B>;          \
  using p##LEFT = pr<RIGHT_A, RIGHT_B>;             \
  using vp##LEFT = vec<pr<RIGHT_A, RIGHT_B>>;       \
  using wp##LEFT = wec<pr<RIGHT_A, RIGHT_B>>;       \
  using vvp##LEFT = vec<vec<pr<RIGHT_A, RIGHT_B>>>; \
  using vwp##LEFT = vec<wec<pr<RIGHT_A, RIGHT_B>>>; \
  using wvp##LEFT = wec<vec<pr<RIGHT_A, RIGHT_B>>>; \
  using wwp##LEFT = ww<pr<RIGHT_A, RIGHT_B>>;

GENERATE_AB(ii, int, int)
GENERATE_AB(dd, double, double)
GENERATE_AB(cc, char, char)
GENERATE_AB(ll, ll, ll)
GENERATE_AB(bb, bool, bool)

GENERATE_AB(ill, int, ll)
GENERATE_AB(lli, ll, int)
GENERATE_AB(ci, char, int)
GENERATE_AB(ic, int, char)
GENERATE_AB(ib, int, bool)
GENERATE_AB(di, double, int)

using mpii = map<pii, pii>;
using mivi = map<int, vi>;
using miwi = map<int, wi>;
using mipii = map<int, pii>;

using vipll = vec<pill>;
template <typename T>
using www = wec<ww<T>>;
using wwwi = www<int>;
template <typename T>
using vvv = vec<vv<T>>;
using vvvi = vvv<int>;
using vpcc = vec<pcc>;

template <typename T>
using opt = std::optional<T>;
using si = set<int>;
using sd = set<double>;
using sll = set<ll>;
using spii = set<pii>;

using msi = mset<int>;
#endif
