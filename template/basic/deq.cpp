#pragma once
#include "con.cpp"

template <typename T>
struct deq : public Con<deque<T>> {
  using Con<deque<T>>::Con;
  using value_type = T;

  void pf(const T& element) {
    this->v.push_front(element);
  }

  template <typename... Args>
  auto ef(Args&&... args) {
    return this->v.emplace_back(std::forward<Args>(args)...);
  }

  auto rf() {
    T x = this->v.front();
    this->v.pop_front();
    return x;
  }
};
