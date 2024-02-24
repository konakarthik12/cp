#pragma once

#include "base.cpp"
#include "concepts.cpp"
#include "wec.cpp"

void __read(bool &b) {
  char x;
  cin >> x;
  b = (x == '1');
}

void __read(int &x) {
  cin >> x;
}

void __read(uint &x) {
  cin >> x;
}

void __read(char &x) {
  cin >> x;
}

void __read(ll &x) {
  cin >> x;
}

void __read(ull &x) {
  cin >> x;
}

void __read(string &s) {
  cin >> s;
}

template <const size_t N>
void __read(bitset<N> &b) {
  using Type = typename std::conditional_t<(N <= sizeof(int) * 8), int, ll>;
  Type x;
  cin >> x;
  b = x;
}

template <typename T1, typename T2>
void __read(pr<T1, T2> &p) {
  __read(p.f);
  __read(p.s);
}

template <typename T>
concept HasReserve = requires(T &container, size_t s) {
  { container.reserve(s) } -> std::same_as<void>;
};

template <typename T>
  requires HasReserve<T>
void reserve(T &container, size_t s) {
  container.reserve(s);
}

template <typename T>
  requires(!HasReserve<T>)
void reserve(T &, size_t) {
}

template <typename Container>
  requires HasValueType<Container>
void __read(Container &v, int n) {
  using T = Container::value_type;
  reserve(v, n);
  for (int i = 0; i < n; i++) {
    T x;
    __read(x);
    v.push_back(x);
  }
}

template <typename Container>
  requires HasValueType2D<Container>
void __read(Container &v, int r, int c) {
  using T = Container::value_type;
  reserve(v, r);
  for (int i = 0; i < r; i++) {
    T &col = v.emplace_back();
    reserve(col, c);
    __read(col, c);
  }
}

void read() {
}

template <typename T>
void read(T &&arg) {
  __read(std::forward<T>(arg));
}

template <typename T, typename T2, typename... Args>
  requires(Readable1D<T> && !Readable2D<T> && !Readable<T>)
void read(T &&first, T2 &&second, Args &&...args) {
  __read(std::forward<T>(first), std::forward<T2>(second));
  read(std::forward<Args>(args)...);
}

template <typename T, typename T2, typename T3, typename... Args>
  requires(Readable2D<T> && !Readable<T>)
void read(T &&first, T2 &&second, T3 &&third, Args &&...args) {
  __read(std::forward<T>(first), std::forward<T2>(second), std::forward<T3>(third));
  read(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
  requires(Readable<T> || (!Readable1D<T> && !Readable2D<T>) )
void read(T &&first, Args &&...args) {
  __read(std::forward<T>(first));
  read(std::forward<Args>(args)...);
}

int readInt() {
  int x;
  read(x);
  return x;
}

template <class T>
void read_count(map<T, int> &m, int n) {
  for (int i = 0; i < n; i++) {
    T temp;
    read(temp);
    m[temp]++;
  }
}

template <class T, class Comp = less<T>()>
void read_count(map<T, int, Comp> &m, int n) {
  m.clear();
  for (int i = 0; i < n; i++) {
    T temp;
    rd(temp);
    m[temp]++;
  }
}

wwi read_graph(int n, int m, bool directed = false) {
  wwi adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    read(u, v);
    adj[u].pb(v);
    if (!directed) adj[v].pb(u);
  }
  return adj;
}

wwi read_tree(int n) {
  return read_graph(n, n - 1);
}

wwpii read_graph_weighted(int n, int m, bool directed = false) {
  wwpii adj(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    read(u, v, w);
    adj[u].eb(v, w);
    if (!directed) {
      adj[v].eb(u, w);
    }
  }
  return adj;
}
