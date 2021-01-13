class Solution {
public:
  int calculateMinimumHP(vector<vector<int>> &dungeon) {
    if (dungeon.empty() || dungeon[0].empty())
      return 0;
    int m = dungeon.size();
    int n = dungeon[0].size();

    // dp[i][j]表示从初始位置(i,j)到达右下角，初始位置处最少需要的健康点数
    vector<vector<int>> dp(m, vector<int>(n));
    dp[m - 1][n - 1] =
        dungeon[m - 1][n - 1] > 0 ? 1 : -dungeon[m - 1][n - 1] + 1;

    for (int i = m - 1; i >= 0; i--) {
      for (int j = n - 1; j >= 0; j--) {
        if (i == m - 1 && j == n - 1)
          dp[i][j] = dungeon[i][j] > 0 ? 1 : -dungeon[i][j] + 1;
        else if (i == m - 1)
          dp[i][j] = dp[i][j + 1] - dungeon[i][j];
        else if (j == n - 1)
          dp[i][j] = dp[i + 1][j] - dungeon[i][j];
        else
          dp[i][j] = min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j];
        if (dp[i][j] <= 0)
          dp[i][j] = 1;
      }
    }

    return dp[0][0];
  }
};