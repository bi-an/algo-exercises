/*
 * @lc app=leetcode.cn id=2207 lang=cpp
 *
 * [2207] 字符串中最多数目的子序列
 */

// @lc code=start
class Solution {
   public:
    long long maximumSubsequenceCount(string text, string pattern) {
        int n = text.size();
        long long ans = 0;

        // dp[i] 保存遇到的 pattern[i] 的次数
        vector<int> dp(2);
        // 先算字符串 text 本身含有的等于 pattern 子序列个数
        for (char c : text) {
            if (c == pattern[1]) {
                ans += dp[0]; // 每当遇到 pattern[1] ，之前 text 中含有的 pattern[0] 可以与之组成一个 pattern
                ++dp[1];
            }
            // 注意 pattern 中两个字母可能相同
            if (c == pattern[0]) {
                ++dp[0];
            }
        }
        // 如果添加 pattern[0] ，最优解是添加到开头，此时 text 中所有的 pattern[1] 可与之组成一个 pattern
        // 如果添加 pattern[1] ，最优解是添加到末尾，同理
        ans += max(dp[0], dp[1]);
        return ans;
    }
};
// @lc code=end

