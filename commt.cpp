#include "template.cpp"

void first(int) {
}

void second(int) {

}
void solve() {
  str s;
  read(s);
  int t;
  read(t);
  if (s == "first") {
    for (int i = 1; i <= t; i++) first(t);
  } else if (s == "second") {
    for (int i = 1; i <= t; i++) second(t);
  }
}
