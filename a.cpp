#include "template.cpp"

auto solve(int) {
  int n;
  read(n);
  int y, r;
  read(y, r);
  return min(n, (y / 2) + r);
}
