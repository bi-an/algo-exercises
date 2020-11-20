/**
 * @动态规划
 *   dp[i][j] 使用前i种面额硬币恰好凑成总金额为j的总组合数
 *  （1）不使用第i种面额
 *      dp[i-1][j]
 *  （2）使用第i种面额
 *      dp[i][j-coins[i]]，当j-coin>=0
 *    说明：使用了第i种面额凑成总额j的组合数，与使用了第i种面额凑成总额j-coins[i]是相同的，TOOD
 *  由于是求总组合数，所以这两种情况需要相加：
 *      dp[i][j] = dp[i-1][j] + dp[i][j-coin]
 * 
 */

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));
		// 递推式dp[i][j-coins[i]]，如果j-coins[i]==0，此时应该恰好有一种方案
        for(int i=0;i<=n;i++)
            dp[i][0] = 1; // 注意

        for(int i=1;i<=n;i++){
            for(int j=1;j<=amount;j++){
                dp[i][j] = dp[i-1][j];
                int diff = j-coins[i-1]; // i从1开始，所以coins下标为i-1
                if(diff >= 0)
                    dp[i][j]+=dp[i][diff]; // 求总组合数，所以为加法
            }
        }

        return dp[n][amount];
    }
};