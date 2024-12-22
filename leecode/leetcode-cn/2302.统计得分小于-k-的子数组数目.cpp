/*
 * @lc app=leetcode.cn id=2302 lang=cpp
 *
 * [2302] 统计得分小于 K 的子数组数目
 */

// @lc code=start
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long ans = 0, sum = 0;
        int n = nums.size();
        for (int l = 0, r = 0; r < n; ++r) {
            sum += nums[r];
            // 最大合法区间
            while (sum * (r - l + 1) >= k)
                sum -= nums[l++];
            // 最大区间的每个子区间均合法
            // 为了避免重复计入，要求每个子区间必须包含 nums[right]
            ans += r - l + 1;
        }
        return ans;
    }
};
// @lc code=end
