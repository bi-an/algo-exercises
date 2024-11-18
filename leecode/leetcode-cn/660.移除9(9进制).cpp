#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int newInteger(int n) {
    --n;  // 让 n 从 0 开始索引

    // 9 进制
    int re = n % 9;
    if (re == 8) ++re;  // 跳过 9
    int tens = n / 9;

    return tens * 10 + re + 1;  // +1 表示从 1 开始
  }
};

Solution sol;

void test(int n) { cout << n << ": " << sol.newInteger(n) << endl; }

int main() {
  for (int i = 1; i < 30; ++i) test(i);
}