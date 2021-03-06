/**
 * 回溯法
 */

#include <bits/stdc++.h>
using namespace std;

// 方法1
// 从数字的角度来看，每个数字可以选择填入任何一个桶
// 时间复杂度：O(k^n)，因为共有n个数字，每个数字均有k种选择
class Solution
{
 public:
  bool canPartitionKSubsets(vector<int> &nums, int k)
  {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
      sum += nums[i];

    if (nums.empty() || sum % k != 0 || nums.size() < k)
      return false;

    // 由大到小排序，这样容易触发backtrace()的剪枝条件，减少递归次数，减少运算时间
    std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });

    int target = sum / k;
    vector<int> sumOfBin(k);
    return backtrace(nums, 0, sumOfBin, target);
  }

  bool backtrace(vector<int> &nums, int index, vector<int> &sumOfBin, int target)
  {
    int k = sumOfBin.size();
    if (index == nums.size())
    {
      for (int i = 0; i < k; i++)
      {
        if (sumOfBin[i] != target)
          return false;
      }
      return true;
    }

    for (int i = 0; i < k; i++)
    {
      // 剪枝
      if (sumOfBin[i] + nums[index] > target)
        continue;

      /// 回溯
      // 选择
      sumOfBin[i] += nums[index];
      // 返回递归结果
      if (backtrace(nums, index + 1, sumOfBin, target))
        return true;
      // 撤销选择
      sumOfBin[i] -= nums[index];
    }

    return false;
  }
};

// 方法2
// 从桶的角度来看，先填满一个桶，再填下一个桶，把所有的数字都填完
// 时间复杂度：O(k*2^n)，填某个桶，对所有数字遍历，该数可以选择填入，也可以选择不填入，所以有2^n种可能；而共有k个桶。
class Solution
{
 public:
  bool canPartitionKSubsets(vector<int> &nums, int k)
  {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
      sum += nums[i];

    if (nums.empty() || nums.size() < k || sum % k != 0)
      return false;
    int target = sum / k;
    vector<bool> used(nums.size(), false);
    vector<int> bucket(k, 0);
    return backtrace(nums, used, bucket, 0, 0, target);
  }

  bool backtrace(vector<int> &nums, vector<bool> &used, vector<int> &bucket, int index, int start, int target)
  {
    int k = bucket.size();
    if (index == k)
      return true;

    // Tip
    if (bucket[index] == target) // 第index个bucket填满了，开始填下一个bucket
      return backtrace(nums, used, bucket, index + 1, 0, target); // start清0

    for (int i = start; i < nums.size(); i++)
    {
      if (used[i] || bucket[index] + nums[i] > target)
        continue;
      bucket[index] += nums[i];
      used[i] = true;
      // 该桶还没有填完，递归填入
      if (backtrace(nums, used, bucket, index, i + 1, target)) // 函数的start参数(i+1)用来避免重复计算
        return true;
      bucket[index] -= nums[i];
      used[i] = false;
    }
    return false;
  }
};

// 方法3
// 可以看到，bucket不需要额外空间
class Solution
{
 public:
  bool canPartitionKSubsets(vector<int> &nums, int k) {
    int sum = accumulate(nums.begin(), nums.end(),  0); // STL求和函数
    if(nums.empty() || k <= 0 || nums.size() < k || sum % k != 0)
      return false;
    int target = sum / k;
    vector<bool> used(nums.size(), false);
    int bucket = 0;
    return backtrace(nums, used, bucket, k, 0, target);
  }

  bool backtrace(vector<int> &nums, vector<bool> &used, int bucket, int k, int start, int target)
  {
    if (k == 0)
      return true;
    if (bucket == target) // 第k个桶填满了，填下一个桶
      return backtrace(nums, used, 0, k-1, 0, target); // bucket和start重置为0

    for(int i=start;i<nums.size();i++) {
      if(used[i] || nums[i] + bucket > target)
        continue;
      bucket+=nums[i];
      used[i] = true;
      if(backtrace(nums, used, bucket, k, i+1, target))
        return true;
      bucket-=nums[i];
      used[i] = false;
    }

    return false;
  }
};