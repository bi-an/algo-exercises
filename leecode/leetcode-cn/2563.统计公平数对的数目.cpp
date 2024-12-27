/*
 * @lc app=leetcode.cn id=2563 lang=cpp
 *
 * [2563] 统计公平数对的数目
 */

// @lc code=start
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        long long ans = 0;
        int n = nums.size();

        ranges::sort(nums);

        for (auto it = nums.begin(); it != nums.end(); ++it) {
            // lower - nums[i] ≤ nums[j] ≤ upper - nums[i]

            // 写法一：往右找
            // lower_bound 是下界，第一个 num ≥ x 的位置（即闭区间），
            // // 如果 num 都小于 x ，则返回 nums.end()
            // auto left = lower_bound(it + 1, nums.end(), lower - *it);
            // // // 第一个 num > lower - nums[i] - 1
            // // auto left = upper_bound(it + 1, nums.end(), lower - *it - 1);
            // // 第一个 num > upper - nums[i]
            // auto right = upper_bound(it + 1, nums.end(), upper - *it);

            // 写法二：向左找
            auto left = lower_bound(nums.begin(), it, lower - *it);
            auto right = upper_bound(nums.begin(), it, upper - *it);

            ans += right - left;
        }
        return ans;
    }
};
// @lc code=end
