/*
 * @lc app=leetcode.cn id=1004 lang=cpp
 *
 * [1004] 最大连续1的个数 III
 */

// @lc code=start
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0, cnt = 0;  // cnt 统计 0 的个数
        for (int l = 0, r = 0; r < n; ++r) {
            cnt += nums[r] == 0;
            while (cnt > k)
                cnt -= nums[l++] == 0;
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
// @lc code=end
