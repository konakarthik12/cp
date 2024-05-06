#pragma once
#include "../concepts.cpp"
template <typename C>
struct Con {
  using T = C::value_type;
  using value_type = T;
  C v;

  Con() {
  }
  explicit Con(int size) : v(size) {
  }
  explicit Con(int size, T init) : v(size, init) {
  }
  template <typename Container>
    requires HasIter<Container>
  explicit Con(Container cnt) : v(cnt.begin(), cnt.end()) {
  }
  Con(initializer_list<T> initList) : v(initList.size()) {
    auto it = v.begin();
    for (const auto& value: initList) {
      *it++ = value;
    }
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

  T& front() {
    return this->v.front();
  }

  T& back() {
    return this->v.back();
  }
  int size() const {
    return this->v.size();
  }

  bool empty() const {
    return this->v.empty();
  }
  explicit operator bool() const {
    return !this->empty();
  }

  T& operator[](size_t index) {
    return this->v[index];
  }

  const T& operator[](size_t index) const {
    return this->v[index];
  }

  void reserve(int size) {
    this->v.reserve(size);
  }

  void resize(int size) {
    this->v.resize(size);
  }
  void assign(int size, T x = T()) {
    this->v.assign(size, x);
  }

  void pb(const T& element) {
    this->v.push_back(element);
  }

  template <typename... Args>
  auto& eb(Args&&... args) {
    return this->v.emplace_back(std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto& insert(Args&&... args) {
    return this->v.insert(std::forward<Args>(args)...);
  }

  void rb() {
    this->v.pop_back();
  }

  void clear() {
    this->v.clear();
  }

  bool operator==(const Con& other) const {
    return this->v == other.v;
  }

  auto operator<=>(const Con& other) const {
    return this->v <=> other.v;
  }

  void iota(int n) {
    this->iota(1, n);
  }
  void iota(T a, T b) {
    this->resize(b - a + 1);
    std::iota(this->v.begin(), this->v.end(), a);
  }

  template <typename Comp = less<T>>
    requires SortPredicate<T, Comp>
  void sort(Comp comp = less<T>()) {
    std::sort(this->v.begin(), this->v.end(), comp);
  }

  template <class Proj = std::identity, class Comp = ranges::less>
    requires(!SortPredicate<T, Proj>)
  void sort(Proj proj, Comp comp = {}) {
    std::ranges::sort(this->v, comp, proj);
  }

  void rsort() {
    return this->sort(greater());
  }

  template <typename Pred>
    requires predicate<Pred, T>
  auto partition(Pred p) {
    return std::partition(this->v.begin(), this->v.end(), p);
  }
};

template <typename Iter, typename Proj = std::identity>
  requires(!SortPredicate<decltype(*Iter()), Proj>)
void sort(Iter first, Iter last, Proj proj) {
  std::ranges::sort(first, last, ranges::less{}, proj);
}