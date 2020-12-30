// 不限买卖次数，k=inf，这相当于说，188题的j和j-1属于相同的情况
// dp[i][j] 第i天、是否持有（j=0持有、j=1不持有）股票时，最大的收益
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n==0) return 0;

        vector<vector<int>> dp(n, vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for(int i=1;i<n;i++){
            dp[i][0]=max(dp[i-1][0], dp[i-1][1]+prices[i]);
            if(i>=2)
                dp[i][1]=max(dp[i-1][1], dp[i-2][0]-prices[i]); // 有冷冻期，所以要隔一天才能卖出
            else
                // dp[i][1]=max(dp[i-1][1],dp[i-1][0]-prices[i]); // 也对
                dp[i][1]=max(-prices[0],-prices[1]); // dp[1][1]可能是第0天买入，也可能是第1天买入
        }

        return max(dp[n-1][0],dp[n-1][1]);
    }
};