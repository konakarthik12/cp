#include "base.cpp"
#ifndef TEMPLATE_VEC
#define TEMPLATE_VEC
template <typename Con>
void iota(Con& v, const typename Con::value_type start = Con::value_type(0)) {
  iota(all(v), start);
};

template <typename T>
struct wec {
  vec<T> v;

  auto operator<=>(const wec&) const = default;

  using value_type = T;
  wec() : v(1) {
  }
  explicit wec(int size) : v(size + 1) {
  }
  explicit wec(int size, T init) : v(size + 1, init) {
  }
  wec(initializer_list<T> initList) : v(initList.size() + 1) {
    auto it = v.begin() + 1;
    for (const auto& value: initList) {
      *it++ = value;
    }
  }

  T& operator[](size_t index) {
    return v[index];
  }

  const T& operator[](size_t index) const {
    return v[index];
  }
  auto begin() {
    return v.begin() + 1;
  }

  auto end() {
    return v.end();
  }
  int size() const {
    return v.size() - 1;
  }

  void resize(int size) {
    v.resize(size + 1);
  }
  void assign(int size, int x = T()) {
    v.assign(size + 1, x);
  }

  auto begin() const {
    return v.begin() + 1;
  }

  auto end() const {
    return v.end();
  }

  void push_back(const T& value) {
    v.push_back(value);
  }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    v.emplace_back(std::forward<Args>(args)...);
  }

  void pop_back() {
    v.pop_back();
  }

  bool operator==(const wec& other) const {
    return v == other.v;
  }
  void clear() {
    v.resize(1);
  }
};

using wi = wec<int>;
using wll = wec<ll>;
template <typename T>
using ww = wec<wec<T>>;
using wwi = ww<int>;
using wpii = wec<pii>;
using wwpii = ww<pii>;
using wb = wec<Bool>;
using wc = wec<char>;
#endif
