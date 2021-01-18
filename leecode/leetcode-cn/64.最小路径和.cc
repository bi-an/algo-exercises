
// 动态规划
// dp[i][j] 从grid[0][0]到grid[i][j]的最小路径和
lass Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
      if(grid.empty()) return 0;
      int m = grid.size();
      int n = grid[0].size();

      vector<vector<int>> dp(grid);
      
      for(int i=1;i<m;i++)
        dp[i][0] += dp[i-1][0];
      for(int j=1;j<n;j++)
        dp[0][j] += dp[0][j-1];
      
      for(int i=1;i<m;i++) {
        for(int j=1;j<n;j++) {
          dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
      }

      return dp[m-1][n-1];
    }
};