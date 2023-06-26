#include "template.cpp"
vi primes = sieve(12);
vi factors(long long n, bool print = false) {
  mii factorization;
  for (int d: primes) {
    if (d * d > n) {
      break;
    }
    while (n % d == 0) {
      factorization[d]++;
      n /= d;
    }
  }
  if (n > 1) {
    factorization[n]++;
  }
  if (print) {
    deb(factorization);
  }
  vi nums;
  for (auto [x, c]: factorization) {
    nums.pb(x);
    nums.pb(c);
  }
  sort(nums);
  return nums;
}
void solve() {
  int n;
  read(n);
  n *= 2;
  vi arr;
  read(arr, n);
  // mii cur;
  // for (int x: arr) {
  //   cur[x]++;
  // }
  // deb(cur);
  // vi ans;
  // for (auto [x, c]: cur) {
  //   ans.pb(x);
  //   ans.pb(c);
  // }
  sort(arr);
  int count = 0;
  deb(factors(210), arr);
  deb(factors(6006129981862500) == arr);
  for (ll i = 2; i <= 7000000000000000000; i++) {
    if (factors(i) == arr) {
      deb(i, factors(i, true));
      count++;
    }
  }
  println(count);
}
