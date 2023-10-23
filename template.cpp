#include "wrapper.h"
#ifndef TEMPLATE_H
#define TEMPLATE_H
#include "template/deb.cpp"
using namespace std;
template <class T1, class T2>
bool operator<(const Pair<T1, T2>& x, const Pair<T1, T2>& y) {
  return std::tie(x.f, x.s) < std::tie(y.f, y.s);
}
template <class T1, class T2>
bool operator>(const Pair<T1, T2>& x, const Pair<T1, T2>& y) {
  return std::tie(x.f, x.s) > std::tie(y.f, y.s);
}
template <class T1, class T2>
bool operator==(const Pair<T1, T2>& x, const Pair<T1, T2>& y) {
  return std::tie(x.f, x.s) == std::tie(y.f, y.s);
}
using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

template <typename T1, typename T2>
using pr = Pair<T1, T2>;
using pii = pr<int, int>;
using pdd = pr<double, double>;
using pcc = pr<char, char>;
using pll = pair<ll, ll>;
using mii = map<int, int>;
using mci = map<char, int>;
template <class T, class Compare = less<T>>
using pqueue = priority_queue<T, vector<T>, Compare>;
template <class T>
using vec = vector<T>;
using vi = vec<int>;
using vd = vec<double>;
using vll = vec<ll>;
template <class T>
using vv = vec<vec<T>>;
template <class T>
using vvv = vec<vv<T>>;
using vvi = vv<int>;
using vvvi = vvv<int>;
using vvll = vv<ll>;
using vvc = vv<char>;
using vpii = vec<pii>;
using vvpii = vv<pii>;
using vpll = vec<pll>;
using vvpll = vv<pll>;
using vc = vec<char>;
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

  // the following operators are to allow bool* b = &v[0]; (v is a vector here).
  bool* operator&() {
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
#define pb(x) push_back(x);
#define eb(...) emplace_back(__VA_ARGS__);
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define fir first
#define sec second

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
int sgn(T val) {
  if (T(0) == val) {
    return 0;
  }
  return (T(0) < val) - (val < T(0));
}
template <typename T>
T ceil_div(T a, T b) {
  char ans_sgn = sgn(a) * sgn(b);
  return a / b + (a % b != 0) * ans_sgn;
}

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

template <class T, typename... Args>
void read(vec<T>& v, int n, Args&... args) {
  v.reserve(v.size() + n);
  for (int i = 0; i < n; i++) {
    T temp;
    read(temp);
    v.push_back(temp);
  }
  read(args...);
}
template <class T, typename... Args>
void read(deque<T>& v, int n, Args&... args) {
  for (int i = 0; i < n; i++) {
    T temp;
    read(temp);
    v.push_back(temp);
  }
  read(args...);
}
template <class T, typename... Args>
void read_count(map<T, int>& m, int n, Args&... args) {
  for (int i = 0; i < n; i++) {
    T temp;
    read(temp);
    m[temp]++;
  }
  read(args...);
}
template <typename T, typename = void>
struct has_value_type : std::false_type {};

template <typename T>
struct has_value_type<T, std::void_t<typename T::value_type>> : std::true_type {};

template <typename T>
typename std::enable_if<has_value_type<T>::value, void>::type read(T& v, int n) {
  for (int i = 0; i < n; i++) {
    typename T::value_type temp;
    read(temp);
    v.insert(temp);
  }
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
void read1(vec<T>& arr, int n) {
  arr.push_back(0);
  read(arr, n);
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
void read1(string& s) {
  read(s);
  s = '*' + s;
}
void print() {
}
template <class T>
void print(const T& arg) {
  cout << arg;
}

template <class T, class... Args>
void print(const T& arg, const Args&... args) {
  cout << arg << " ";
  print(args...);
}

template <class... Args>
void printsp(Args... args) {
  print(args...);
  cout << " ";
}
template <typename T>
void printsp(vec<T>& arr) {
  for (T& item: arr) {
    printsp(item);
  }
}
template <class... Args>
void println(Args... args) {
  print(args...);
  cout << "\n";
}

template <typename ForwardIt>
void printsp(ForwardIt first, ForwardIt last) {
  for (auto it = first; it != last; it++) {
    printsp(*it);
  }
}

template <typename T>
void println(vec<T>& v) {
  printsp(all(v));
  println();
}

void flush() {
  cout.flush();
}

const double pi = acos(-1);

double to_rad(double degrees) {
  return degrees * (pi / 180);
}
template <class Iter>
int idist(Iter a, Iter b) {
  return distance(a, b);
}
template <class Container>
void dedupe(Container& vec) {
  vec.erase(unique(all(vec)), vec.end());
}
template <class Container, class Predicate>
void dedupe(Container& vec, Predicate p) {
  vec.erase(unique(all(vec), p), vec.end());
}
template <class Container>
void sort(Container& vec) {
  sort(all(vec));
}
template <class Container>
void rsort(Container& vec) {
  sort(all(vec), greater());
}
template <class Container>
void reverse(Container& vec) {
  reverse(all(vec));
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
ll sum(vi& arr) {
  return sum(all(arr));
}

template <class Container>
ll sum(Container& vec) {
  return sum(all(vec));
}
template <class Container, typename T>
void fill(Container& vec, T value) {
  fill(all(vec), value);
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
template <typename T>
vll prefix_sum(vec<T> arr) {
  ll cur = 0;
  vll prefixs(1);
  prefixs.reserve(sz(arr));
  for (T x: arr) {
    cur += x;
    prefixs.pb(cur);
  }
  return prefixs;
}
template <class ForwardIt>
constexpr std::pair<typename std::iterator_traits<ForwardIt>::value_type,
                    typename std::iterator_traits<ForwardIt>::value_type>
lowhigh(ForwardIt first, ForwardIt last) {
  auto [low, high] = std::minmax_element(first, last);
  return {*low, *high};
}

template <typename T>
T max(vec<T>& arr) {
  return *max_element(all(arr));
}
template <typename T>
T min(vec<T>& arr) {
  return *min_element(all(arr));
}
template <typename T>
T min(Pair<T, T> p) {
  return min(p.f, p.s);
}

ll asum(ll a) {
  return (a + 1) * a / 2;
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
vi linsieve(int n) {
  vi lp(n + 1);
  vi pr;

  for (int i = 2; i <= n; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= n; ++j) {
      lp[i * pr[j]] = pr[j];
      if (pr[j] == lp[i]) {
        break;
      }
    }
  }
  return lp;
}
template <typename T>
struct Combo {
  vec<T> facts;
  vec<T> inv_facts;
  Combo(int max_n) {
    facts.pb(1);
    inv_facts.pb(1);
    for (int i = 1; i <= max_n; i++) {
      facts.push_back(facts.back() * i);
      inv_facts.push_back(1 / facts.back());
    }
  }
  T fact(int x) {
    return facts[x];
  }
  T choose(int n, int k) {
    if (n < k) {
      return 0;
    }
    T ans;

    if (n >= sz(facts)) {
      // if n is really big, compute n! / (n - k)! linearly
      ans = 1;
      for (int i = 0; i < k; i++) {
        ans *= n - i;
      }
    } else {
      ans = facts[n] * inv_facts[n - k];
    }
    return ans * inv_facts[k];
  }
  T permute(int n) {
    if (n < 0) {
      return 0;
    }
    return facts[n];
  }

  T permute(int n, int k) {
    if (n < k) {
      return 0;
    }
    return facts[n] * inv_facts[n - k];
  }
  T bin(int n) {
    return mexp(T(2), n);
  }
  T sum(int n, int k, bool allow_zero = true) {
    if (allow_zero) {
      return choose(n + k - 1, k - 1);
    } else {
      return choose(n - 1, k - 1);
    }
  }
};

template <typename T, typename F>
T max_true(T l, T h, F comp) {
  auto iter = ranges::partition_point(views::iota(l, h + 1), comp);
  return *iter - 1;
}

str yes(bool ans, str yes = "YES", str no = "NO") {
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

#endif
