#include "template/gen_template.cpp"

void generate() {
  int n = rnd(2, 200);
  cout << n << "\n";
  int m = rnd(1, n / 2);
  vi nums;
  nums.insert(nums.end(), n - m, 0);
  nums.insert(nums.end(), m, 1);
  for (int num: nums) {
    cout << num << " ";
  }
  cout << "\n";
}
