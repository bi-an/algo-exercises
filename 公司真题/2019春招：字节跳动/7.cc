// https://www.nowcoder.com/question/next?pid=16516564&qid=362290&tid=37075116

// Tips: 乘法容易溢出，那就改成除法

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> num(n);
  for (int i = 0; i < n; i++)
    cin >> num[i];

  // long long sum = 0;
  // for (int i = 0; i < n; i++)
  // {
  //   sum += pow(2, i) * (double)num[n - 1 - i];
  //   cout << sum << " "; // test
  // }
  // cout << endl; // test

  double sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum += (double)num[i] / pow(2, i + 1);
  }

  cout << ceil(sum) << endl;

  return 0;
}