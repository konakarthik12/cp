#pragma once
#include "../concepts.cpp"
#include "vec.cpp"

template <typename T, typename Comp = less<T>, typename Container = std::vector<T>>
struct pqueue {
  std::priority_queue<T, Container, Comp> v;
  using value_type = T;

  pqueue() {
  }

  pqueue(const std::priority_queue<T, Container, Comp>& v) : v(v) {
  }

  pqueue(const pqueue& q) : v(q.v) {
  }

  pqueue(pqueue&& q) : v(std::move(q.v)) {
  }

  pqueue(initializer_list<T> initList) {
    for (const auto& value: initList) v.push(value);
  }

  template <typename Iter>
    requires input_iterator<Iter>
  pqueue(Iter start, Iter end) {
    for (auto it = start; it != end; ++it) {
      v.push(*it);
    }
  }

  template <HasIter ContainerType>
  explicit pqueue(const ContainerType& cnt) {
    for (const auto& value: cnt) {
      v.push(value);
    }
  }

  pqueue& operator=(const pqueue& q) {
    v = q.v;
    return *this;
  }

  pqueue& operator=(pqueue&& q) {
    v = std::move(q.v);
    return *this;
  }

  auto top() {
    return v.top();
  }

  auto top() const {
    return v.top();
  }

  void ps(const T& x) {
    v.push(x);
  }

  template <typename... Args>
  void em(Args&&... args) {
    v.emplace(std::forward<Args>(args)...);
  }

  T rm() {
    T x = v.top();
    v.pop();
    return x;
  }

  int sz() const {
    return v.size();
  }

  bool empty() const {
    return v.empty();
  }

  explicit operator bool() const {
    return !v.empty();
  }

  void clear() {
    while (!v.empty()) {
      v.pop();
    }
  }
};
