/*
 * @lc app=leetcode.cn id=1014 lang=cpp
 *
 * [1014] 最佳观光组合
 */

// @lc code=start
// 这类题目一般要移项，否则很难发现规律
// values[i] + values[j] + i - j
// 改成 (values[i] + i) + (values[j] - j)
// 对每个 j 来说，values[j] - j 是固定的，只要找到最大的 values[i] + i ，就能得到最大的得分。
// 而 values[i] + i 可以在之前的遍历中保存下来。
class Solution {
   public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int n = values.size();
        int maxi = values[0] + 0, ans = INT_MIN;
        for (int j = 1; j < n; ++j) {
            ans = max(ans, maxi + values[j] - j);
            maxi = max(maxi, values[j] + j);
        }
        return ans;
    }
};
// @lc code=end

