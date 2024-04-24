#define NO_MAIN
#include "template.cpp"
int seed;

ll rnd_internal(ll a, ll b) {
  assert(a <= b);
  if (a == b) {
    return a;
  }
  uniform_int_distribution<ll> dis(a, b);
  return dis(rng);
}
ll rnd(ll a, ll b) {
  assert(a <= b);
  if (seed < 1000) {
    ld progress = seed / 1000.0L;
    ld new_b = (ld) a + (b - a) * progress;
    assert(new_b >= a && new_b <= b);
    b = new_b;
  }
  return rnd_internal(a, b);
}
char rnd_char() {
  return 'a' + rnd(0, 25);
}
int rnd_not(int a, int b, int exclude) {
  int n = exclude;
  while (n == exclude) {
    n = rnd(a, b);
  }
  return n;
}
vpii pruefer_decode(vec<int> const& code) {
  int n = code.size() + 2;
  vec<int> degree(n, 1);
  for (int i: code) {
    degree[i]++;
  }

  int ptr = 0;
  while (degree[ptr] != 1) {
    ptr++;
  }
  int leaf = ptr;

  vpii edges;
  for (int v: code) {
    edges.eb(leaf, v);
    if (--degree[v] == 1 && v < ptr) {
      leaf = v;
    } else {
      ptr++;
      while (degree[ptr] != 1) {
        ptr++;
      }
      leaf = ptr;
    }
  }
  edges.eb(leaf, n - 1);
  return edges;
}

template <typename T>
vec<T> rnd_list(int n, T a, T b) {
  vec<T> arr;
  for (int i = 0; i < n; i++) {
    arr.pb(rnd(a, b));
  }
  return arr;
}

vi rnd_list_distinct(int n, int a, int b) {
  assert((b - a + 1) >= n);
  if (seed < 1000) {
    b = min(b, max(a + seed / 5, (a + n - 1)));
  }
  set<int> s;
  while ((int) s.size() < n) {
    s.insert(rnd_internal(a, b));
  }
  return vi{s};
}

vi rnd_permute(int n) {
  vi arr(n);
  iota(all(arr), 1);
  shuffle(all(arr), rng);
  return arr;
}

bool rnd_bool() {
  return rnd(0, 1);
}
void generate();

int main(int argc, char* argv[]) {
  if (argc == 2) {
    seed = atoi(argv[1]);
    assert(seed >= 0);
    rng = mt19937(seed);
  }
  generate();
}
