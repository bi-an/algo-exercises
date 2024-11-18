#include <bits/stdc++.h>
using namespace std;

/**
 * @动态规划
 *   dp[i][j] 使用前i种面额硬币恰好凑成总金额为j的总组合数
 *  （1）没有使用第i种面额
 *      dp[i-1][j]
 *  （2）使用了第i种面额
 *      dp[i][j-coins[i]]，当j-coins[i]>=0
 *    说明：由于一定使用了第i种面额的至少一个，那么此时的组合数与减去一个这个面额的组合数是一样的。
 *      如果j<coins[i]，说明不能使用这种面额，直接跳过即可（也就是对应的组合数不能加上去）。
 *      动态规划使用的是递归思想，只要能准确地推出递推式和base case，就一定能算出来，至于这个递推式的形式可以有多种，每一种都是可行的。
 *  由于是求总组合数，所以这两种情况需要相加：
 *      dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]]
 * 
 *  base case:
 *      dp[0][j] = 0
 *      dp[i][0] = 1，使用0个硬币就可以，所以组合数为1。这样初始化是为了，当考虑情况（2）、j==coins[i]时，对应的使用了第i种面额的组合
 *   数应该为1，而不是0。换个角度说，由上面的递推式，如果dp[i][0]和dp[0][j]都初始化为0，那么递推结果一直是0，没有意义，至于为什么初始化
 *   为1而不是其他数字，可以举例，因为初始结果只会影响它紧邻的下一个结果，只要下一个结果正确，其他结果自然正确。例如，1中硬币（1元）、总额
 *   为1，那么dp[1][1]=dp[0][1]+dp[1][1-1]=0+1=1。
 */

class Solution
{
 public:
  int change(int amount, vector<int> &coins)
  {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
    // 递推式dp[i][j-coins[i]]，如果j-coins[i]==0，此时应该恰好有一种方案:即使用coins[i]
    for (int i = 0; i <= n; i++)
      dp[i][0] = 1; // 注意

    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= amount; j++)
      {
        dp[i][j] = dp[i - 1][j];
        int diff = j - coins[i - 1]; // i从1开始，所以coins下标为i-1
        if (diff >= 0)
          dp[i][j] += dp[i][diff]; // 求总组合数，所以为加法
      }
    }

    return dp[n][amount];
  }
};

/**
 *              j-coins[i]          |    j          |      amount
 * --------------------------------------------------------------
 * i-1  |                           |    (i-1,j)    |
 * --------------------------------------------------------------
 * i    |       (i,j-coins[i])      |    (i,j)      |
 * --------------------------------------------------------------
 * 
 * dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]]
 */

class Solution_2
{
 public:
  int change(int amount, vector<int> &coins)
  {
    vector<int> dp(amount + 1);
    dp[0] = 1;

    // 这两个循环不能交换顺序
    // 因为j-coins[i]不是j-1（总额j-1也是一个合理的值），j-coins[i]在数组中对应的值被覆盖了
    for (auto coin : coins)
    {
      for (int i = 1; i <= amount; i++)
      {
        if (i - coin >= 0)
          dp[i] += dp[i - coin];
      }
    }
    return dp[amount];
  }
};

// 与Solution_2是一样的
class Solution_3
{
 public:
  int change(int amount, vector<int> &coins)
  {
    vector<int> dp(amount + 1);
    dp[0] = 1;

    int n = coins.size();

    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= amount; j++)
      {
        if (j - coins[i - 1] >= 0)
        {
          dp[j] = dp[j] + dp[j - coins[i - 1]];
        }
      }
    }

    return dp[amount];
  }
};