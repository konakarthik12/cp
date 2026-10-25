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
  CHECK(combo.fact(3) == Frac(6));
  CHECK(Frac(1, 3) < Frac(1, 2));
  CHECK(Frac(-1, 2) < Frac(1, 3));
  CHECK_FALSE(Frac(2, 3) < Frac(4, 6));
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

  TEST_CASE("foreach") {
    double total = 0;
    for (double& x: doubles) total += x;

    CHECK(total == Approx(6.0));
  }
  TEST_CASE("sum") {
    CHECK(ints.sum() == bigl * 4);
    CHECK(bools.sum() == 2);
    CHECK(doubles.sum() == Approx(6));
    CHECK(same_as<decltype(ints.sum()), ll>);
    CHECK(same_as<decltype(doubles.sum()), double>);
  }

  TEST_CASE("prefix") {
    static_assert(same_as<decltype(pref_arr(bools)), vi>);
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

  TEST_CASE("map") {
    vi nums = {1, 2, 3, 4, 5};
    auto squared = nums.map([](int x) { return x * x; });
    CHECK(squared == vi{1, 4, 9, 16, 25});

    wi nums2 = {2, 3, 4};
    auto alt = nums2.map([](int x) { return (char) ('a' + x); });
    CHECK(alt == wc{'c', 'd', 'e'});
  }

  TEST_CASE("max") {
    vi nums = {1, 2, 3, 4, 5};
    CHECK(nums.max() == 5);
    auto squared = [](int x) {
      return x * x;
    };

    CHECK(nums.max(squared) == 25);
    vpii pairs = {{1, 2}, {3, 1}, {2, 4}};
    CHECK(pairs.max(&pii::s) == 4);
  }

  TEST_CASE("PreSum") {
    vi arr = {1, 2, 3, 4, 5};
    PreSum ps_vi(arr);
    CHECK(ps_vi.query(0, 2) == 6);   // 1 + 2 + 3
    CHECK(ps_vi.query(1, 4) == 14);  // 2 + 3 + 4 + 5
    CHECK(ps_vi.prefix(3) == 10);    // 1 + 2 + 3 + 4

    wi arr2 = {1, 2, 3, 4, 5};
    PreSum ps_wi(arr2);
    static_assert(std::same_as<decltype(ps_wi), PreSum<ll, 1>>);
    CHECK(ps_wi.query(1, 3) == 6);   // 1 + 2 + 3
    CHECK(ps_wi.query(2, 5) == 14);  // 2 + 3 + 4 + 5
    CHECK(ps_wi.prefix(4) == 10);    // 1 + 2 + 3 + 4

    vb flags = {true, false, true, true};
    PreSum ps_vb(flags);
    static_assert(std::same_as<decltype(ps_vb), PreSum<int, 0>>);
    CHECK(ps_vb.query(0, 3) == 3);
    CHECK(ps_vb.query(1, 2) == 1);
    CHECK(ps_vb.prefix(2) == 2);

    wb flags2 = {true, false, true, true};
    PreSum ps_wb(flags2);
    static_assert(std::same_as<decltype(ps_wb), PreSum<int, 1>>);
    CHECK(ps_wb.query(1, 4) == 3);
    CHECK(ps_wb.query(2, 3) == 1);
    CHECK(ps_wb.prefix(3) == 2);
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
    str_raw<1> s;

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
    str_raw<1> s2;
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

  TEST_CASE("pqueue") {
    pqueue<int> pq;
    CHECK(pq.empty());
    CHECK(pq.sz() == 0);
    CHECK(!pq);

    pq.ps(3);
    pq.ps(1);
    pq.ps(4);
    pq.ps(1);
    pq.ps(5);

    CHECK(!pq.empty());
    CHECK(pq.sz() == 5);
    CHECK(pq.top() == 5);

    CHECK(pq.rm() == 5);
    CHECK(pq.rm() == 4);
    CHECK(pq.rm() == 3);
    CHECK(pq.sz() == 2);

    pqueue<int> pq2{9, 2, 7, 1};
    CHECK(pq2.top() == 9);
    CHECK(pq2.sz() == 4);

    vi vec = {6, 2, 8, 3};
    pqueue<int> pq3(vec);
    CHECK(pq3.top() == 8);
    CHECK(pq3.sz() == 4);

    pq3.clear();
    CHECK(pq3.empty());

    // Test with greater comparator (min heap)
    pqueue<int, greater<int>> min_pq{5, 2, 8, 1};
    CHECK(min_pq.top() == 1);
    CHECK(min_pq.rm() == 1);
    CHECK(min_pq.rm() == 2);
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
  str_raw<1> output = GetCapturedStdout();
  CHECK(output == "5\n1 2 3 4 5\n4 3\n");
}

TEST_SUITE("views") {
  TEST_CASE("pairwise") {
    vi arr = {1, 2, 3, 4, 5};
    vpii prs(arr | pairwise);

    CHECK(prs == vpii{{1, 2}, {2, 3}, {3, 4}, {4, 5}});
    prs.clear();
    for (auto [a, b]: arr | pairwise | rview) {
      prs.eb(a, b);
    }
    CHECK(prs == vpii{{4, 5}, {3, 4}, {2, 3}, {1, 2}});
  }

  TEST_CASE("values") {
    vpii v{{1, 10}, {2, 20}, {3, 30}};

    for (auto& s: v | sview) {
      s += 1;
    }

    vi result;
    for (auto s: v | sview) {
      result.pb(s);
    }
    CHECK(result == vi{11, 21, 31});
  }
}

TEST_CASE("misc") {
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

TEST_SUITE("container hierarchy") {
  TEST_CASE("vec inherits from list") {
    vec<int> v;
    v.pb(1);
    v.pb(2);
    v.eb(3);
    CHECK(v.sz() == 3);
    CHECK(v[0] == 1);
    CHECK(v.sum() == 6);
    v.sort();
    CHECK(v.is_sorted());
    v.flip();
    CHECK(v == vi{3, 2, 1});
  }

  TEST_CASE("wec inherits from vec/list") {
    wec<int> w;
    w.pb(10);
    w.pb(20);
    w.pb(30);
    CHECK(w.sz() == 3);
    CHECK(w[1] == 10);  // 1-indexed
    CHECK(w[3] == 30);
    CHECK(w.sum() == 60);
    w.sort();
    CHECK(w.is_sorted());
  }

  TEST_CASE("deq inherits from list") {
    deq<int> d;
    d.pb(2);
    d.pf(1);  // deq-specific
    d.pb(3);
    CHECK(d.sz() == 3);
    CHECK(d[1] == 1);  // 1-indexed
    CHECK(d[3] == 3);
    CHECK(d.rf() == 1);  // deq-specific remove front
    CHECK(d.rb() == 3);
    CHECK(d.sz() == 1);
    CHECK(d.sum() == 2);
  }

  TEST_CASE("stack inherits from wec") {
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    CHECK(st.sz() == 3);
    CHECK(st.top() == 3);
    CHECK(st.pop() == 3);
    CHECK(st.pop() == 2);
    CHECK(st.sz() == 1);
    // Can still use list operations
    CHECK(st.sum() == 1);
  }

  TEST_CASE("set inherits from Con") {
    set<int> s;
    s.ps(3);
    s.ps(1);
    s.ps(2);
    CHECK(s.sz() == 3);
    CHECK(s.has(2));
    CHECK(!s.has(5));
    CHECK(s.front() == 1);
    CHECK(s.back() == 3);
    CHECK(s.rf() == 1);  // remove front
    CHECK(s.rb() == 3);  // remove back
    CHECK(s.sz() == 1);
    // Iterators from Con
    int sum = 0;
    for (auto x: s) sum += x;
    CHECK(sum == 2);
  }

  TEST_CASE("mset inherits from set") {
    mset<int> ms;
    ms.ps(1);
    ms.ps(1);
    ms.ps(2);
    CHECK(ms.sz() == 3);
    CHECK(ms.has(1));
    CHECK(ms.erase_one(1));
    CHECK(ms.sz() == 2);
    CHECK(ms.has(1));  // still has one more
    ms.erase_all(1);
    CHECK(!ms.has(1));
    CHECK(ms.sz() == 1);
  }

  TEST_CASE("map container") {
    map<int, int> m;
    m[1] = 10;
    m[2] = 20;
    m[3] = 30;
    CHECK(m.sz() == 3);
    CHECK(m.has(2));
    CHECK(!m.has(5));
    CHECK(m[2] == 20);
    CHECK(m.get(2) == 20);
    CHECK(m.get(5, -1) == -1);  // default value
    CHECK(m.front().first == 1);
    CHECK(m.back().first == 3);
    // Iterators from Con concept
    int key_sum = 0;
    for (auto& [k, v]: m) key_sum += k;
    CHECK(key_sum == 6);
  }

  TEST_CASE("set lower/upper bound") {
    set<int> s{1, 3, 5, 7, 9};
    CHECK(s.ge(4) == 5);  // >= 4
    CHECK(s.gr(5) == 7);  // > 5
    CHECK(s.le(6) == 5);  // <= 6
    CHECK(s.ls(5) == 3);  // < 5
  }

  TEST_CASE("list lower/upper bound (sorted array)") {
    vi v{1, 3, 5, 7, 9};
    CHECK(v.ge(4) == 5);  // >= 4
    CHECK(v.gr(5) == 7);  // > 5
    CHECK(v.le(6) == 5);  // <= 6
    CHECK(v.ls(5) == 3);  // < 5
  }
}
