/*
计算连续子向量的最大和,
例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。
给一个数组，返回它的最大连续子序列的和(子向量的长度至少是1)。
*/

// 思路1：枚举所有和，一个长度为n的数组，总共有n(n-1)/2个子数组，时间复杂度为O(n^2)，不可行

// 思路2：如果当前累加和为负数，那么再加上一个数，和会小于这个数。所以应该重新累加，并且保存当前的累加和，因为它可能是最大的。
// 时间复杂度：O(n)
class Solution
{
 public:
  bool m_gInputValid = false;
  int FindGreatestSumOfSubArray(vector<int> array)
  {
    if (array.empty())
    {
      m_gInputValid = false;
      return 0;
    }
    m_gInputValid = true;
    int curSum = array[0];
    int maxSum = curSum;
    for (size_t i = 1; i < array.size(); i++)
    {
      if (curSum >= 0)
        curSum += array[i];
      else
        curSum = array[i];
      if (maxSum < curSum)
        maxSum = curSum;
    }
    return maxSum;
  }
};

// @Athor zzg
// 如果下一个数是负数，那么当前和加上它一定会变小，那么存下当前和，因为当前和可能是最大和；
// 如果当前和小于0，那么它加上下一个数则会小于下一个数，所以最大和一定不可能是它们的和，所以把当前和重置为下一个数；
// 否则当前和加上下一个数
class Solution
{
 public:
  int FindGreatestSumOfSubArray(vector<int> array)
  {
    if (array.empty())
      return 0;
    int maxSum = array[0];
    int curSum = array[0];
    for (int i = 1; i < array.size(); i++)
    {
      if (array[i] < 0)
      {
        if (maxSum < curSum) // 如果把这个放到最后判断，那么不需要判断array[i]是否小于0
          maxSum = curSum;
      }
      if (curSum < 0)
        curSum = array[i];
      else
        curSum += array[i];
    }
    return maxSum > curSum ? maxSum : curSum;
  }
};

// 思路3：动态规划
//
// 用f(i)表示第i个数字结尾的子数组的最大和
// 那么要求出 maxSum[f(i)], 0<=i<=n. 得到递归公式：
//
// f(i) = data[i], i=0或者f(i-1)<=0;
// f(i) = f(i-1)+data[i], i>0并且f(i-1)>0.
//
// 基于循环的代码如上。殊途同归。
//
// curSum对应f(i)
// max[f(i)]对应maxSum
