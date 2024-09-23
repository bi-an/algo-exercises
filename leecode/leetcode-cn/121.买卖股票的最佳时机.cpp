/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start

// （1）尽可能以最低价格买入；
// （2）以最高价格卖出；
// （3）卖出时间一定要在买入之后。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty())
            return 0;
        int min_price_pos = 0, max_profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            int profit = prices[i] - prices[min_price_pos];
            if (profit > max_profit)
                max_profit = profit;
            else if (profit < 0)
                min_price_pos = i;  // 说明min_price_pos处不是最低的买入价格, i处的买入价格更低
        }
        return max_profit;
    }
};

namespace solution_2 {
// @Athor zzg
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        int res = 0;
        int min_val = prices[0];
        for (int i = 1; i < n; i++) {
            if (prices[i] - min_val > res)
                res = prices[i] - min_val;
            if (prices[i] < min_val)
                min_val = prices[i];
        }

        return res;
    }
};
}  // namespace solution_2

namespace solution_3 {
// 根据题“188.买卖股票的最佳时机IV”的框架
// 点评：时空复杂度都偏高
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(2));

        dp[0][0] = 0, dp[0][1] = -prices[0];

        // // 状态转移方程
        // for (int i = 1; i <= n; i++) {
        //   for (int j = 1; j <= k; j++) {
        //     dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
        //     dp[i][j][1] = max(dp[i - 1][j][1],
        //                       dp[i - 1][j - 1][0] - prices[i - 1]); // buy，所以j-1（在sell时标记成j-1是一样的）
        //   }
        // }

        // 直接令188题中的k=1即可，但是我们可以适度优化。
        // k=1, 那么j=0或1
        // 根据上面的状态转移方程，只有dp[i - 1][j - 1][0]涉及j==0时，我们把它提前计算出来就可以了
        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], -prices[i]);  // dp[i - 1][j - 1][0] = 0
        }

        return dp[n - 1][0];
    }
};
}  // namespace solution_3

// @lc code=end
