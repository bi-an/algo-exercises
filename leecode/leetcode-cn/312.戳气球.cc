#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> points(n + 2);
        for (int i = 0; i < n; i++)
            points[i + 1] = nums[i];
        points[0] = 1, points[n + 1] = 1;

        // dp[i][j]：将开区间(i,j)内的所有气球都戳破能得到的最多硬币数
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int i = n + 1; i >= 0; i--) {
            for (int j = i + 2; j <= n + 1; j++) {
                // 最后戳破的气球是第k个
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + points[i] * points[k] * points[j]);
                }
            }
        }

        return dp[0][n + 1];
    }
};