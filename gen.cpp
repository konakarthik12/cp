#include "gen_template.cpp"
int dist(int a, int b, int x, int y) {
  int x_dist = abs(a - x);
  int y_dist = abs(b - y);

  return max(x_dist, y_dist);
}
void generate() {
  int q = rnd(1, 1);
  println(q);
  for (int i = 0; i < q; i++) {
    println();
    int n = rnd(1, 30);
    println(n);
    flush();
    for (int j = 0; j < 15; j++) {
      char t;
      read(t);
      assert(t == '?' || t == '!');
      int a, b;
      read(a, b);

      assert(1 <= a && a <= r);
      assert(1 <= b && b <= c);
      if (t == '?') {
        println(dist(x, y, a, b));
        flush();
      } else {
        assert(a == x);
        assert(b == y);
        goto done;
      }
    }
    assert(false);
  done:;
  }
}
