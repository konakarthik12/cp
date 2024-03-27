#define DOCTEST_CONFIG_IMPLEMENT
#include "../template.cpp"
#include "doctest.h"
#include "test_utils.cpp"
using namespace doctest;
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
    CHECK(n == 4);
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
    string s;

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
    string s2;
    read(s1, 7, s2);

    CHECK(s1 == wc{'a', 'b', 'c', 'd', 'e', 'f', 'g'});
    CHECK(s2 == "hello");
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
  string output = GetCapturedStdout();
  CHECK(output == "5\n1 2 3 4 5\n4 3\n");
}

TEST_CASE("misc") {
  vi arr = {1, 2, 3, 4, 5};
  vpii prs;
  for (auto [a, b]: arr | pairwise) {
    prs.eb(a, b);
  }
  CHECK(prs == vpii{{1, 2}, {2, 3}, {3, 4}, {4, 5}});
}

void solve() {
  doctest::Context context;
  context.setOption("no-intro", true);
  int res = context.run();
  if (res != 0) exit(res);
}