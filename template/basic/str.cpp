#pragma once
#include "../scaffold.cpp"
#include "../concepts.cpp"
#include "../deb_raw.cpp"
template <int offset>
struct str_raw {
  using value_type = char;
  std::string s;

  str_raw() {
  }

  explicit str_raw(int size, char init = '\0') : s(size, init) {
  }

  str_raw(const char* cstr) : s(cstr) {
  }

  str_raw(const std::string& other) : s(other) {
  }

  str_raw(std::string&& other) : s(std::move(other)) {
  }

  template <input_iterator Iter>
  str_raw(Iter start, Iter end) : s(start, end) {
  }

  template <HasIter Container>
  explicit str_raw(const Container& cnt) : s(cnt.begin(), cnt.end()) {
  }

  str_raw(initializer_list<char> initList) : s(initList) {
  }

  auto begin() const {
    return this->s.begin();
  }

  auto end() const {
    return this->s.end();
  }

  auto begin() {
    return this->s.begin();
  }

  auto end() {
    return this->s.end();
  }

  auto rbegin() const {
    return this->s.rbegin();
  }

  auto rend() const {
    return this->s.rend();
  }

  auto rbegin() {
    return this->s.rbegin();
  }

  auto rend() {
    return this->s.rend();
  }

  char& front() {
    return this->s.front();
  }

  const char& front() const {
    return this->s.front();
  }

  char& back() {
    return this->s.back();
  }

  const char& back() const {
    return this->s.back();
  }

  int sz() const {
    return static_cast<int>(this->s.size());
  }

  int length() const {
    return sz();
  }

  bool empty() const {
    return this->s.empty();
  }

  explicit operator bool() const {
    return !this->empty();
  }

  char& operator[](int idx) {
    int index = idx - offset;
    dssert(index >= 0 && index < this->sz());
    return this->s[index];
  }

  const char& operator[](int idx) const {
    int index = idx - offset;
    dssert(index >= 0 && index < this->sz());
    return this->s[index];
  }

  char& at(int idx) {
    return (*this)[idx];
  }

  const char& at(int idx) const {
    return (*this)[idx];
  }

  void reserve(int size) {
    this->s.reserve(size);
  }

  void resize(int size, char c = '\0') {
    this->s.resize(size, c);
  }

  void assign(const str_raw& other) {
    this->s = other.s;
  }

  void assign(const std::string& other) {
    this->s = other;
  }

  void assign(const char* cstr) {
    this->s = cstr;
  }

  void fill(char c) {
    std::fill(s.begin(), s.end(), c);
  }

  void pb(char c) {
    this->s.push_back(c);
  }

  void append(const str_raw& other) {
    this->s.append(other.s);
  }

  void append(const std::string& other) {
    this->s.append(other);
  }

  void append(const char* cstr) {
    this->s.append(cstr);
  }

  void append(char c) {
    this->s.push_back(c);
  }

  void ab(const str_raw& other) {
    append(other);
  }

  void clear() {
    this->s.clear();
  }

  bool operator==(const str_raw& other) const {
    return s == other.s;
  }

  bool operator==(const std::string& other) const {
    return s == other;
  }

  friend bool operator==(const std::string& lhs, const str_raw& rhs) {
    return lhs == rhs.s;
  }

  bool operator==(const char* other) const {
    return s == other;
  }

  friend bool operator==(const char* lhs, const str_raw& rhs) {
    return lhs == rhs.s;
  }
  friend istream& operator>>(istream& in, str_raw& str) {
    in >> str.s;
    return in;
  }


  str_raw operator+(const str_raw& other) const {
    str_raw result = *this;
    result.append(other);
    return result;
  }

  str_raw& operator+=(const str_raw& other) {
    append(other);
    return *this;
  }

  str_raw& operator+=(char c) {
    pb(c);
    return *this;
  }

  str_raw& operator+=(const char* cstr) {
    append(cstr);
    return *this;
  }

  str_raw substr(int pos, int len = -1) const {
    pos -= offset;
    dssert(pos >= 0 && pos <= sz());
    if (len == -1) {
      len = sz() - pos;
    }
    dssert(len >= 0 && pos + len <= sz());
    return str_raw(s.substr(pos, len));
  }

