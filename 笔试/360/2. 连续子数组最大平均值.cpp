// @Athor zzg
// 动态规划，似乎正确，但是时间复杂度O(n^2)，估计会超时

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int main()
{
  int N, M; // 共有N章，至少连续看M章
  cin >> N >> M;
  vector<int> num;
  int *preSum = new int[N + 1]();
  vector<vector<double>> dp(N + 1);
  for (int i = 0; i < N + 1; i++)
  {
    dp[i] = vector<double>(N + 1, 0);
  }

  for (int i = 0; i < N; i++)
  {
    int tmp;
    cin >> tmp;
    num.push_back(tmp);
    preSum[i + 1] = preSum[i] + tmp;
  }

  double maxVal = 0;

  for (int i = 1; i < N + 1; i++)
  {
    for (int j = i; j < N + 1; j++)
    {
      if (j - i >= M - 1)
      {
        //double ava = ((double)(j - i)*dp[i][j - 1] + num[j - 1]) / (j - i + 1);
        double ava = ((double)preSum[j] - preSum[i - 1]) / (j - i + 1);
        maxVal = max(ava, dp[i - 1][j]);
        maxVal = max(maxVal, dp[i][j - 1]);
        dp[i][j] = maxVal;
      }
      //else {
      //	while (j < N + 1) {
      //		dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      //		j++;
      //	}
      //}
    }
  }

  //printf("%.3f", dp[N][N]);
  printf("%.3f", maxVal);

  return 0;
}