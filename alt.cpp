#include "template.cpp"

using Mi = ModInt<(int) 1e9 + 7>;
struct Node {
  Mi a, b, c;
  Node(int h) {
    int x = 1 << h;
    a = b = c = Mi(2, x);
  }
  Node(Mi a, Mi b, Mi c) : a(a), b(b), c(c) {
  }

  void mask(int t) {
    if (t == 0) return;
    if (t != 1) a = 0;
    if (t != 2) b = 0;
    if (t != 3) c = 0;
  }
};
Node merge(Node& a, Node& b) {
  return {(a.b + a.c) * (b.b + b.c), (a.a + a.c) * (b.a + b.c), (a.b + a.c) * (b.b + b.c)};
}
void solve(int) {
  int k;
  read(k);

  int n;
  read(n);

  // set<pr<ll, wi>> r;
  mlli t;
  sll focus;
  for (int i = 1; i <= n; i++) {
    int v;
    str s;
    read(v, s);

    int ty;
    if (s == "white" || s == "yellow") {
      ty = 1;
    } else if (s == "blue" || s == "green") {
      ty = 2;
    } else {
      ty = 3;
    }

    t[v] = ty;
    while (v) {
      focus.ps(v);
      v <<= 1;
    }
  }

  map<ll, Node> hold;
  while (focus) {
    ll x = focus.rb();
    int w = blen(x);
    int h = k - w + 1;
    if (w == k) {
      hold[x] = Node(w);
      hold[x].mask(t[x]);
      continue;
    }
    assert(h > 1);
    Node l(h - 1), r(h - 1);
    if (auto iter = hold.find(x * 2); iter != hold.end()) {
      l = iter->second;
    }
    if (auto iter = hold.find(x * 2 + 1); iter != hold.end()) {
      r = iter->second;
    }
    hold[x] = merge(l, r);
    hold[x].mask(t[x]);
  }
}
