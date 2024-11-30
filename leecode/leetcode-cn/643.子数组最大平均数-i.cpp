/*
 * @lc app=leetcode.cn id=643 lang=cpp
 *
 * [643] 子数组最大平均数 I
 */

// @lc code=start
// 定长滑动窗口
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        long long sum = 0, max_sum = LLONG_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            // 窗口长度不足 k
            if (i < k - 1)
                continue;
            // 更新答案
            max_sum = max(max_sum, sum);
            // 离开窗口，删除本窗口头部，为下一次作准备
            sum -= nums[i - k + 1];
        }
        return (double)max_sum / k;
    }
};
// @lc code=end
