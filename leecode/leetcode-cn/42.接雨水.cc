#include <bits/stdc++.h>
using namespace std;

/**
 * @ref labuladong
 * 
 * 关键在于：i处所能接的雨量为
 *      water[i] = min{左边[0...i]的最高柱子高度, 左边[i...n-1]的最高柱子高度} - height[i];
 */

// 暴力解法
// 时间O(N^2)，空间O(1)
class Solution_1
{
 public:
  int trap(vector<int> &height)
  {
    if (height.empty())
      return 0;
    int n = height.size(), res = 0;

    for (int i = 0; i < n; i++)
    {
      int l_max = height[i], r_max = height[i];
      for (int j = i; j >= 0; j--)
        l_max = max(l_max, height[j]);
      for (int j = i; j < n; j++)
        r_max = max(r_max, height[j]);
      res += min(l_max, r_max) - height[i];
    }

    return res;
  }
};

// 备忘录解法
// 时间O(N)，空间O(N)
//
// 用备忘录记下左边和右边的最高高度，以后就不需要再计算了
class Solution_2
{
 public:
  int trap(vector<int> &height)
  {
    if (height.empty())
      return 0;

    int n = height.size(), res = 0;
    vector<int> l_max(n), r_max(n);
    l_max[0] = height[0], r_max[n - 1] = height[n - 1];
    for (int i = 1; i < n; i++)
      l_max[i] = max(l_max[i - 1], height[i]);
    for (int i = n - 2; i >= 0; i--)
      r_max[i] = max(r_max[i + 1], height[i]);
    for (int i = 0; i < n; i++)
      res += min(l_max[i], r_max[i]) - height[i];

    return res;
  }
};

// 双指针解法
// 时间O(N)，空间O(1)
//
// l_max = max{height[0...left]}
// r_max = max{height[right...n-1]}
//
// 解惑：上面的l_max和r_max的区间并不闭合？
// 由于我们每次计算min{l_max, r_max}指针处的柱子，假设本次在左边，
// 那么，能够保证，指针left指向的是max{height[0...left]}处，
// 至于右边柱子是不是[left...n-1]的最高点并不重要
class Solution_3
{
 public:
  int trap(vector<int> &height)
  {
    if (height.empty())
      return 0;
    int left = 0, right = height.size() - 1;
    int l_max = height[left], r_max = height[right];
    int res = 0;
    while (left < right)
    {
      l_max = max(height[left], l_max);
      r_max = max(height[right], r_max);
      if (l_max < r_max)
      {
        res += l_max - height[left];
        left++;
      }
      else
      {
        res += r_max - height[right];
        right--;
      }
    }
    return res;
  }
};
