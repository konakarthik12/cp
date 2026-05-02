#pragma once
#include "../scaffold.cpp"
#include "../concepts.cpp"
#include "../deb_raw.cpp"
#include "bool.cpp"

template <typename T, template <class, class...> class C, const int offset = 0, typename... Extra>
struct Con {
  using V = C<T, Extra...>;
  using value_type = T;
  V v;

  Con() {
  }

  template <input_iterator Iter>
  Con(Iter start, Iter end) : v(start, end) {
  }

  template <HasIter Container>
  explicit Con(const Container& cnt) : v(cnt.begin(), cnt.end()) {
  }

  Con(initializer_list<T> initList) : v(initList) {
  }

  auto begin() const {
    return this->v.begin();
  }

  auto end() const {
    return this->v.end();
  }

  auto begin() {
    return this->v.begin();
  }

  auto end() {
    return this->v.end();
  }

  auto rbegin() const {
    return this->v.rbegin();
  }

  auto rend() const {
    return this->v.rend();
  }

  auto rbegin() {
    return this->v.rbegin();
  }

  auto rend() {
    return this->v.rend();
  }

  int sz() const {
    return (int) this->v.size();
  }

  bool empty() const {
    return this->v.empty();
  }

  explicit operator bool() const {
    return !this->empty();
  }

  void clear() {
    this->v.clear();
  }

  bool operator==(const Con& other) const {
    return this->v == other.v;
  }
};
