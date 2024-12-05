/*
 * @lc app=leetcode.cn id=1658 lang=cpp
 *
 * [1658] 将 x 减到 0 的最小操作数
 */

// @lc code=start
// 等效：也就是让窗口内所有数之和等于 s-x ，其中 s 是原数组所有数之和。
// 注意：题意有简化的意图，因为所有数都是正整数。
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size(), len = -1, sum = 0;
        int target = reduce(nums.begin(), nums.end()) - x;
        for (int l = 0, r = 0; l < n && r < n; ++r) {
            sum += nums[r];
            while (l <= r && sum > target)
                sum -= nums[l++];
            if (sum == target)
                len = max(len, r - l + 1);  // l 可能大于 r，此时 len 等于 0
        }
        return len >= 0 ? n - len : -1;
    }
};
// @lc code=end
