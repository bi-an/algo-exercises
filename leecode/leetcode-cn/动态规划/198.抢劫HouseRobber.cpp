/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:
Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
*/

// 动态规划，一维表格
// f(i)表示一直抢到第i个房子所能获得最大累计价值，i的范围为0~n
// f(i)=max{ f(i-1), f(i-2)+cost[i]};
// f(0)=0, f(1)=1.
// 解释: 抢第i个房子所能获得最大累计价值=max(第i-2个房子所获累计价值+本房子价值, 第i-1个房子的累计价值)
class Solution
{
 public:
  int rob(vector<int> &nums)
  {
    if (nums.empty())
      return 0;
    vector<int> c(nums.size() + 1);
    c[0] = 0, c[1] = nums[0];
    for (int i = 2; i < c.size(); i++)
    {
      c[i] = std::max(c[i - 2] + nums[i - 1], c[i - 1]);
    }
    return c[nums.size()];
  }
};