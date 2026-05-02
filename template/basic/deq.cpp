#pragma once
#include "list.cpp"

template <typename T>
struct deq : list<T, std::deque, 1> {
  using list<T, std::deque, 1>::list;
  using value_type = T;

  void pf(const T& element) {
    this->v.push_front(element);
  }

  template <typename... Args>
  auto ef(Args&&... args) {
    return this->v.emplace_front(std::forward<Args>(args)...);
  }

  auto rf() {
    T x = this->v.front();
    this->v.pop_front();
    return x;
  }

  auto front_inserter() {
    return std::front_inserter(this->v);
  }

  auto reserve() = delete;
};
