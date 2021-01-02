// https://www.nowcoder.com/question/next?pid=16516564&qid=362290&tid=37005972

// 提示：用两个map存储本次和上次的帧

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  pair<int, int> xy;

  int maxCnt = 0;

  while (n--)
  {
    int m;
    cin >> m;

    map<pair<int, int>, int> feaTimes, preFeaTimes;

    while (m--)
    {
      int k;
      cin >> k;

      while (k--)
      {
        cin >> xy.first >> xy.second;

        if (preFeaTimes.count(xy) > 0)
          feaTimes[xy] = preFeaTimes[xy] + 1;
        else
          feaTimes[xy] = 1;

        if (maxCnt < feaTimes[xy])
          maxCnt = feaTimes[xy];
      }
      preFeaTimes.clear();
      preFeaTimes.swap(feaTimes);
    }
  }
  cout << maxCnt << endl;

  return 0;
}