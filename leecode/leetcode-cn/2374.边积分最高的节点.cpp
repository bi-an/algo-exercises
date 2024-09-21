/*
 * @lc app=leetcode.cn id=2374 lang=cpp
 *
 * [2374] 边积分最高的节点
 */

// @lc code=start
class Solution {
public:
    int edgeScore(vector<int>& edges) {
        int n = edges.size();
        vector<long long> dp(n);  // dp[i] 表示节点 i 当前的积分
        long long maxScore = 0;   // long long防止加法溢出，
                                  // 因为n的范围为10^5，加法可能超过2^31（即2*10^10）
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int j = edges[i];
            dp[j] += i;
            if (maxScore < dp[j]) {
                ans = j;
                maxScore = dp[j];
            } else if (maxScore == dp[j]) {
                ans = min(j, ans);
            }
        }
        return ans;
    }
};
// @lc code=end
