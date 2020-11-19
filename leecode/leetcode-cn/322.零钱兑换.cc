#include <bits/stdc++.h>
using namespace std;

// 递归+备忘录
// TODO 时间复杂度慢了将近10倍
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // if(coins.empty() || amount < 0) return -1;

        unordered_map<int,int> memo(amount+1); // amount -> ans
        return dp(coins, memo, amount);
    }

    int dp(vector<int>& coins, unordered_map<int, int>& memo, int amount){
        if(amount == 0) return 0;
        if(amount < 0) return -1;

        if(memo.find(amount)!=memo.end())
            return memo[amount];
        
        int res = INT_MAX;
        for(auto coin : coins){
            int cur = dp(coins, memo, amount - coin);
            if(cur == -1)
                continue;
            res = min(res, cur + 1);
        }
        res = res==INT_MAX?-1:res; // 有可能for循环中cur全部为-1
        memo[amount] = res;
        return res;
    }
};

// 动态规划
class Solution_2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, amount + 1); // 因为最大硬币数不会超过amount（全是1元硬币），所以amount+1相当于INT_MAX
        dp[0] = 0;
        for(int i=1;i<amount+1;i++){
            for(auto coin : coins){
                if(i - coin < 0)
                    continue;
                dp[i] = min(dp[i-coin] + 1, dp[i]);
            }
        }
        return dp[amount]==amount+1?-1:dp[amount];
    }
};