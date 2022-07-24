// 动态规划
class Solution
{
 public:
  int maxProfit(vector<int> &prices)
  {
    if (prices.empty())
      return 0;
    int n = prices.size();
    // dp[i][j] 表示第 i 天交易结束后，持有 j 支股票。
    // 由于每天最多持有一支股票，所以 j = 0, 1 只有两个取值。 
    vector<vector<int>> dp(n, vector<int>(2));

    dp[0][0] = 0, dp[0][1] = -prices[0];
    for (int i = 1; i < n; i++)
    {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }

    return dp[n - 1][0];
  }
};

// 贪心算法
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution
{
 public:
  int maxProfit(vector<int> &prices)
  {
    int ans = 0;
    int min_price = INT_MAX;
    for (int price : prices)
    {
      if (price < min_price)
        min_price = price;
      // 只要当前价格高于之前的最低价格，就可以获利。
      if (price > min_price)
      {
        ans += price - min_price;
        // 更新最低股票价格，因为之前的最低价格已经卖出了，但此时可以重新买进。
        // 很显然，如果当前卖出又买进，这是无意义的操作，但是不会影响最终结果。
        // 这说明贪心算法的迭代过程不是实际操作过程，但是不会影响最终结果。
        min_price = price;
      }
    }
    return ans;
  }
};

// 贪心算法二
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 只要当前的价格高于昨天的价格，就可以获利。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1]) {
                ans += prices[i] - prices[i - 1];
            }
        }
        return ans;
    }
};