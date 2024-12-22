/*
 * @lc app=leetcode.cn id=713 lang=cpp
 *
 * [713] 乘积小于 K 的子数组
 */

// @lc code=start
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        long long prod = 1;
        int ans = 0, n = nums.size();
        for (int l = 0, r = 0; r < n; ++r) {
            prod *= nums[r];
            // 先找最大区间
            // 有可能所有数都 ≥ k ，且 prod 最小值 1 可能也 ≥ k ，所以需要防止访问越界
            while (l <= r && prod >= k)
                prod /= nums[l++];
            ans += r - l + 1;  // 最大区间的任意子区间都合法
                               // 但为了防止重复计入，我们要求所有子区间都包含 nums[r]
        }
        return ans;
    }
};
// @lc code=end
