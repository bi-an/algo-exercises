#include <bits/stdc++.h>
using namespace std;

/**
 * @ref labuladong
 * 
 * @动态规划
 * 
 * 回文串问题，从中间向两边
 * 
 * 1. 当s[i]==s[j]，
 *      dp[i][j]=dp[i+1][j-1]
 * 2. 当s[i]!=s[j]
 *      2.1 当s[i+1]==s[j]，
 *          dp[i][j]=dp[i+1][j]+1
 *        例如：
 *              c   a   a   a
 *              i           j
 *      2.2 当s[i]==s[j-1]，
 *          dp[i][j]=dp[i][j-1]+1
 *      2.3 否则
 *          dp[i][j]=dp[i+1][j-1]+2，实际上，这种情况已经被2.1和2.2包括了。 
 * 3. base case:
 *      dp[i][i]=0，即对角线上为0，因为此时只有一个字符，本身是回文串
 *      dp[i][j]=0（当i-j=-1）， 即次下对角线上为0，因为我们填次上对角线时，对照递推公式，此时有两个字符，
 *  当s[i]!=s[j]时，需要插入一个字符变成回文串；否则不需要插入。
 */
class Solution
{
 public:
  int minInsertions(string s)
  {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n));

    for (int i = n - 2; i >= 0; i--)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (s[i] == s[j])
          dp[i][j] = dp[i + 1][j - 1];
        else
          dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
      }
    }

    return dp[0][n - 1];
  }
};

/**
 * @brief 状态压缩 
 */
class Solution_2
{
 public:
  int minInsertions(string s)
  {
    int n = s.size();
    vector<int> dp(n);
    for (int i = n - 2; i >= 0; i--)
    {
      int res = 0; // 因为dp[i+1][j-1]会被本次运算结果dp[i][j]所覆盖，所以提前暂存下来
      for (int j = i + 1; j < n; j++)
      {
        int tmp = dp[j];
        if (s[i] == s[j])
          dp[j] = res;
        else
          // 等号右边的dp[j]就是dp[i+1][j]，dp[j-1]就是dp[i][j-1]
          dp[j] = min(dp[j], dp[j - 1]) + 1;
        res = tmp;
      }
    }
    return dp[n - 1];
  }
};