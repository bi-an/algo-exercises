/*
 * @lc app=leetcode.cn id=2414 lang=cpp
 *
 * [2414] 最长的字母序连续子字符串的长度
 */

// @lc code=start
class Solution {
   public:
    int longestContinuousSubstring(string s) {
        int n = s.length();
        if (n == 0)
            return 0;

        int ans = 1;
        // vector<int> dp(n, 1);
        int cur = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i - 1] + 1) {
                // dp[i] = dp[i - 1] + 1;
                cur++;
            } else {
                cur = 1;
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};
// @lc code=end

