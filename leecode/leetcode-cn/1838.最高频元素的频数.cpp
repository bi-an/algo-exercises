/*
 * @lc app=leetcode.cn id=1838 lang=cpp
 *
 * [1838] 最高频元素的频数
 */

// @lc code=start
// 滑动窗口
// 注意：可以对同一个数多次操作
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size(), ans = 1;
        // op 是窗口内需要操作的次数；
        // op 可能远远大于 k ，所以需要 long long 来表示
        long long op = 0;

        // 排序不影响结果，先排序
        sort(nums.begin(), nums.end());
        // 每个数都需要变成窗口最右端的数
        for (int l = 0, r = 1; r < n; ++r) {
            // 之前窗口内的每个数现在都要变成 nums[r] ，需要统一增加操作次数
            op += (long long)(r - l) * (nums[r] - nums[r - 1]);
            while (op > k)
                op -= nums[r] - nums[l++];
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
// @lc code=end
