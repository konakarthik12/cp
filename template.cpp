#include "wrapper.h"
using namespace std;
using ll = long long;
using uint = unsigned int;
template <class T1, class T2>
struct Pair {
  T1 f;
  T2 s;
  // cpp 17 needs constructor
  Pair(T1 f, T2 s) {
    this->f = f;
    this->s = s;
  }
  Pair(T1 x)
      : Pair(x, x) {
  }
  Pair()
      : Pair(T1(), T2()) {
  }
};
template <class T1, class T2>
bool operator<(const Pair<T1, T2>& x, const Pair<T1, T2>& y) {
  return std::tie(x.f, x.s) < std::tie(y.f, y.s);
}
template <class T1, class T2>
using pr = Pair<T1, T2>;
using pii = pr<int, int>;
using pdd = pr<double, double>;
using pll = pair<ll, ll>;
using mii = map<int, int>;
template <class T, class Compare = less<T>>
using pqueue = priority_queue<T, vector<T>, Compare>;
template <class T>
using vec = vector<T>;
using vi = vec<int>;
using vd = vec<double>;
using vll = vec<ll>;
template <class T>
using vv = vec<vec<T>>;
using vvi = vv<int>;
using vvc = vv<char>;
using vpii = vec<pii>;
using vvpii = vv<pii>;
using vpll = vec<pll>;
using vvpll = vv<pll>;
using vc = vec<char>;
using str = string;
template <class T>
using mset = multiset<T>;
template <class T>
using uset = unordered_set<T>;
class Bool {
 public:
  Bool()
      : m_value() {
  }
  Bool(bool value)
      : m_value(value) {
  }

  operator bool() const {
    return m_value;
  }

