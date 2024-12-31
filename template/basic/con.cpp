#pragma once
#include "../concepts.cpp"
#include "../scaffold.cpp"
#include "../deb.cpp"


#include "bool.cpp"

template <typename T, template <class, class...> class C>
struct Con {
  using V = C<T>;
  using iter = C<T>::iterator;
  using value_type = T;
  V v;

  Con() {
  }
  explicit Con(int size) : v(size) {
  }
  Con(int size, T init) : v(size, init) {
  }
  template <typename Iter>
    requires input_iterator<Iter>
  Con(Iter start, Iter end) : v(start, end) {
  }

  template <typename Container>
    requires HasIter<Container>
  explicit Con(const Container& cnt) : v(cnt.begin(), cnt.end()) {
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

  int sz() const {
    return this->v.size();
  }

  bool empty() const {
    return this->v.empty();
  }

  explicit operator bool() const {
    return !this->empty();
  }

  T& operator[](size_t index) {
    dssert(index >= 1 && <= this->v.size());
    return this->v[index];
  }

  const T& operator[](size_t index) const {
    dssert(index >= 1 && <= this->v.size());

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

  void fill(T x = T()) {
    std::fill(v.begin(), v.end(), x);
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

  T rb() {
    T x = this->back();
    this->v.pop_back();
    return x;
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

  void iota(T a, T b) {
    this->resize(b - a + 1);
    std::iota(this->v.begin(), this->v.end(), a);
  }

  void iota(int n) {
    iota(0, n - 1);
  }

  template <typename Comp = less<T>>
    requires SortPredicate<T, Comp>
  void sort(Comp comp = {}) {
    std::sort(this->v.begin(), this->v.end(), comp);
  }

  template <class Proj = std::identity, class Comp = ranges::less>
    requires(!SortPredicate<T, Proj>)
  void sort(Proj proj, Comp comp = {}) {
    std::ranges::sort(this->v.begin(), this->v.end(), comp, proj);
  }
  template <typename Comp = less<T>>
    requires SortPredicate<T, Comp>
  void stable_sort(Comp comp = {}) {
    std::stable_sort(this->v.begin(), this->v.end(), comp);
  }

  template <class Proj = std::identity, class Comp = ranges::less>
    requires(!SortPredicate<T, Proj>)
  void stable_sort(Proj proj, Comp comp = {}) {
    std::ranges::stable_sort(this->v, comp, proj);
  }

  auto rsort() {
    return this->sort(greater());
  }
  template <class Proj = std::identity, class Comp = ranges::greater>
    requires(!SortPredicate<T, Proj>)
  void rsort(Proj proj, Comp comp = {}) {
    std::ranges::sort(this->v, comp, proj);
  }

  auto reverse() {
    return std::reverse(this->v.begin(), this->v.end());
  }

  auto next_perm() {
    return std::next_permutation(v.begin(), v.end());
  }
  auto prev_perm() {
    return std::prev_permutation(v.begin(), v.end());
  }

  template <typename Pred>
    requires predicate<Pred, T>
  auto partition(Pred p) {
    return std::partition(v.begin(), v.end(), p);
  }
  auto is_sorted() {
    return std::is_sorted(v.begin(), v.end());
  }

  auto back_inserter() {
    return std::back_inserter(v);
  }
  auto get(int x) {
    if (x < 0) x += sz();
    return v[x];
  }

  template <class Predicate = std::equal_to<>>
  void dedupe(Predicate p = {}) {
    v.erase(unique(v.begin(), v.end(), p), end());
  }

  template <class Compare = std::less<>>
  auto lower_bound(const T& x, Compare comp = {}) {
    return std::lower_bound(v.begin(), v.end(), x, comp);
  }

  template <class Compare = std::less<>>
  auto upper_bound(const T& x, Compare comp = {}) {
    return std::upper_bound(v.begin(), v.end(), x, comp);
  }

  template <class Compare = std::less<>>
  auto gr(const T& x, Compare comp = {}) {
    return *upper_bound(x, comp);
  }

  template <class Compare = std::less<>>
  auto ge(const T& x, Compare comp = {}) {
    return *lower_bound(x, comp);
  }
  template <class Compare = std::less<>>
  auto cnt_ge(const T& x, Compare comp = {}) {
    auto iter = lower_bound(x, comp);
    return idist(v.begin(), iter);
  }

  template <class Compare = std::less<>>
  auto ls(const T& x, Compare comp = {}) {
    return *prev(lower_bound(x, comp));
  }
  template <class Compare = std::less<>>
  auto le(const T& x, Compare comp = {}) {
    return *prev(upper_bound(x, comp));
  }

  auto sum() {
    if cexp (is_integral_v<T>) return reduce(this->begin(), this->end(), 0LL);
    else return reduce(this->begin(), this->end(), T(0));
  }

  T max() {
    return *std::max_element(v.begin(), v.end());
  }
  T min() {
    return *std::min_element(v.begin(), v.end());
  }

  template <typename... Args>
  auto count(Args&&... args) {
    return std::count(this->v.begin(), this->v.end(), std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto count_if(Args&&... args) {
    return v.count_if(std::forward<Args>(args)...);
  }

  //  auto append(const Con& other) {
  //    this->v.insert(this->v.end(), other.begin(), other.end());
  //  }

  auto operator+=(const Con& other) {
    this->v.insert(this->v.end(), other.begin(), other.end());
  }

  template <class RNG>
  auto shuffle(RNG& gen) {
    std::shuffle(v.begin(), v.end(), gen);
  }
};

template <typename Iter, typename Proj = std::identity>
  requires(!SortPredicate<decltype(*Iter()), Proj>)
void sort(Iter first, Iter last, Proj proj) {
  std::ranges::sort(first, last, ranges::less{}, proj);
}
