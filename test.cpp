#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// ordered_set supports:
// - find_by_order(k): iterator to kth smallest element, 0-indexed
// - order_of_key(x): number of elements strictly less than x
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  ordered_set<int> s;

  s.insert(10);
  s.insert(20);
  s.insert(30);
  s.insert(40);

  cout << "Elements: ";
  for (int x: s) {
    cout << x << ' ';
  }
  cout << '\n';

  cout << "0th smallest: " << *s.find_by_order(0) << '\n';  // 10
  cout << "2nd smallest: " << *s.find_by_order(2) << '\n';  // 30

  cout << "Count < 25: " << s.order_of_key(25) << '\n';  // 2
  cout << "Count < 30: " << s.order_of_key(30) << '\n';  // 2
  cout << "Count < 50: " << s.order_of_key(50) << '\n';  // 4

  s.erase(20);

  cout << "After erase 20, count < 30: " << s.order_of_key(30) << '\n';  // 1

  return 0;
}
