/*
Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n.
求0~2^n中的所有数中，每个位上的数字都不同的数的总个数

Example:
Input: 2
Output: 91 
Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100, 
             excluding 11,22,33,44,55,66,77,88,99
*/

// 找规律：n位数，每两个位上的数字都不相同的数个数为dp[n]
// n=1, dp=C(10,1) // C(10,1)表示组合数，10个中取1个
// n=2, dp=C(9,1)*C(9,1) // 第一个数可能是1~9，第二个数可能是0~9中除去第一个数相同的
// n=3, dp=C(9,1)*C(9,1)*C(8,1) // 第一个数可能是1~9，第二数可能是0~9中除去第一个数，第三个数可能是0~9中除去第一、二个数
// ...
// n=10, dp=C(9,1)*C(9,1)*...*C(1,1)
// n>10, 一定会有两个位是相同的，所以返回0.
// n==0, 返回1 // 0 ≤ x < 10^n, 那么x可以为0，也就是有1个
class Solution
{
 public:
  int countNumbersWithUniqueDigits(int n)
  {
    if (n < 0 || n > 10)
      return 0;
    if (n == 0)
      return 1;
    if (n == 1)
      return 10;
    vector<int> dp(n); // dp[i]保存i位数的每位都不相同的数字个数
    dp[0] = 10;
    dp[1] = 9 * 9;
    int factor = 9, res = dp[0] + dp[1];
    for (int i = 2; i < n; i++)
    {
      factor--;
      dp[i] = dp[i - 1] * factor; // 由于是不断连乘，所以可以利用前面的结果，减小时间复杂度
      res += dp[i];
    }
    return res;
  }
};