  int find(const str_raw& pattern, int start = 1) const {
    start -= offset;
    dssert(start >= 0 && start <= sz());
    size_t pos = s.find(pattern.s, start);
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find(const char* pattern, int start = 1) const {
    start -= offset;
    dssert(start >= 0 && start <= sz());
    size_t pos = s.find(pattern, start);
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find(char c, int start = 1) const {
    start -= offset;
    dssert(start >= 0 && start <= sz());
    size_t pos = s.find(c, start);
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int rfind(const str_raw& pattern, int start = -1) const {
    size_t pos;
    if (start == -1) {
      pos = s.rfind(pattern.s);
    } else {
      start -= offset;
      dssert(start >= 0 && start <= sz());
      pos = s.rfind(pattern.s, start);
    }
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int rfind(const char* pattern, int start = -1) const {
    size_t pos;
    if (start == -1) {
      pos = s.rfind(pattern);
    } else {
      start -= offset;
      dssert(start >= 0 && start <= sz());
      pos = s.rfind(pattern, start);
    }
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int rfind(char c, int start = -1) const {
    size_t pos;
    if (start == -1) {
      pos = s.rfind(c);
    } else {
      start -= offset;
      dssert(start >= 0 && start <= sz());
      pos = s.rfind(c, start);
    }
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_first_of(const str_raw& chars, int start = 1) const {
    start -= offset;
    dssert(start >= 0 && start <= sz());
    size_t pos = s.find_first_of(chars.s, start);
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_first_of(const char* chars, int start = 1) const {
    start -= offset;
    dssert(start >= 0 && start <= sz());
    size_t pos = s.find_first_of(chars, start);
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_first_of(char c, int start = 1) const {
    return find(c, start);
  }

  int find_last_of(const str_raw& chars, int start = -1) const {
    size_t pos;
    if (start == -1) {
      pos = s.find_last_of(chars.s);
    } else {
      start -= offset;
      dssert(start >= 0 && start <= sz());
      pos = s.find_last_of(chars.s, start);
    }
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_last_of(const char* chars, int start = -1) const {
    size_t pos;
    if (start == -1) {
      pos = s.find_last_of(chars);
    } else {
      start -= offset;
      dssert(start >= 0 && start <= sz());
      pos = s.find_last_of(chars, start);
    }
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_first_not_of(const str_raw& chars, int start = 1) const {
    start -= offset;
    dssert(start >= 0 && start <= sz());
    size_t pos = s.find_first_not_of(chars.s, start);
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_first_not_of(const char* chars, int start = 1) const {
    start -= offset;
    dssert(start >= 0 && start <= sz());
    size_t pos = s.find_first_not_of(chars, start);
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_last_not_of(const str_raw& chars, int start = -1) const {
    size_t pos;
    if (start == -1) {
      pos = s.find_last_not_of(chars.s);
    } else {
      start -= offset;
      dssert(start >= 0 && start <= sz());
      pos = s.find_last_not_of(chars.s, start);
    }
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  int find_last_not_of(const char* chars, int start = -1) const {
    size_t pos;
    if (start == -1) {
      pos = s.find_last_not_of(chars);
    } else {
      start -= offset;
      dssert(start >= 0 && start <= sz());
      pos = s.find_last_not_of(chars, start);
    }
    if (pos == std::string::npos) {
      return -1;
    }
    return static_cast<int>(pos) + offset;
  }

  void replace(int pos, int len, const str_raw& replacement) {
    pos -= offset;
    dssert(pos >= 0 && pos <= sz());
    dssert(len >= 0 && pos + len <= sz());
    s.replace(pos, len, replacement.s);
  }

  void replace(int pos, int len, const std::string& replacement) {
    pos -= offset;
    dssert(pos >= 0 && pos <= sz());
    dssert(len >= 0 && pos + len <= sz());
    s.replace(pos, len, replacement);
  }

  void replace(int pos, int len, const char* replacement) {
    pos -= offset;
    dssert(pos >= 0 && pos <= sz());
    dssert(len >= 0 && pos + len <= sz());
    s.replace(pos, len, replacement);
  }

  void replace(int pos, int len, char c) {
    pos -= offset;
    dssert(pos >= 0 && pos <= sz());
    dssert(len >= 0 && pos + len <= sz());
    s.replace(pos, len, 1, c);
  }

  void erase(int pos, int len = 1) {
    pos -= offset;
    dssert(pos >= 0 && pos <= sz());
    dssert(len >= 0 && pos + len <= sz());
    s.erase(pos, len);
  }

  void insert(int pos, const str_raw& other) {
    pos -= offset;
    if (pos < 0) pos += sz();
    dssert(pos >= 0 && pos <= sz());
    s.insert(pos, other.s);
  }

  void insert(int pos, const std::string& other) {
    pos -= offset;
    if (pos < 0) pos += sz();
    dssert(pos >= 0 && pos <= sz());
    s.insert(pos, other);
  }

  void insert(int pos, const char* other) {
    pos -= offset;
    if (pos < 0) pos += sz();
    dssert(pos >= 0 && pos <= sz());
    s.insert(pos, other);
  }

  void insert(int pos, char c) {
    pos -= offset;
    if (pos < 0) pos += sz();
    dssert(pos >= 0 && pos <= sz());
    s.insert(pos, 1, c);
  }

  void reverse() {
    std::reverse(s.begin(), s.end());
  }

  void sort() {
    std::sort(s.begin(), s.end());
  }

  bool has(char c) {
    return find(c) != -1;
  }

  bool has(const str_raw& pattern) {
    return find(pattern) != -1;
  }

  bool starts_with(const str_raw& prefix) const {
    return s.starts_with(prefix.s);
  }

  bool starts_with(const char* prefix) const {
    return s.starts_with(prefix);
  }

  bool starts_with(char c) const {
    return !empty() && front() == c;
  }

  bool ends_with(const str_raw& suffix) const {
    return s.ends_with(suffix.s);
  }

  bool ends_with(const char* suffix) const {
    return s.ends_with(suffix);
  }

  bool ends_with(char c) const {
    return !empty() && back() == c;
  }

  template <typename Pred>
  void erase_if(Pred p) {
    s.erase(std::remove_if(s.begin(), s.end(), p), s.end());
  }

  void erase_all(char c) {
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
  }

  str_raw trim_left(const str_raw& chars = str_raw(" \t\n\r")) {
    int start = find_first_not_of(chars);
    if (start == -1) {
      clear();
      return *this;
    }
    erase(1, start - 1);
    return *this;
  }

  str_raw trim_right(const str_raw& chars = str_raw(" \t\n\r")) {
    int end = find_last_not_of(chars);
    if (end == -1) {
      clear();
      return *this;
    }
    erase(end + 1, sz() - end);
    return *this;
  }

  str_raw trim(const str_raw& chars = str_raw(" \t\n\r")) {
    trim_left(chars);
    trim_right(chars);
    return *this;
  }

  operator std::string() const {
    return s;
  }

  operator const char*() const {
    return s.c_str();
  }

  const char* c_str() const {
    return s.c_str();
  }

  const std::string& std_str() const {
    return s;
  }

  std::string& std_str() {
    return s;
  }
};

using str = str_raw<1>;
