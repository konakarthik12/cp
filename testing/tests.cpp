#define DOCTEST_CONFIG_IMPLEMENT
#define NO_MAIN
#include "../template.cpp"
#include "doctest.h"
#include "test_utils.cpp"
using namespace doctest;

int main(int argc, char** argv) {
  Context context;
  context.setOption("no-intro", true);
  context.applyCommandLine(argc, argv);
  init_main();
  int res = context.run();

  if (context.shouldExit()) return res;

  return res;
}
TEST_CASE("testing modint") {
  using Mi = ModInt<17>;
  Mi x = 11;
  Mi y = 12;
  CHECK(x + y == Mi(6));
  CHECK(x * y == Mi(13));
  CHECK((x * 3 + y) / 5 == Mi(9));
}

TEST_CASE("testing combinatorics") {
  Combo<Frac> combo(12);
  CHECK(combo.choose(12, 5) == 792);
  CHECK(combo.choose(20, 4) == 4845);
  CHECK(combo.choose(8, 8, 1) == 0);

  //  stars and bars
  CHECK(combo.sum(10, 4) == 286);        // zero not allowed
  CHECK(combo.sum(10, 4, false) == 84);  // zero not allowed

  Combo<ModInt<17>> combo2(3);
  CHECK(combo2.bin(20) == (1 << 20) % 17);
}

TEST_CASE("vectors") {
  vi arr = {1, 2, 3, 4, 5};
  wi arr2 = {1, 2, 3, 4, 5};
  CHECK(arr[3] == 4);
  CHECK(arr2[3] == 3);
  arr.front()++;
  arr.back()--;
  arr2.front()++;
  arr2.back()--;
  CHECK(arr[0] == 2);
  CHECK(arr[4] == 4);
  CHECK(arr2[1] == 2);
  CHECK(arr2[5] == 4);

  vec<bool> data = {0, 1, 0, 1};
  wec<bool> data2 = {0, 0, 1, 1};
  CHECK(data[1] == 1);
  CHECK(data2[2] == 0);
  wec<int> data3 = {5};
  CHECK(sz(data3) == 1);
  CHECK(data3[1] == 5);
  wec<int> data4;
  CHECK(data3);
  CHECK(!data4);
}

TEST_CASE("containers") {
  vi arr = {1, 2, 3};
  CHECK(sum(arr) == 6);

  vd arr2 = {1.0, 2.0, 3.0};
  CHECK(sum(arr) == Approx(6));
  CHECK(sum(arr) == Approx(6));
  CHECK(same_as<decltype(sum(arr)), ll>);
  CHECK(same_as<decltype(sum(arr2)), double>);
}

TEST_SUITE("input") {
  TEST_CASE("fastio") {
    CHECK(cin.tie() == nullptr);
    CHECK(ios_base::sync_with_stdio() == false);
    ios_base::sync_with_stdio(false);
  }
  TEST_CASE("") {
    R"(
       4
       1 2 3 4 5 6 7 8
    )"_cin_set;

    int n;
    vi arr;
    read(n);
    read(arr, n * 2);
    CHECK(arr == vi{1, 2, 3, 4, 5, 6, 7, 8});
  }

  TEST_CASE("") {
    R"(
      3 4
      string-time
      1 2 3 4
      5 6 7 8
      9 10 11 12
    )"_cin_set;
    int n, m;
    str s;

    read(n, m, s);

    CHECK(n == 3);
    CHECK(m == 4);
    CHECK(s == "string-time");

    vvi arr2;
    read(arr2, n, m);
    vvi arr_ans{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    CHECK(arr2 == arr_ans);
  }
  TEST_CASE("") {
    R"(
      1 1
      2 2
      3 3
    )"_cin_set;
    wpii arr3;
    read(arr3, 3);
    CHECK(arr3 == wpii{{1, 1}, {2, 2}, {3, 3}});
  }
  TEST_CASE("") {
    R"(
      abcdefg
      hello
    )"_cin_set;
    wc s1;
    str s2;
    read(s1, 7, s2);

    CHECK(s1 == wc{'a', 'b', 'c', 'd', 'e', 'f', 'g'});
    CHECK(s2 == "hello");
  }
}

TEST_SUITE("containers") {
  TEST_CASE("iota") {
    wi arr;
    arr.iota(1, 10);
    CHECK(arr[5] == 5);

    CHECK(sum(arr) == 55);
  }
  TEST_CASE("sort") {
    wpii arr{{1, 2}, {2, 1}};
    arr.rsort();
    CHECK(arr == wpii{{2, 1}, {1, 2}});
    arr.sort();
    CHECK(arr == wpii{{1, 2}, {2, 1}});
    auto lamb = [&](pii& a, pii& b) { return a.f < b.f; };
    arr.sort(lamb);
    CHECK(arr == wpii{{1, 2}, {2, 1}});
    arr.sort(&pii::s);
    CHECK(arr == wpii{{2, 1}, {1, 2}});
  }
}

TEST_CASE("testing_output") {
  CaptureStdout();
  int x = 5;
  vi arr = {1, 2, 3, 4, 5};
  wi arr1 = {1, 2, 3, 4, 5};
  println(x);
  println(arr);
  println(arr[3], arr1[3]);
  str output = GetCapturedStdout();
  CHECK(output == "5\n1 2 3 4 5\n4 3\n");
}

TEST_CASE("misc") {
//  vi arr = {1, 2, 3, 4, 5};
//  vpii prs;
//  for (auto [a, b]: arr | pairwise) {
//    prs.eb(a, b);
//  }
//  CHECK(prs == vpii{{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  prs.clear();
  for (auto [a, b]: arr | pairwise | rview) {
    prs.eb(a, b);
  }
  CHECK(prs == vpii{{4, 5}, {3, 4}, {2, 3}, {1, 2}});
  CHECK(blen(15) == 4);
  CHECK(blen(16) == 5);

  assert(sum(vi(3, 1e9)) == 3e9);
  assert(asum(4) == 10);
  assert(asum(0) == 0);
  assert(asum(0, 0) == 0);
}

void solve() {
  doctest::Context context;
  context.setOption("no-intro", true);
  int res = context.run();
  if (res != 0) exit(res);
}

namespace doctest {
template <Readable1D T>
struct StringMaker<T> {
  static String convert(const T& value) {
    ostream* old = dout;
    stringstream sstream;
    dout = &sstream;
    debug_all(value);
    dout = old;
    return String(sstream.str().c_str());
  }
};
}  // namespace doctest
