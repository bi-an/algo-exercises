/*
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Follow up:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

// 这与《剑指offer》的最大连续数字和是一样的题目
class Solution
{
 public:
  int maxSubArray(vector<int> &nums)
  {
    if (nums.empty())
      return 0;
    int curSum = nums[0], maxSum = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
      if (nums[i] < 0)
      {
        if (curSum > maxSum)
          maxSum = curSum;
      }
      if (curSum < 0)
        curSum = nums[i];
      else
        curSum += nums[i];
    }
    if (curSum > maxSum)
      maxSum = curSum;
    return maxSum;
  }
};