  // the following operators are to allow bool* b = &v[0]; (v is a vector here).
  bool* operator&() {
    return &m_value;
  }
  const bool* operator&() const {
    return &m_value;
  }
  friend istream& operator>>(istream& in, Bool& b) {
    in >> b.m_value;
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
#define pb(x) push_back(x);
#define eb(...) emplace_back(__VA_ARGS__);
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define fir first
#define sec second

mt19937 rng(random_device());

template <typename T>
int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}
template <typename T>
T ceil_div(T a, T b) {
  return (a + b - 1) / b;
}
template <typename T, typename V>
ostream& operator<<(ostream& out, pair<T, V> const& p) {
  out << '(' << p.first << ", " << p.second << ')';
  return out;
}
template <typename T, typename V>
ostream& operator<<(ostream& out, Pair<T, V> const& p) {
  out << '(' << p.f << ", " << p.s << ')';
  return out;
}
template <typename Ostream, typename T>
typename enable_if<is_same<Ostream, ostream>::value, Ostream&>::type operator<<(Ostream& os, const T* v) {
  os << *v;
}

template <typename Ostream, typename T>
typename enable_if<is_same<Ostream, ostream>::value, Ostream&>::type operator<<(Ostream& os, const T& v) {
  os << '[';
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      os << ", ";
    }
    os << *it;
  }
  return os << ']';
}
template <typename A, typename B, typename C>
ostream& operator<<(ostream& os, priority_queue<A, B, C>& v) {
  vec<A> items;
  while (!v.empty()) {
    items.pb(v.top());
    v.pop();
  }
  for (auto item: items) {
    v.push(item);
  }
  return os << items;
}
template <typename T>
ostream& operator<<(ostream& os, stack<T>& v) {
  vec<T> items;
  while (!v.empty()) {
    items.pb(v.top());
    v.pop();
  }
  for (auto item: items) {
    v.push(item);
  }
  reverse(all(items));
  return os << items;
}
template <size_t I = 0, typename... Tp>
ostream& operator<<(ostream& out, tuple<Tp...> const& t) {
  constexpr bool first = I == 0;
  constexpr bool last = I == sizeof...(Tp);
  constexpr bool middle = !first && !last;
  if constexpr (first) {
    out << '(';
  } else if constexpr (middle) {
    out << ", ";
  }

  if constexpr (middle) {
    out << get<I>(t);
    operator<< <I + 1>(out, t);
  } else if constexpr (last) {
    out << ')';
  }

  return out;
}
#ifdef LOCAL
#include "execinfo.h"
#define deb(...) logger(cerr, __LINE__, false, #__VA_ARGS__, ##__VA_ARGS__);
template <typename... Args>
void logger(ostream& out, int line, bool nest, string vars, Args&&... values) {
  if (sz(vars) == 0) {
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
  string delim = "";
  (..., (out << delim << values, delim = ", "));
  out << "\033[0m\n";
}
#else
#define deb(...) (void) 0;
#endif
template <typename T, typename V>
istream& operator>>(istream& in, Pair<T, V>& p) {
  in >> p.f >> p.s;
  return in;
}
template <size_t N>
istream& operator>>(istream& in, bitset<N>& b) {
  ll num;
  in >> num;
  b = num;
  return in;
}
template <class... Args>
void read(Args&... args) {
  (..., (cin >> args));
}
int readInt() {
  int x;
  read(x);
  return x;
}
template <class T>
void read(T arr[], int n) {
  for (int i = 0; i < n; i++) {
    read(arr[i]);
  }
}

template <class T>
void read(vec<T>& v, int n) {
  v.reserve(v.size() + n);
  for (int i = 0; i < n; i++) {
    T temp;
    read(temp);
    v.push_back(temp);
  }
}
template <class T>
void read(set<T>& v, int n) {
  for (int i = 0; i < n; i++) {
    T temp;
    read(temp);
    v.insert(temp);
  }
}
template <class T>
void read1(vec<T>& v, int n) {
  v.pb(0);
  read(v, n);
}
template <class T>
void read(vv<T>& arr, int n, int m) {
  arr.reserve(arr.size() + n);
  for (int i = 0; i < n; i++) {
    arr.emplace_back();
    arr[i].reserve(m);
    for (int j = 0; j < m; j++) {
      T x;
      read(x);
      arr[i].push_back(x);
    }
  }
}
template <class T>
void read1(vv<T>& arr, int n, int m) {
  arr.reserve(arr.size() + n + 1);
  arr.emplace_back(m + 1);
  for (int i = 0; i < n; i++) {
    arr.emplace_back();
    arr.back().reserve(m + 1);
    arr.back().pb(0);
    for (int j = 0; j < m; j++) {
      T x;
      read(x);
      arr.back().push_back(x);
    }
  }
}

template <class... Args>
void print(Args... args) {
  string delim = "";
  (..., (cout << delim << args, delim = " "));
}

template <class... Args>
void printsp(Args... args) {
  print(args...);
  cout << " ";
}
template <typename ForwardIt>
void printsp(ForwardIt first, ForwardIt last) {
  for (auto it = first; it != last; it++) {
    printsp(*it);
  }
}

template <class... Args>
void println(Args... args) {
  print(args...);
  cout << "\n";
}
void flush() {
  cout.flush();
}

const double pi = acos(-1);

double to_rad(double degrees) {
  return degrees * (pi / 180);
}
template <class Container>
void dedupe(Container& vec) {
  vec.erase(unique(all(vec)), vec.end());
}
template <class Container>
void sort(Container& vec) {
  sort(all(vec));
}
template <class Container, class Comp>
void sort(Container& vec, Comp comp) {
  sort(all(vec), comp);
}
template <class T>
void swapsort(T& a, T& b) {
  if (a > b) {
    swap(a, b);
  }
}
template <class Container>
void erase_all(Container& vec, char c) {
  vec.erase(remove(all(vec), c), vec.end());
}
template <typename T>
ll sum(T start, T end) {
  ll total = 0;
  for (auto i = start; i < end; i++) {
    total += *i;
  }
  return total;
}

ll asum(ll a) {
  return (a + 1) * a / 2;
}
template <class Container>
ll sum(Container& vec) {
  return sum(all(vec));
}
template <typename T, typename V>
void prefix_sum(T* start, T* end, V* result) {
  ll cur = 0;
  *result++ = 0;
  for (int* i = start; i < end; i++) {
    cur += *i;
    *result++ = cur;
  }
}
template <class ForwardIt>
constexpr std::pair<typename std::iterator_traits<ForwardIt>::value_type,
                    typename std::iterator_traits<ForwardIt>::value_type>
lowhigh(ForwardIt first, ForwardIt last) {
  auto [low, high] = std::minmax_element(first, last);
  return {*low, *high};
}

template <int MOD = 998244353>
struct ModInt {
  int value;
  static const int MOD_value = MOD;

  ModInt(long long v = 0) {
    value = v % MOD;
    if (value < 0) {
      value += MOD;
    }
  }
  ModInt(long long a, long long b)
      : value(0) {
    *this += a;
    *this /= b;
  }

  ModInt& operator+=(ModInt const& b) {
    value += b.value;
    if (value >= MOD) {
      value -= MOD;
    }
    return *this;
  }
  ModInt& operator-=(ModInt const& b) {
    value -= b.value;
    if (value < 0) {
      value += MOD;
    }
    return *this;
  }
  ModInt& operator*=(ModInt const& b) {
    value = (long long) value * b.value % MOD;
    return *this;
  }

  friend ModInt inverse(ModInt a) {
    return mexp(a, MOD - 2);
  }

  ModInt& operator/=(ModInt const& b) {
    return *this *= inverse(b);
  }
  friend ModInt operator+(ModInt a, ModInt const b) {
    return a += b;
  }
  friend ModInt operator-(ModInt a, ModInt const b) {
    return a -= b;
  }
  friend ModInt operator-(ModInt const a) {
    return 0 - a;
  }
  friend ModInt operator*(ModInt a, ModInt const b) {
    return a *= b;
  }
  friend ModInt operator/(ModInt a, ModInt const b) {
    return a /= b;
  }
  friend istream& operator>>(istream& in, ModInt& a) {
    return in >> a.value;
  }
  friend std::ostream& operator<<(std::ostream& os, ModInt const& a) {
    return os << a.value;
  }
  friend bool operator==(ModInt const& a, ModInt const& b) {
    return a.value == b.value;
  }
  friend bool operator!=(ModInt const& a, ModInt const& b) {
    return a.value != b.value;
  }
};

template <int MOD>
ModInt<MOD> mexp(ModInt<MOD> a, long long e) {
  ModInt<MOD> res = 1;
  while (e) {
    if (e & 1) {
      res *= a;
    }
    a *= a;
    e >>= 1;
  }
  return res;
}

vi sieve(int max_n) {
  vi primes;
  vec<bool> is_prime(max_n + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;
  for (int i = 2; i <= max_n; i++) {
    if (is_prime[i] && (ll) i * i <= max_n) {
      for (int j = i * i; j <= max_n; j += i) {
        is_prime[j] = false;
      }
    }
  }
  for (int i = 2; i <= max_n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
  return primes;
}
template <typename T>
struct Combo {
  vec<T> fact;
  vec<T> inv_fact;
  Combo(int max_n) {
    fact.pb(1);
    inv_fact.pb(1);
    for (int i = 1; i <= max_n; i++) {
      fact.push_back(fact.back() * i);
      inv_fact.push_back(1 / fact.back());
    }
  }
  T choose(int n, int k) {
    if (n < k) {
      return 0;
    }
    return fact[n] * (inv_fact[k] * inv_fact[n - k]);
  }
  T permute(int n) {
    if (n < 0) {
      return 0;
    }
    return fact[n];
  }

  T permute(int n, int k) {
    if (n < k) {
      return 0;
    }
    return fact[n] * inv_fact[n - k];
  }
};
str yes(bool ans, str yes = "Yes", str no = "No") {
  return ans ? yes : no;
}
void exit() {
  exit(0);
}
void solve();
#ifndef NO_MAIN
int main() {
  cin.tie(0)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  solve();
  cout.flush();
  return 0;
}
#endif
