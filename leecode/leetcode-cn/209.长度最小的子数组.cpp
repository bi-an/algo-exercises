/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), ans = n + 1;
        long long sum = 0;
        for (int l = 0, r = 0; l < n; ++l) {
            while (r < n && sum < target)
                sum += nums[r++];
            // 有可能 sum 一直小于 target
            if (sum >= target)
                ans = min(ans, r - l);
            sum -= nums[l];
        }
        return ans <= n ? ans : 0;
    }
};
// @lc code=end
