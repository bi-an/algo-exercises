/*
 * @lc app=leetcode.cn id=1695 lang=cpp
 *
 * [1695] 删除子数组的最大得分
 */

// @lc code=start
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size(), ans = 0, sum = 0;
        unordered_map<int, int> cnt;
        for (int l = 0, r = 0; r < n; ++r) {
            ++cnt[nums[r]];
            sum += nums[r];
            while (cnt[nums[r]] > 1) {
                --cnt[nums[l]];
                sum -= nums[l++];
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
// @lc code=end
