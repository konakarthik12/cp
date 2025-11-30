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
TEST_SUITE("testing modint") {
  TEST_CASE("static mod") {
    using Mi = ModInt<17>;
    Mi x = 11;
    Mi y = 12;
    CHECK(x + y == Mi(6));
    CHECK(x * y == Mi(13));
    CHECK((x * 3 + y) / 5 == Mi(9));
  }

  TEST_CASE("dynamic mod") {
    using DMi = DynModInt;
    DMi::mod = 17;
    DMi x = 11;
    DMi y = 12;
    CHECK(x + y == DMi(6));
    CHECK(x * y == DMi(13));
    CHECK((x * 3 + y) / 5 == DMi(9));
  }

  TEST_CASE("mod double") {
    using Mi = ModDouble;
    Mi x = Mi(1) / Mi(2);
    Mi y = 2;
    CHECK(x + y == Mi(5) / Mi(2));
    CHECK(x * y == Mi(1));
  }
}

TEST_CASE("testing combinatorics") {
  Combo<Frac> combo(12);
  CHECK(combo.choose(12, 5) == 792);
  CHECK(combo.choose(20, 4) == 4845);
  CHECK(combo.choose(8, 8, 1) == 0);

  //  stars and bars
  CHECK(combo.sum(10, 4) == 286);
  CHECK(combo.sum(10, 4, false) == 84);

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
  CHECK(data3.sz() == 1);
  CHECK(data3[1] == 5);
  wec<int> data4;
  CHECK(data3);
  CHECK(!data4);

  www<int> nested(3, 4, 5);
  CHECK(nested.sz() == 3);
  CHECK(nested[1].sz() == 4);
  CHECK(nested[1][1].sz() == 5);

  www<int> nested_def(3, 4, 5, 2);
  CHECK(nested_def.sz() == 3);
  CHECK(nested_def[1].sz() == 4);
  CHECK(nested_def[1][1].sz() == 5);
  CHECK(nested_def[1][1][1] == 2);

}

TEST_SUITE("containers") {
  int big = 1e9;
  ll bigl = 1e9;
  vi ints = {big, big, big, big};
  vd doubles = {1.0, 2.0, 3.0};
  vb bools = {false, false, true, true};
  wll longs = {1, 2, 3, 4, 5};
  TEST_CASE("sum") {
    CHECK(ints.sum() == bigl * 4);

    CHECK(doubles.sum() == Approx(6));
    CHECK(same_as<decltype(ints.sum()), ll>);
    CHECK(same_as<decltype(doubles.sum()), double>);
  }

  TEST_CASE("prefix") {
    static_assert(same_as<decltype(pref_arr(bools)), vll>);
    CHECK(prefix_arr(bools) == vll{0, 0, 0, 1, 2});
    CHECK(prefix_arr(ints) == vll{0, bigl, bigl * 2, bigl * 3, bigl * 4});
    CHECK(prefix_arr(longs) == vll{0, 1, 3, 6, 10, 15});
    CHECK(prefix_arr(doubles)[3] == Approx(6));
    CHECK(pref_arr(longs) == wll{1, 3, 6, 10, 15});
    CHECK(diff_arr(longs) == wll{1, 1, 1, 1, 1});
    CHECK(diff_arr(pref_arr(longs)) == longs);
  }

  TEST_CASE("replace_first") {
    static_assert(same_as<replace_first<vec<int>, ll>, vec<ll>>);
    static_assert(same_as<replace_first<const vec<int>, ll>, vec<ll>>);
    static_assert(same_as<replace_first<wec<int>, ll>, wec<ll>>);
    static_assert(same_as<replace_first<const wec<int>, ll>, wec<ll>>);
    static_assert(same_as<replace_first<vec<ll>, int>, vec<int>>);
    static_assert(same_as<replace_first<vec<int>, double>, vec<double>>);
  }
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

  TEST_CASE("") {
    R"(
      abc def hij
    )"_cin_set;

    ws s_arr;
    read(s_arr, 3);
  }
}

TEST_SUITE("containers") {
  TEST_CASE("iota") {
    wi arr;
    arr.iota(1, 10);
    CHECK(arr[5] == 5);

    CHECK(arr.sum() == 55);
  }
  TEST_CASE("sort") {
    wpii arr{{1, 2}, {2, 1}};
    arr.rsort();
    CHECK(arr == wpii{{2, 1}, {1, 2}});
    arr.sort();
    CHECK(arr == wpii{{1, 2}, {2, 1}});
    auto lamb = [&](pii& a, pii& b) {
      return a.f < b.f;
    };
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
  vi arr = {1, 2, 3, 4, 5};
  vpii prs(arr | pairwise);

  CHECK(prs == vpii{{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  prs.clear();
  for (auto [a, b]: arr | pairwise | rview) {
    prs.eb(a, b);
  }
  CHECK(prs == vpii{{4, 5}, {3, 4}, {2, 3}, {1, 2}});


  vec<tuple<int, int, int>> arr2;
  arr2.sort(get<1>);
  CHECK(blen(15) == 4);
  CHECK(blen(16) == 5);

  assert(vi(3, 1e9).sum() == 3e9);
  assert(asum(1e9) == 500000000500000000);
  assert(asum(0) == 0);
  assert(asum(0, 0) == 0);
}

TEST_SUITE("Bool operators") {
  TEST_CASE("Bool |= Bool") {
    Bool a = false;
    Bool b = true;
    a |= b;
    CHECK(a == true);
  }

  TEST_CASE("Bool |= bool") {
    Bool a = false;
    bool b = true;
    a |= b;
    CHECK(a == true);
    
    Bool c = false;
    bool d = false;
    c |= d;
    CHECK(c == false);
  }

  TEST_CASE("vb[1] |= bool") {
    vb arr = {false, false, true, false};
    bool val = true;
    arr[1] |= val;
    CHECK(arr[1] == true);
  }

  TEST_CASE("vb[1] |= Bool") {
    vb arr = {false, false, true, false};
    Bool val = true;
    arr[1] |= val;
    CHECK(arr[1] == true);
  }
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
