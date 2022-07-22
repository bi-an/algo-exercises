// 方法一：动态规划
// 时间复杂度:O(n^3)
// 空间复杂度：O(n^2)
class Solution
{
 public:
  int numTrees(int n)
  {
    // dp[i][j] 表示 [i,j] 区间的数构成的二叉搜索树的个数
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = n - 1; i >= 0; --i)
    {
      for (int j = i; j < n; ++j)
      {
        // dp[i][j] = sum { dp[i][k - 1] * dp[k + 1][j], k ∈ [i, j]}
        for (int k = i; k <= j; ++k)
        {
          int left = (k == i) ? 1 : dp[i][k - 1];
          int right = (k == j) ? 1 : dp[k + 1][j];
          dp[i][j] += left * right;
        }
      }
    }
    return dp[0][n - 1];
  }
};


// 方法二：动态规划
// 时间复杂度:O(n^2)
// 空间复杂度：O(n)
// 
// 方法一的递推式可以进一步推导为一维，详见官方题解一
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};


// 方法三：卡塔兰数
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 上面推导出的 G(n) 函数值在数学上称为“卡塔兰数”。