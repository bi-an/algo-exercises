/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */

// @lc code=start
// 动态规划，一维表格
// f(i)表示一直抢到第i个房子所能获得最大累计价值，i的范围为0~n
// f(i)=max{ f(i-1), f(i-2)+cost[i]};
// f(0)=0, f(1)=1.
// 解释: 抢第i个房子所能获得最大累计价值=max(第i-2个房子所获累计价值+本房子价值, 第i-1个房子的累计价值)
class Solution {
public:
    int rob(vector<int> &nums) {
        if (nums.empty())
            return 0;
        vector<int> c(nums.size() + 1);
        c[0] = 0, c[1] = nums[0];
        for (int i = 2; i < c.size(); i++) {
            c[i] = std::max(c[i - 2] + nums[i - 1], c[i - 1]);
        }
        return c[nums.size()];
    }
};
// @lc code=end
