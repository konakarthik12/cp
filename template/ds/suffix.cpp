#pragma once
#include "../base.cpp"
#include "../deb.cpp"
#include "../views.cpp"
#include "../container.cpp"

template <typename func>
auto build_cls(vi& order, func hash) {
  int n = order.sz();
  vi cls_next(n);

  for (auto [p, c]: order | pairwise) {
    cls_next[c] = cls_next[p];
    if (hash(p) != hash(c)) cls_next[c]++;
  }
  return cls_next;
}

auto suffix_arr(str s) {
  int n;
  s += '$';
  n = sz(s);
  vi order;
  auto raw_hash = [&](int x) { return s[x]; };
  order.iota(n);

  order.sort(raw_hash);

  vi cls = build_cls(order, raw_hash);

  for (int t = 0; t < blen(n); t++) {
    int k = 1 << t;
    auto hash_l = [&](int x) { return cls[x]; };
    auto hash_r = [&](int x) { return cls[(x + k) % n]; };
    auto hash = [&](int x) { return pii(hash_l(x), hash_r(x)); };

    for (int& x: order) {
      x -= k;
      if (x < 0) x += n;
    }
    vi order_new(n);
    vi sort_cnt(n);
    for (int i = 0; i < n; i++) sort_cnt[hash_l(i)]++;
    vll cnt = pref_arr(sort_cnt);
    for (int x: order | rview) order_new[--cnt[hash_l(x)]] = x;

    order = order_new;
    cls = build_cls(order, hash);
  }

  return order;

  // // i'th suffix in the suffix array
  // auto suf_view = [&](int i) { return sview{s.begin() + suf[i], s.end()}; };
  // auto suf_view = [&](int i) { return sview{s.begin() + suf[i], s.end()}; };
  // vi rev = invperm(suf);

  // int k = 0;
  // wi lcp(n);
  // for (int x: rev) {
  //   if (x == 0) continue;
  //   sview cur = suf_view(x);
  //   sview prv = suf_view(x - 1);
  //   int mx = max(sz(cur), sz(prv));
  //   while (k < mx && cur[k] == prv[k]) k++;
  //   lcp[x] = k;
  //   if (k > 0) k--;
  // }

  // using sview = std::string_view;
  // // true if a <= b
  // auto lower = [&](sview a, sview b) {
  //   deb(a, b);
  //   for (int i = 0; i <= min(sz(a), sz(b)); i++) {
  //     if (a[i] == b[i]) continue;
  //     if (a[i] < b[i]) return true;
  //     if (a[i] > b[i]) return false;
  //   }

  //   return sz(a) < sz(b);
  // };
  // // true if a and b match starting
  // auto lower2 = [&](sview a, sview b) {
  //   deb("lower2", a, b);
  //   for (int i = 0; i < min(sz(a), sz(b)); i++) {
  //     deb(i, a[i], b[i]);
  //     if (a[i] == b[i]) continue;
  //     if (a[i] < b[i]) return true;
  //     if (a[i] > b[i]) return false;
  //   }
  //   return true;
  //   // return sz(a) <= sz(b);
  // };
  // int q;
  // read(q);
  // for (int qr = 0; qr < q; qr++) {
  //   deb(qr);
  //   str t;
  //   read(t);
  //   deb(t);
  //   auto check = [&](int x) { return lower(suf_view(x), sview{all(t)}); };
  //   auto check2 = [&](int x) { return lower2(suf_view(x), sview{all(t)}); };

  //   for (int i = 0; i <= n; i++) {
  //     deb(i, suf_view(i), t, check(i), check2(i));
  //   }
  //   int low = min_false(0, n, check);
  //   int high = max_true(0, n, check2);
  //   deb(low, high);
  //   int ans = high - low + 1;

  //   println(ans);
  //   deb();
  // }
}
