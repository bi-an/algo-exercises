/*
 * @lc app=leetcode.cn id=2529 lang=cpp
 *
 * [2529] 正整数和负整数的最大计数
 */

// @lc code=start
class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int negative = ranges::lower_bound(nums, 0) - nums.begin();                  // 负数个数
        int positive = nums.size() - (ranges::upper_bound(nums, 0) - nums.begin());  // 正数个数
        return max(negative, positive);
    }
};
// @lc code=end
