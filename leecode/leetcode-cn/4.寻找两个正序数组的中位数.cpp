/*
 * @Author: your name
 * @Date: 2021-09-04 12:38:37
 * @LastEditTime: 2022-07-03 16:26:58
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\4.寻找两个正序数组的中位数.cc
 */

// 双指针遍历
// 时间 O(m+n)
// 空间 O(1)
//
// 思路：两个数组都是有序的，所以我们可以分别使用一个指针遍历，一边遍历一边计数，
// 直到找到第 k 个数（对于中位数 k = (m+n)/2 ）。
class Solution
{
 public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
  {
    int i = 0, j = 0, n1 = nums1.size(), n2 = nums2.size();
    int k = 0;
    int last = 0, cur = 0;
    double ans = 0;
    while (k++ <= (n1 + n2) / 2)
    {
      last = cur;
      if (i < n1 && j < n2)
      {
        if (nums1[i] < nums2[j])
        {
          cur = nums1[i++];
        }
        else
        {
          cur = nums2[j++];
        }
      }
      else if (i < n1)
      {
        cur = nums1[i++];
      }
      else
      {
        cur = nums2[j++];
      }
    }
    if ((n1 + n2) % 2 == 0)
    {
      ans = (last + cur) / 2.0;
    }
    else
    {
      ans = cur;
    }
    return ans;
  }
};

// 双指针 + 二分查找
// 时间 O(log(m+n))
// 空间 O(1)
//
// 思路：由于两个数组是有序的，方法一的双指针可以尝试增大步长，可以每次越过 k/2
// 步。 此时的 k 是当前搜索空间的长度。
//
// 二分查找的本质：
// 二分查找本质上是不断将搜索空间长度减半的过程。如果用搜索步长来描述，就是不断将步长减半。
class Solution
{
 public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
  {
    int n1 = nums1.size(), n2 = nums2.size();
    if ((n1 + n2) % 2 == 0)
    {
      return (getKthNum(nums1, nums2, (n1 + n2) / 2)
              + getKthNum(nums1, nums2, (n1 + n2) / 2 + 1))
             / 2.0;
    }
    else
    {
      return getKthNum(nums1, nums2, (n1 + n2) / 2 + 1);
    }
  }

  // k 从 1 开始，因为 k 表示的是搜索区间长度
  int getKthNum(vector<int> &nums1, vector<int> &nums2, int k)
  {
    int i = 0, j = 0, n1 = nums1.size(), n2 = nums2.size();
    if (k > n1 + n2)
      return -1;
    while (k > 1)
    {
      // 如果我们要寻找第 k 大的数，那么必须要保证步长不得超过 k/2.
      // 原因见图解。
      int delta = k / 2 - 1;
      if (i + delta < n1 && j + delta < n2)
      {
        if (nums1[i + delta] < nums2[j + delta])
        {
          i += delta + 1;
        }
        else
        {
          j += delta + 1;
        }
      }
      else if (i + delta < n1)
      {
        i += delta + 1;
      }
      else if (j + delta < n2)
      {
        j += delta + 1;
      }
      k -= k / 2;
    }
    if (i < n1 && j < n2)
    {
      return min(nums1[i], nums2[j]);
    }
    else if (i < n1)
    {
      return nums1[i];
    }
    return nums2[j];
  }
};

// 方法三：划分数组
// 时间复杂度：O(log min(m, n))
// 空间复杂度：O(1)
// @ref 官方题解
// TODO