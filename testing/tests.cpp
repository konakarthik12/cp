#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define NO_MAIN

#include "../template.cpp"
#include "DocTestExtension.cpp"
#include "doctest.h"
#include "utils.cpp"
using namespace quill::testing;


TEST_CASE("testing modint") {
  using Mi = ModInt<17>;
  Mi x = 11;
  Mi y = 12;
  CHECK(x + y == Mi(6));
  CHECK(x * y == Mi(13));
  CHECK((x * 3 + y) / 5 == Mi(9));
}

TEST_CASE("testing combinatorics") {
  Combo<ld_approx> combo(25);
  CHECK(combo.choose(12, 5) == 792);
  CHECK(combo.sum(10, 4) == 286);        // stars and bars
  CHECK(combo.sum(10, 4, false) == 84);  // zero not allowed
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
TEST_CASE("testing input") {
  redirectInput("test_input.txt");

  int n;
  vi arr;
  read(n);
  CHECK(n == 4);
  read(arr, n * 2);
  CHECK(arr == vi{1, 2, 3, 4, 5, 6, 7, 8});

  int m;
  string s;

  read(n, m, s);

  CHECK(s == "string-time");

  CHECK(n == 3);
  CHECK(m == 4);
  vvi arr2;
  read(arr2, n, m);

  vvi arr_ans{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
  CHECK(arr2 == arr_ans);

  wpii arr3;
  read(arr3, 3);
  CHECK(arr3 == wpii{{1, 1}, {2, 2}, {3, 3}});

  wc s1;
  read(s1, 7);
  CHECK(s1 == wc{'a', 'b', 'c', 'd', 'e', 'f', 'g'});
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
