#include "wrapper.h"
using namespace std;
using std::numbers::pi;
using ll = long long;
using pii = pair<int, int>;
using pdd = pair<double, double>;
using pll = pair<ll, ll>;
using mii = map<int, int>;
template <class T, class Compare = less<T>>
using pqueue = priority_queue<T, vector<T>, Compare>;
template <class T>
using vec = vector<T>;
using vi = vec<int>;
template <class T>
using vv = vec<vec<T>>;
using vvi = vv<int>;
using vpii = vec<pii>;
using vvpii = vv<pii>;
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

 private:
  bool m_value;
};

using vb = vector<Bool>;
using vc = vec<char>;
using str = string;
template <class T>
using mset = multiset<T>;
template <class T>
using uset = unordered_set<T>;
template <class T>
using umset = unordered_multiset<T>;

#define sz(x) (int) size(x)
#define pb(x) push_back(x);
#define eb(...) emplace_back(__VA_ARGS__);
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define filla(x, v) memset(x, v, sizeof x);
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
#define deb(...) logger(cerr, __LINE__, false, #__VA_ARGS__, __VA_ARGS__);
template <typename... Args>
void logger(ostream& out, int line, bool nest, string vars, Args&&... values) {
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
#define deb(...) (void) 0
#endif
template <typename T, typename V>
istream& operator>>(istream& in, pair<T, V>& p) {
  in >> p.first >> p.second;
  return in;
}
template <class... Args>
void read(Args&... args) {
  (..., (cin >> args));
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
void read(vv<T>& arr, int n, int m) {
  arr.reserve(n);
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
template <class... Args>
void println(Args... args) {
  print(args...);
  cout << "\n";
}
double to_rad(double degrees) {
  return degrees * (pi / 180);
}
template <class Container>
void dedupe(Container& vec) {
  vec.erase(unique(all(vec)), vec.end());
}
template <class Container>
void erase_all(Container& vec, char c) {
  // vec.erase(remove(all(vec), c), prefix.end());
  vec.erase(remove(all(vec), c), vec.end());
}

void prefix_sum(int* start, int* end, ll* result) {
  ll cur = 0;
  *result++ = 0;
  for (int* i = start; i < end; i++) {
    cur += *i;
    *result++ = cur;
  }
}
template <int MOD>
struct Modular {
  int value;
  static const int MOD_value = MOD;

  Modular(long long v = 0) {
    value = v % MOD;
    if (value < 0) {
      value += MOD;
    }
  }
  Modular(long long a, long long b)
      : value(0) {
    *this += a;
    *this /= b;
  }

  Modular& operator+=(Modular const& b) {
    value += b.value;
    if (value >= MOD) {
      value -= MOD;
    }
    return *this;
  }
  Modular& operator-=(Modular const& b) {
    value -= b.value;
    if (value < 0) {
      value += MOD;
    }
    return *this;
  }
  Modular& operator*=(Modular const& b) {
    value = (long long) value * b.value % MOD;
    return *this;
  }

  static Modular mexp(Modular a, long long e) {
    Modular res = 1;
    while (e) {
      if (e & 1) {
        res *= a;
      }
      a *= a;
      e >>= 1;
    }
    return res;
  }
  friend Modular inverse(Modular a) {
    return mexp(a, MOD - 2);
  }

  Modular& operator/=(Modular const& b) {
    return *this *= inverse(b);
  }
  friend Modular operator+(Modular a, Modular const b) {
    return a += b;
  }
  friend Modular operator-(Modular a, Modular const b) {
    return a -= b;
  }
  friend Modular operator-(Modular const a) {
    return 0 - a;
  }
  friend Modular operator*(Modular a, Modular const b) {
    return a *= b;
  }
  friend Modular operator/(Modular a, Modular const b) {
    return a /= b;
  }
  friend std::ostream& operator<<(std::ostream& os, Modular const& a) {
    return os << a.value;
  }

  friend bool operator==(Modular const& a, Modular const& b) {
    return a.value == b.value;
  }
  friend bool operator!=(Modular const& a, Modular const& b) {
    return a.value != b.value;
  }
};

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
};
str yes(bool ans, str yes = "YES", str no = "NO") {
  return ans ? yes : no;
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
