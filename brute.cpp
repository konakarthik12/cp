#include "template/template.cpp"
int n;
vi people;
vi used;
// vi open;
using state = bitset<200>;
map<int, map<string, int>> dp;
int recurse(int cur, state open) {
  if (cur == sz(people)) {
    return 0;
  }
  if (dp[cur][open.to_string()]) {
    return dp[cur][open.to_string()];
  }
  deb(cur);
  int low = 1e9;
  for (int i = 0; i < n; i++) {
    if (!open[i]) {
      continue;
    }
    open[i] = false;
    low = min(low, recurse(cur + 1, open) + abs(people[cur] - i));
    open[i] = true;
  }
  deb(cur, open, low);
  dp[cur][open.to_string()] = low;
  return low;
}
void solve() {
  read(n);
  used.reserve(n);
  read(used, n);
  for (int i = 0; i < n; i++) {
    if (used[i]) {
      people.push_back(i);
    }
  }
  deb(people);
  state open;
  // open.reserve(n);
  for (int i = 0; i < n; i++) {
    open[i] = !used[i];
  }
  deb(n, used);
  int ans = recurse(0, open);
  println(ans);
}
