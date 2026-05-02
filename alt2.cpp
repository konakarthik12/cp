#include "template.cpp"

auto solve(int) {
  int n;
  read(n);

  wb arr;
  read(arr, n);

  int cur = 1;
  int cnt = 0;
  wpii track;
  for (int i = 1; i <= n; i++) {
    if (arr[i] == cur) {
      cnt++;
      continue;
    } else {
      if (cur == 0) {
        track.eb(i - cnt, i - 1);
      }
      cnt = 1;
      cur = arr[i];
    }
  }
  if (cur == 0) {
    track.eb(n - cnt + 1, n);
  }
  deb(track);

  // assert(track.sum() == n);
  // assert(track.sz() % 2 == 1);
  int ans = 0;
  for (auto [l_idx, r_idx]: track) {
    int l = l_idx - 1;
    int r = n - r_idx;
    int m = r_idx - l_idx + 1;

    deb(l_idx, m, r_idx);
    deb(l, m, r);
    int top_res = (ll) asum(m - 1) + l * m;
    int bot_res = (ll) asum(m - 1) + r * m;
    if (l > 0) top_res++;
    if (r > 0) bot_res++;
    deb(top_res, bot_res);
    int res = max(top_res, bot_res);
    ans = max(ans, res);
  }
  return ans;
}
