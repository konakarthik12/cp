#include "template.cpp"

int attempt(wi& group) {
  int n = group.sz();
  if (group.sz() == 1) return 0;

  wi best_kep(n, n + 1), best_del(n, n + 1);
  best_kep[1] = 0;
  best_del[1] = group[1];

  for (int i = 2; i <= n; i++) {
    int x = group[i];
    best_kep[i] = min(best_kep[i], best_del[i - 1]);
    best_del[i] = min(best_del[i], min(best_del[i - 1], best_kep[i - 1]) + x);
  }
  deb(best_kep);
  deb(best_del);
  int res = min(best_kep[n], best_del[n]);
  deb(group, res);
  return res;
}
auto solve(int) {
  int n;
  read(n);
  mii cnt;
  read_cnt(cnt, n);

  wwi groups;
  wi cur;
  cur.pb(cnt.front().second);
  for (auto [a, b]: cnt | pairwise) {
    auto [ax, ac] = a;
    auto [bx, bc] = b;
    int g = bx - ax;
    assert(g >= 1);
    if (g != 1) {
      groups.pb(cur);
      cur.clear();
    }
    cur.pb(bc);
  }
  groups.pb(cur);

  deb(groups);
  int ans = 0;
  for (wi& group: groups) {
    ans += attempt(group);
  }
  return ans;
}
