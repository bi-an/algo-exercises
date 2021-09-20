// 法一：动态规划
// 时间复杂度O(n)
class Solution {
public:
    int minSteps(int n) {
        // dp[i]表示打印出i个A，需要的最少操作次数
        // 要想打印出dp[i]，必须已有dp[j]，然后经过1次复制、若干次粘贴（即i/j次操作）得到
        // dp[i] = min {dp[i], dp[j] + i/j}，当且仅当i能整除j时
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 0;

        for(int i = 2; i < n + 1; i++) {
            for(int j = 1; j <= i / 2; j++) { // 这里可以优化
                if(i % j == 0)
                    dp[i] = min(dp[i], dp[j] + i / j);
            }
        }

        return dp[n];
    }
};

// 法一优化，减少遍历次数
// 时间复杂度O(sqrt(n))
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 0;

        for(int i = 2; i < n + 1; i++) {
            for(int j = 1; j * j <= i; j++) { // i一定可以同时整除i和i/j
                if(i % j == 0) {
                    dp[i] = min(dp[i], dp[j] + i / j);
                    dp[i] = min(dp[i], dp[i / j] + j);
                }
            }
        }

        return dp[n];
    }
};