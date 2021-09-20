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

// https://leetcode-cn.com/problems/2-keys-keyboard/solution/zhi-you-liang-ge-jian-de-jian-pan-by-lee-ussa/
// 分解质因子
class Solution {
public:
    int minSteps(int n) {
        int ans = 0;
        for(int i = 2; i * i <= n; i++) { // n最多有一个大于sqrt(n)的质因子，因为如果有2个的话，它们的乘积必然大于n
            while(n % i == 0) {
                n /= i;
                ans += i;
            }
        }
        if(n > 1) // 有一个大于sqrt(n)的质因子，比如 26 = 2*13
            ans += n;
        return ans;
    }
};