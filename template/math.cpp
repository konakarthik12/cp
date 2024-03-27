#pragma once
#include "base.cpp"
const double pi = acos(-1);
template <typename T>
int sgn(T val) {
  if (T(0) == val) {
    return 0;
  }
  return (T(0) < val) - (val < T(0));
}
template <typename T, typename V>
auto ceil_div(T a, V b) {
  char ans_sgn = sgn(a) * sgn(b);
  return a / b + (a % b != 0) * ans_sgn;
}

template <typename T, typename U>
common_type_t<T, U> neg_mod(T n, U m) {
  if (n % m == 0) {
    return 0;
  }
  return m - (n % m);
}

double to_rad(double degrees) {
  return degrees * (pi / 180);
}

ll asum(ll a) {
  return (a + 1) * a / 2;
}
ll asum(ll a, ll b) {
  return (b + a) * (b - a + 1) / 2;
}
ll asum(ll a, ll b, ll c) {
  ll n = (b - a) / c + 1;
  ll sum = (n * (2 * a + (n - 1) * c)) / 2;
  return sum;
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
    if (is_prime[i]) primes.pb(i);
  }
  return primes;
}
vi linsieve(int n) {
  vi lp(n + 1);
  vi pr;

  for (int i = 2; i <= n; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.pb(i);
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

vi divisors(int n) {
  vi divs;
  for (int j = 1; j * j <= n; j++) {
    if (n % j == 0) {
      divs.pb(j);
      if (n / j != j) divs.pb(n / j);
    }
  }
  return divs;
}

template <typename T>
struct Combo {
  vec<T> facts;
  vec<T> inv_facts;
  Combo(int max_n) {
    facts.pb(1);
    inv_facts.pb(1);
    for (int i = 1; i <= max_n; i++) {
      facts.pb(facts.back() * i);
      inv_facts.pb(1 / facts.back());
    }
  }
  T fact(int x) {
    return facts[x];
  }

  T choose(int n, int k) {
    if (n < k) {
      return 0;
    }
    T ans(1);

    if (n >= sz(facts)) {
      for (int i = 0; i < k; i++) {
        ans *= n - i;
      }
    } else {
      ans = facts[n] * inv_facts[n - k];
    }
    return ans * inv_facts[k];
  }

  template <class... Args>
  T choose(int n, Args&&... args) {
    T ans(1);
    for (int a: {args...}) {
      ans *= choose(n, a);
      n -= a;
    }
    return ans;
  }

  T permute(int n, int k) {
    if (n < k) {
      return 0;
    }
    return facts[n] * inv_facts[n - k];
  }

  T bin(int n) {
    return T(2, n);
  }

  T sum(int n, int k, bool allow_zero = true) {
    if (allow_zero) {
      return choose(n + k - 1, k - 1);
    } else {
      return choose(n - 1, k - 1);
    }
  }
};

template <typename T>
concept Number = std::is_integral_v<T>;

struct Frac {
  ll p, q;
  Frac(ll p = 0, ll q = 1) : p(p), q(q) {
  }
  Frac simplify() const {
    ll g = gcd(p, q);
    return Frac(p / g, q / g);
  }
  Frac& simplify() {
    ll g = gcd(p, q);
    p /= g;
    q /= g;
    return *this;
  }
  Frac operator+=(const Frac& other) {
    int num = q * other.p + other.q * p;
    int denom = q * other.q;
    return Frac(num, denom);
  }
  Frac operator-=(const Frac& other) {
    int num = q * other.p - other.q * p;
    int denom = q * other.q;
    return Frac(num, denom);
  }

  Frac operator*=(Frac const& other) {
    p *= other.p;
    q *= other.q;
    return *this;
  }
  Frac operator/=(Frac const& other) {
    p *= other.q;
    q *= other.p;
    return *this;
  }

  friend Frac operator+(Frac a, Frac const b) {
    return a += b;
  }
  friend Frac operator-(Frac a, Frac const b) {
    return a -= b;
  }
  friend Frac operator-(Frac const a) {
    return 0 - a;
  }
  friend Frac operator*(Frac a, Frac const b) {
    return a *= b;
  }
  friend Frac operator/(Frac a, Frac const b) {
    return a /= b;
  }

  friend bool operator==(Frac const& a, Frac const& b) {
    return a.p == b.p && a.q == b.q;
  }

  friend bool operator==(Frac const& a, Number auto const& b) {
    Frac const& x = a.simplify();
    return x.q == 1 && x.p == b;
  }
};
