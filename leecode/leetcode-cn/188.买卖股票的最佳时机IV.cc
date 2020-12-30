// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/

// @ref labuladong
// 状态机、动态规划
// 所谓状态机：就是穷举所有状态
// dp[i][j][s] 当前第i天、已经交易了j次（也就是buy了j次，或者说sell了j次）、当前是否持有股票（s=0不持有、s=1持有）时，获得的最大收益
class Solution {
public:
  int maxProfit(int k, vector<int> &prices) {
    if (prices.empty())
      return 0;
    int n = prices.size();
    vector<vector<vector<int>>> dp(n + 1,
                                   vector<vector<int>>(k + 1, vector<int>(2)));

    // base case
    for (int j = 0; j <= k; j++) {
      dp[0][j][0] = 0; // 第0天、不持有股票，也就是没有买，那么收益为0
      dp[0][j][1] = -prices[0]; // 第0天、持有股票，也就是买了股票，那么收益为-prices[0]
    }

    // 状态转移方程
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= k; j++) {
        dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
        dp[i][j][1] = max(dp[i - 1][j][1],
                          dp[i - 1][j - 1][0] - prices[i - 1]); // buy，所以j-1（在sell时标记成j-1是一样的）
      }
    }

    return dp[n][k][0];
  }
};