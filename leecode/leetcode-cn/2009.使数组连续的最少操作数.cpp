/*
 * @lc app=leetcode.cn id=2009 lang=cpp
 *
 * [2009] 使数组连续的最少操作数
 */

// @lc code=start
// 考虑不变因素比考虑可变因素容易
// 反向思考：最多可以让多少个数保持不变
// 题解：https://leetcode.cn/problems/minimum-number-of-operations-to-make-array-continuous/solutions/1005398/on-zuo-fa-by-endlesscheng-l7yi/
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        // 排序
        ranges::sort(nums);
        // 原地去重
        int m = unique(nums.begin(), nums.end()) - nums.begin();
        for (int l = 0, r = 0; r < m; ++r) {
            while (nums[l] + n - 1 < nums[r])
                ++l;
            ans = max(ans, r - l + 1);
        }
        return n - ans;
    }
};
// @lc code=end
