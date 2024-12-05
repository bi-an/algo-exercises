/*
 * @lc app=leetcode.cn id=2958 lang=cpp
 *
 * [2958] 最多 K 个重复元素的最长子数组
 */

// @lc code=start
class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        unordered_map<int, int> cnt;
        for (int l = 0, r = 0; r < n; ++r) {
            ++cnt[nums[r]];
            while (cnt[nums[r]] > k) {
                --cnt[nums[l++]];
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
// @lc code=end
