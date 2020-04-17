class Solution
{
 public:
  int longestPalindromeSubseq(string s)
  {
    int n = s.size();
    vector<vector<int>> dp(n);
    for (int i = 0; i < n; i++)
      dp[i] = vector<int>(n, 0);
    for (int i = 0; i < n; i++)
      dp[i][i] = 1; // dp[i][i]都要初始化为1，其他的位置应该初始化为0，详见下面分析

    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (s[i] == s[j])
          dp[i][j] = dp[i + 1][j - 1] + 2; // 技巧：这里一下子把字符串长度为奇数或者偶数的情况都考虑到了；
                                           // 但是，有个初始化细节，
                                           // 例如"bb"，i=0,j=1,此时dp[i+1][j-1]=dp[1][0]，所以dp初始化时，dp[i][i]之外都要初始化为0
        else
          dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
      }
    }

    return dp[0][n - 1];
  }
};

/*
解题思路：
    动态规划四要素

    1. 状态
    f[i][j] 表示 s 的第 i 个字符到第 j 个字符组成的子串中，最长的回文序列长度是多少。

    2. 转移方程
    如果 s 的第 i 个字符和第 j 个字符相同的话

    f[i][j] = f[i + 1][j - 1] + 2

    如果 s 的第 i 个字符和第 j 个字符不同的话

    f[i][j] = max(f[i + 1][j], f[i][j - 1])

    然后注意遍历顺序，i 从最后一个字符开始往前遍历，j 从 i + 1 开始往后遍历，这样可以保证每个子问题都已经算好了。

    3. 初始化
    f[i][i] = 1 单个字符的最长回文序列是 1

    4. 结果
    f[0][n - 1]

作者：a380922457
链接：https://leetcode-cn.com/problems/longest-palindromic-subsequence/solution/dong-tai-gui-hua-si-yao-su-by-a380922457-3/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/