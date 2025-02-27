/*
On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].

Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].
*/

// 方法一：从前往后迭代
// 本质是斐波那契数列
// f(i)表示总共有i阶的最小cost和
// 初始值：f(0)=max_int; --> 这个其实不重要
// f(1)=cost[0]
// f(2)=min(cost[0], cost[1])
// f(i)=cost[i]+min(f(i-1),f(i-2))
class Solution
{
 public:
  int minCostClimbingStairs(vector<int> &cost)
  {
    if (cost.empty())
      return std::numeric_limits<int>::max();
    if (cost.size() == 1)
      return cost[0]; // 实际上，即使没有这两个判断，也可以通过测试
    int f1 = cost[0], f2 = cost[1];
    for (int i = 2; i < cost.size(); i++)
    {
      int f3 = cost[i] + std::min(f1, f2);
      f1 = f2;
      f2 = f3;
    }
    return std::min(f1, f2);
  }
};

// 方法二：从后往前迭代
// f(i)表示从第i阶开始到最后一阶的cost和
// f(i)=cost[i]+min(f(i+1),f(i+2))
// 初始条件：f1=0, f2=0
// 可以解释为:如果只有最后一阶，那么f3=cost[last].
class Solution
{
 public:
  int minCostClimbingStairs(vector<int> &cost)
  {
    if (cost.empty())
      return std::numeric_limits<int>::max();
    if (cost.size() == 1)
      return cost[0]; // 实际上，即使没有这两个判断，也可以通过测试
    int f1 = 0, f2 = 0;
    for (int i = cost.size() - 1; i >= 0; i--)
    {
      int f3 = cost[i] + std::min(f1, f2);
      f1 = f2;
      f2 = f3;
    }
    return std::min(f1, f2);
  }
};