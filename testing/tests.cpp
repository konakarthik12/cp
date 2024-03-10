#define NO_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../template.cpp"
#include "DocTestExtension.cpp"
#include "doctest.h"

TEST_CASE("testing combinatorics") {
  Combo<ld> combo(25);
  CHECK(combo.choose(12, 5) == 792);
}

TEST_CASE("testing input") {
  int n;

  vi arr;
  read(n);
  read(arr, n * 2);
  CHECK(n == 4);
  CHECK(arr == vi{1, 2, 3, 4, 5, 6, 7, 8});

  int m;
  string s;

  read(n, m, s);

  CHECK(s == "string-time");

  CHECK(n == 3);
  CHECK(m == 4);
  vvi arr2;
  read(s, arr, n, m);

  //    vvi arr_ans{{1, 2,  3,  4},
  //                {5, 6,  7,  8},
  //                {9, 10, 11, 12}};
  //
  //    CHECK(arr2 == arr_ans);

  //    wpii arr3;
  //    read(arr3, 3);
  //    CHECK(arr3 == wpii{{1, 1},
  //                       {2, 2},
  //                       {3, 3}});
  //
  //    wc s1;
  //    read(s1, 7);
  //    CHECK(s1 == wc{'a', 'b', 'c', 'd', 'e', 'f', 'g'});
}

TEST_CASE("testing_output") {
  using namespace quill::testing;
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