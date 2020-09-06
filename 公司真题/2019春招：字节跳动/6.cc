// https://www.nowcoder.com/question/next?pid=16516564&qid=362290&tid=37072880

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int num[4];
  memset(num, 0, sizeof(num));

  int total, coins = 0;
  cin >> total;
  total = 1024 - total;

  if (total >= 64)
  {
    coins += total / 64;
    total -= total / 64 * 64;
  }
  if (total >= 16)
  {
    coins += total / 16;
    total -= total / 16 * 16;
  }
  if (total >= 4)
  {
    coins += total / 4;
    total -= total / 4 * 4;
  }
  if (total >= 1)
  {
    coins += total;
  }

  cout << coins << endl;

  return 0;
}