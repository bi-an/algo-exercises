/*
Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

Note:
0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].
*/

// 注意：这题仅仅删除字符，不能改变字符，它不是最小编辑距离，
// 所有不同的字符都应该删除，对于相同的字符，删除哪个位置上的都是一样的。
// s1和s2从最后一个字符开始比较，
// dp[i][j]表示s1[end]到s1[i]为止、s2[end]到s2[j]为止，删去的字符ascii和。
// s1:      i
//	   ---------------------------
//	   | | | | | | | | | | | | | |
//     ---------------------------
// s2:				j
//     ---------------------------
//     | | | | | | | | | | | | | |
//     ---------------------------
// 如图：dp二维表格，填dp[i][j]时，若s1[i]==s2[j]，则应该直接跳过这两个字符，即dp[i][j]=dp[i+1][j+1];
// 若s1[i]!=s2[j]，则应该选择删除s1[i]还是删除s2[j]，若删除s1[i]则表示留下的是s1[i+1]和s2[j]，即dp[i][j]=dp[i+1][j]；若删除s2[j]类似。
// 初始化：dp[m][n]表示s1和s2都为空，所以初始化为0；
// dp[i][n]表示留下的s2含有0个字符，所以应该把s1部分全部删掉，所以dp[i][n]是所有s1的acsii加起来；dp[m][j]类似。

// 时间复杂度: O(m*n)
// 空间复杂度: O(m*n)
class Solution
{
 public:
  int minimumDeleteSum(string s1, string s2)
  {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    dp[m][n] = 0; // s1与s2都为空
    for (int i = m - 1; i >= 0; i--)
      dp[i][n] = dp[i + 1][n] + s1[i]; // s2为空
    for (int j = n - 1; j >= 0; j--)
      dp[m][j] = dp[m][j + 1] + s2[j]; // s1为空

    for (int i = m - 1; i >= 0; i--)
      for (int j = n - 1; j >= 0; j--)
      {
        if (s1[i] != s2[j])
          dp[i][j] = std::min(dp[i + 1][j] + s1[i], dp[i][j + 1] + s2[j]); // 删除s1[i]，则dp[i][j]=dp[i+1][j]+s1[i];
                                                                           // 删除s2[j]，则dp[i][j]=dp[i][j+1]+s2[j]
        else
          dp[i][j] = dp[i + 1][j + 1]; // s1[i]==s2[j]，跳过这两个字符
      }
    return dp[0][0];
  }
};

// 时间复杂度: O(m*n)
// 空间复杂度: O(n)
class Solution
{
 public:
  int minimumDeleteSum(string s1, string s2)
  {
    int m = s1.length(), n = s2.length();
    vector<int> dp(n + 1);
    dp[n] = 0;
    for (int j = n - 1; j >= 0; j--)
      dp[j] = dp[j + 1] + s2[j];
    int temp = 0, dialog = 0; // temp为dp[i+1][j+1]

    for (int i = m - 1; i >= 0; i--)
    {
      dialog += s1[i];
      dp[n] = dialog; // dp[n]为dp[i][n]
      for (int j = n - 1; j >= 0; j--)
        if (s1[i] == s2[j])
        {
          int tm = dp[j];
          dp[j] = temp;
          temp = tm;
        }
        else
        {
          temp = dp[j];
          dp[j] = std::min(s1[i] + dp[j], s2[j] + dp[j + 1]); // 等式左边dp[j]为dp[i][j]，等式右边dp[j]为dp[i+1][j]
        }
      temp = dialog; // temp为dp[i+1][j+1]
    }
    return dp[0];
  }
};