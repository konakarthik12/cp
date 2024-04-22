#pragma once

#include "base.cpp"
#include "basic/wec.cpp"
#include "concepts.cpp"

template <typename T>
  requires Readable<T>
void __read(T& arr) {
  cin >> arr;
}
template <const size_t N>
void __read(bitset<N>& b) {
  using Type = typename std::conditional_t<(N <= sizeof(int) * 8), int, ll>;
  Type x;
  cin >> x;
  b = x;
}

template <typename T1, typename T2>
void __read(pr<T1, T2>& p) {
  __read(p.f);
  __read(p.s);
}

template <typename T>
void reserve(T& v, size_t s) {
  cexp bool HasReserve = requires {
    { v.reserve(s) };
  };

  if cexp (HasReserve) {
    v.reserve(s);
  }
}

template <typename V>
void append(V& v, const typename V::value_type& x) {
  cexp bool HasPB = requires {
    { v.pb(x) };
  };
  cexp bool HasPushBack = requires {
    { v.push_back(x) };
  };

  if cexp (HasPB) {
    v.pb(x);
  } else if cexp (HasPushBack) {
    v.push_back(x);
  } else {
    v.insert(x);
  }
}
template <typename Container>
  requires HasValueType<Container>
void __read(Container& v, int n) {
  using T = Container::value_type;
  reserve(v, n);
  for (int i = 0; i < n; i++) {
    T x;
    __read(x);
    append(v, x);
  }
}

template <class V2>
concept HasEB = requires(V2 v2) {
  { v2.emplace_back() } -> same_as<typename V2::value_type>;
};

template <typename V2>
concept HasEmplaceBack = requires(V2 v2) {
  { v2.emplace_back() } -> same_as<typename V2::value_type>;
};

template <typename V2>
V2::value_type& emplace_empty(V2& v2) {
  if cexp (HasEB<V2>) {
    return v2.eb();
  } else if cexp (HasEmplaceBack<V2>) {
    return v2.emplace_back();
  }
}

template <typename V2>
  requires HasValueType2D<V2>
void __read(V2& v2, int r, int c) {
  using V = V2::value_type;
  reserve(v2, r);
  for (int i = 0; i < r; i++) {
    cexp bool EB = HasEB<V2> || HasEmplaceBack<V2>;
    if cexp (EB) {
      V& col = emplace_empty(v2);
      __read(col, c);
    } else {
      V col;
      __read(col, c);
      append(v2, col);
    }
  }
}

void read() {
}

template <typename T>
void read(T&& arg) {
  __read(std::forward<T>(arg));
}

template <typename T, typename T2, typename... Args>
  requires(Readable1D<T> && !Readable2D<T> && !Readable<T>)
void read(T&& first, T2&& second, Args&&... args) {
  __read(std::forward<T>(first), std::forward<T2>(second));
  read(std::forward<Args>(args)...);
}

template <typename T, typename T2, typename T3, typename... Args>
  requires(Readable2D<T> && !Readable<T>)
void read(T&& first, T2&& second, T3&& third, Args&&... args) {
  __read(std::forward<T>(first), std::forward<T2>(second), std::forward<T3>(third));
  read(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
  requires(Readable<T> || (!Readable1D<T> && !Readable2D<T>) )
void read(T&& first, Args&&... args) {
  __read(std::forward<T>(first));
  read(std::forward<Args>(args)...);
}

int readInt() {
  int x;
  read(x);
  return x;
}

template <class T>
void read_count(map<T, int>& m, int n) {
  for (int i = 0; i < n; i++) {
    T temp;
    read(temp);
    m[temp]++;
  }
}

template <class T, class Comp = less<T>()>
void read_count(map<T, int, Comp>& m, int n) {
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
