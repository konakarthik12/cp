#pragma once

#include "base.cpp"
#include "concepts.cpp"

template <typename T>
enable_if_t<Readable<T>> __read(T& arr) {
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
template<typename V>
struct HasReserve {
  template<typename T, typename = decltype(std::declval<T>().reserve(std::declval<size_t>()))>
  static std::true_type test(int);

  template<typename>
  static std::false_type test(...);

  static constexpr bool value = decltype(test<V>(0))::value;
};


template <typename T>
void reserve(T& v, size_t s) {

    if constexpr (HasReserve<T>::value) {
      v.reserve(s);
    }
}

template <typename V>
std::enable_if_t<std::is_member_function_pointer_v<decltype(&V::pb)>, void> append(V& v,
                                                                                   const typename V::value_type& x) {
  v.pb(x);
}

template <typename V>
std::enable_if_t<std::is_member_function_pointer_v<decltype(&V::push_back)> &&
                     !std::is_member_function_pointer_v<decltype(&V::pb)>,
                 void>
append(V& v, const typename V::value_type& x) {
  v.push_back(x);
}

template <typename V>
std::enable_if_t<!std::is_member_function_pointer_v<decltype(&V::pb)> &&
                     !std::is_member_function_pointer_v<decltype(&V::push_back)>,
                 void>
append(V& v, const typename V::value_type& x) {
  v.insert(x);
}

template <typename Container>
enable_if_t<HasValueType<Container>::value> __read(Container& v, int n) {
  using T = typename Container::value_type;
  reserve(v, n);
  for (int i = 0; i < n; i++) {
    T x;
    __read(x);
    append(v, x);
  }
}

template <typename V2, typename = void>
struct HasEB : std::false_type {};

template <typename V2>
struct HasEB<V2, std::void_t<decltype(std::declval<V2>().eb())>> : std::true_type {};

template <typename V2, typename = void>
struct HasEmplaceBack : std::false_type {};

template <typename V2>
struct HasEmplaceBack<V2, std::void_t<decltype(std::declval<V2>().emplace_back())>> : std::true_type {};


template <typename V2>
typename V2::value_type& emplace_empty(V2& v2) {
  if cexp (HasEB<V2>::value) {
    return v2.eb();
  } else if cexp (HasEmplaceBack<V2>::value) {
    return v2.emplace_back();
  }
}

template <typename V2>
enable_if_t<HasValueType2D<V2>::value> __read(V2& v2, int r, int c) {
  using V = typename V2::value_type;
  reserve(v2, r);
  for (int i = 0; i < r; i++) {
    cexp bool EB = HasEB<V2>::value || HasEmplaceBack<V2>::value;
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
enable_if_t<Readable1D<T> && !Readable2D<T> && !Readable<T>> read(T&& first, T2&& second, Args&&... args) {
  __read(std::forward<T>(first), std::forward<T2>(second));
  read(std::forward<Args>(args)...);
}

template <typename T, typename T2, typename T3, typename... Args>
enable_if_t<Readable2D<T> && !Readable<T>> read(T&& first, T2&& second, T3&& third, Args&&... args) {
  __read(std::forward<T>(first), std::forward<T2>(second), std::forward<T3>(third));
  read(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
enable_if_t<Readable<T> || (!Readable1D<T> && !Readable2D<T>)> read(T&& first, Args&&... args) {
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
