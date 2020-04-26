/*
Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
 
Example 2:
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

Note:
The input string length won't exceed 1000.
*/

// 从中心往两边
// Time Complexity: O(N^2), where NN is the length of S. Each expansion might do O(N)O(N) work.
// Space Complexity: O(1).
class Solution
{
 public:
  int countSubstrings(string S)
  {
    int N = S.length(), ans = 0;
    for (int center = 0; center <= 2 * N - 1; ++center)
    {
      int left = center / 2; // 初始化为子串中心，center不是子串中心，center/2才是
      // 子串长度分别为1,2,...,n 所以子串中心分别为0,(0,1),1,(1,2),...,(n-2,n-1),n-1 所以若center为奇数，right=left+1
      // 同时可以看到，子串个数为2*n-1个(等于子串中心的个数)
      int right = left + center % 2;
      while (left >= 0 && right < N && S[left] == S[right])
      {
        ans++;
        left--;
        right++;
      }
    }
    return ans;
  }
};

// 动态规划
// dp[i][j]表示从第i个字符到第j个字符是否是回文数，是则true，否则false
// 如果i==j，则dp[i][j]=true;
// 如果j-i==1，则如果s[i]==s[j]，则dp[i][j]=true;
// 如果j-i==2，则如果s[i]==s[j]，则dp[i][j]=true;
// 如果J-i>2，则如果s[i]==s[j] && dp[i+1][j-1]，则dp[i][j]=true.(最左和最右相同，并且中间是回文数，那么从i到j的字符是回文数)
class Solution
{
 public:
  int countSubstrings(string s)
  {
    int n = s.size(), res = 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = n - 1; i >= 0; i--)
      for (int j = n - 1; j >= i; j--)
        if (s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1]))
        {
          dp[i][j] = true;
          res++;
        }
    return res;
  }
};