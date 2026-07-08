#pragma once
#include "con.cpp"

// Sequential container operations (for vec, deq, etc.)
template <typename T, template <class, class...> class C, const int offset = 0>
struct list : Con<T, C, offset> {
  using Base = Con<T, C, offset>;
  using Base::Base;
  using value_type = T;

  explicit list(int size, T init = T()) : Base() {
    this->v = typename Base::V(size, init);
  }

  template <std::integral First, std::integral... Rest>
    requires requires(T& container) {
      { sizeof...(Rest) >= 1 };
      { HasIter<T> };
      { std::constructible_from<T, Rest...> };
    }
  explicit list(First first, Rest... rest) : Base() {
    this->v = typename Base::V(static_cast<size_t>(first), T(static_cast<size_t>(rest)...));
  }

  T& front() {
    return this->v.front();
  }

  auto& back() {
    return this->v.back();
  }

  auto& back() const {
    return this->v.back();
  }

  T& operator[](const int idx) {
    int index = idx - offset;
    dssert(index >= 0 && index < this->sz());
    return this->v[index];
  }

  const T& operator[](const int idx) const {
    int index = idx - offset;
    dssert(index >= 0 && index < this->sz());
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
    std::fill(this->v.begin(), this->v.end(), x);
  }

  void pb(const T& element) {
    this->v.push_back(element);
  }

  template <typename... Args>
  auto& eb(Args&&... args) {
    return this->v.emplace_back(std::forward<Args>(args)...);
  }

  auto insert(int idx, const T& x) {
    idx -= offset;
    if (idx < 0) idx += this->sz();
    dssert(idx >= 0 && idx <= this->sz());
    return this->v.insert(this->v.begin() + idx, x);
  }

  T rb() {
    T x = this->back();
    this->v.pop_back();
    return x;
  }

  auto operator<=>(const list& other) const {
    return this->v <=> other.v;
  }

  void iota(T a, T b) {
    this->resize(b - a + 1);
    std::iota(this->v.begin(), this->v.end(), a);
  }

  void iota(int n) {
    iota(offset, n - 1 + offset);
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

  template <typename Comp = less<T>>
    requires SortPredicate<T, Comp>
  void rsort(Comp comp = {}) {
    std::sort(this->v.begin(), this->v.end(), [&](const auto& a, const auto& b) { return comp(b, a); });
  }

  template <class Proj = std::identity, class Comp = ranges::greater>
    requires(!SortPredicate<T, Proj>)
  void rsort(Proj proj, Comp comp = {}) {
    std::ranges::sort(this->v, comp, proj);
  }

  void flip() {
    std::reverse(this->v.begin(), this->v.end());
  }

  auto next_perm() {
    return std::next_permutation(this->v.begin(), this->v.end());
  }

  auto prev_perm() {
    return std::prev_permutation(this->v.begin(), this->v.end());
  }

  template <typename Pred>
    requires predicate<Pred, T>
  auto partition(Pred p) {
    return std::partition(this->v.begin(), this->v.end(), p);
  }

  auto is_sorted() {
    return std::is_sorted(this->v.begin(), this->v.end());
  }

  auto is_rsorted() {
    return std::is_sorted(this->v.begin(), this->v.end(), greater());
  }

  auto back_inserter() {
    return std::back_inserter(this->v);
  }

  auto get(int x) {
    if (x < 0) x += this->sz();
    return this->v[x];
  }

  template <class Predicate = std::equal_to<>>
  void dedupe(Predicate p = {}) {
    this->v.erase(unique(this->v.begin(), this->v.end(), p), this->end());
  }

  template <class Compare = std::less<>>
  auto lower_bound(const T& x, Compare comp = {}) {
    return std::lower_bound(this->v.begin(), this->v.end(), x, comp);
  }

  template <class Compare = std::less<>>
  auto upper_bound(const T& x, Compare comp = {}) {
    return std::upper_bound(this->v.begin(), this->v.end(), x, comp);
  }

  template <class Compare = std::less<>>
  auto gr(const T& x, Compare comp = {}) {
    return *upper_bound(x, comp);
  }

  template <class Compare = std::less<>>
  auto ge(const T& x, Compare comp = {}) {
    return *lower_bound(x, comp);
  }

  template <typename... Args>
  void erase_if(Args&&... args) {
    std::erase_if(this->v, std::forward<Args>(args)...);
  }

  template <class Compare = std::less<>>
  auto ls(const T& x, Compare comp = {}) {
    return *prev(lower_bound(x, comp));
  }

  template <class Compare = std::less<>>
  auto le(const T& x, Compare comp = {}) {
    return *prev(upper_bound(x, comp));
  }

  template <typename Op>
  auto reduce(Op op) const {
    using S = decltype(op(T(), T()));
    return reduce(op, S());
  }

  template <typename Op, typename Init>
  auto reduce(Op op, Init init) const {
    return std::accumulate(this->v.begin(), this->v.end(), init, op);
  }

  auto sum() const {
    return reduce(std::plus<sum_v<T>>());
  }

  template <typename F>
    requires std::invocable<F, const T&>
  auto map(F&& f) const {
    using U = std::decay_t<std::invoke_result_t<F, const T&>>;
    list<U, C, offset> result;
    result.reserve(this->sz());
    std::ranges::transform(this->v, std::back_inserter(result.v), std::forward<F>(f));
    return result;
  }



  template <typename F>
    requires std::invocable<F, const T&>
  auto max(F&& f) const {
    auto const proj = views::transform(this->v, std::forward<F>(f));
    return *std::ranges::max_element(proj);
  }

  T min() const {
    return *std::min_element(this->v.begin(), this->v.end());
  }

  T max() const {
    return *std::max_element(this->v.begin(), this->v.end());
  }

  T gcd() const {
    return reduce(all(this->v), this->v[0], std::gcd<int, int>);
  }

  template <typename... Args>
  auto count(Args&&... args) {
    return std::count(this->v.begin(), this->v.end(), std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto count_if(Args&&... args) {
    return this->v.count_if(std::forward<Args>(args)...);
  }

  auto index(const T& x) {
    const auto it = std::find(this->v.begin(), this->v.end(), x);
    return idist(this->v.begin(), it) + offset;
  }

  auto ab(const list& other) {
    this->v.insert(this->v.end(), other.begin(), other.end());
  }

  auto af(const list& other) {
    this->v.insert(this->v.begin(), other.begin(), other.end());
  }

  template <class RNG>
  auto shuffle(RNG& gen) {
    std::shuffle(this->v.begin(), this->v.end(), gen);
  }

  bool has(T y) {
    return std::any_of(this->v.begin(), this->v.end(), [&](T x) { return x == y; });
  }

  bool every(T y) {
    return std::all_of(this->v.begin(), this->v.end(), [&](T x) { return x == y; });
  }

  void rotate_l(int idx) {
    std::rotate(this->v.begin(), this->v.begin() + idx, this->v.end());
  }

  void rotate_r(int idx) {
    std::rotate(this->v.rbegin(), this->v.rbegin() + idx, this->v.rend());
  }

  void erase(int idx) {
    this->v.erase(this->v.begin() + idx - offset);
  }

  auto span(int l, int r) {
    l -= offset;
    r -= offset;
    return std::span(this->v.begin() + l, r - l + 1);
  }
};
