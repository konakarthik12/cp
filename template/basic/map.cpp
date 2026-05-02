#pragma once
#include "../concepts.cpp"
#include "con.cpp"
#include "pair.cpp"

template <typename K, typename V, typename Comp = less<K>>
struct map {
  std::map<K, V, Comp> v;
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const K, V>;

  map() {
  }

  map(const std::map<K, V, Comp>& m) : v(m) {
  }

  map(const map& m) : v(m.v) {
  }

  map(map&& m) : v(std::move(m.v)) {
  }

  map(initializer_list<std::pair<const K, V>> initList) : v(initList) {
  }

  template <typename Iter>
    requires input_iterator<Iter>
  map(Iter start, Iter end) : v(start, end) {
  }

  template <HasIter Container>
  explicit map(const Container& cnt) : v(cnt.begin(), cnt.end()) {
  }

  map& operator=(const map& m) {
    v = m.v;
    return *this;
  }

  map& operator=(map&& m) {
    v = std::move(m.v);
    return *this;
  }

  // Iterators (from Con concept)
  auto begin() const {
    return v.begin();
  }

  auto end() const {
    return v.end();
  }

  auto begin() {
    return v.begin();
  }

  auto end() {
    return v.end();
  }

  auto rbegin() const {
    return v.rbegin();
  }

  auto rend() const {
    return v.rend();
  }

  auto rbegin() {
    return v.rbegin();
  }

  auto rend() {
    return v.rend();
  }

  // Size operations (from Con concept)
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
    v.clear();
  }

  bool operator==(const map& other) const {
    return v == other.v;
  }

  // Map-specific access
  V& operator[](const K& key) {
    return v[key];
  }

  V& at(const K& key) {
    return v.at(key);
  }

  const V& at(const K& key) const {
    return v.at(key);
  }

  // Front/back access
  auto front() {
    return *v.begin();
  }

  auto back() {
    return *v.rbegin();
  }

  auto front() const {
    return *v.begin();
  }

  auto back() const {
    return *v.rbegin();
  }

  // Remove front/back
  auto rf() {
    auto x = *v.begin();
    v.erase(v.begin());
    return x;
  }

  auto rb() {
    auto iter = prev(v.end());
    auto x = *iter;
    v.erase(iter);
    return x;
  }

  // Insert/emplace
  template <typename... Args>
  auto insert(Args&&... args) {
    return v.insert(std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto emplace(Args&&... args) {
    return v.emplace(std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto try_emplace(const K& key, Args&&... args) {
    return v.try_emplace(key, std::forward<Args>(args)...);
  }

  // Erase
  auto erase(const K& key) {
    return v.erase(key);
  }

  template <typename U>
  auto erase(U&& x) {
    return v.erase(std::forward<U>(x));
  }

  // Lookup
  auto has(const K& key) const {
    return v.contains(key);
  }

  auto find(const K& key) {
    return v.find(key);
  }

  auto find(const K& key) const {
    return v.find(key);
  }

  auto lower_bound(const K& key) {
    return v.lower_bound(key);
  }

  auto upper_bound(const K& key) {
    return v.upper_bound(key);
  }

  auto lower_bound(const K& key) const {
    return v.lower_bound(key);
  }

  auto upper_bound(const K& key) const {
    return v.upper_bound(key);
  }

  // Get value or default
  V get(const K& key, const V& default_val = V()) const {
    auto it = v.find(key);
    return it != v.end() ? it->second : default_val;
  }

  // Merge
  auto merge(map<K, V, Comp>& other) {
    return v.merge(other.v);
  }

  // Keys and values views
  auto keys() const {
    return v | views::transform([](const auto& p) { return p.first; });
  }

  auto values() {
    return v | views::transform([](auto& p) -> V& { return p.second; });
  }

  auto values() const {
    return v | views::transform([](const auto& p) { return p.second; });
  }
};
