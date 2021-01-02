// https://www.nowcoder.com/question/next?pid=16516564&qid=362290&tid=36719992

#include <bits/stdc++.h>
using namespace std;

#define M 99997867

// long long 类型可以防止溢出

long long C(long long n) { return n * (n - 1) / 2; }

int main() {
  int N, D;
  long long res = 0;
  cin >> N >> D;
  vector<int> pos(N);

  for (int i = 0; i < N; i++)
    cin >> pos[i];

  // 可变长滑窗
  for (int start = 0, end = 0; end < N; end++) {
    while (end >= 2 && pos[end] - pos[start] > D) {
      start++;
    }
    res += C(end - start);
  }

  cout << res % M << endl;

  return 0;
}
