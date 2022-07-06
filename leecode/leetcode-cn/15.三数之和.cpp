/**
 * 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？
 * 请你找出所有满足条件且不重复的三元组。
 * 
 * 注意：答案中不可以包含重复的三元组。
 * 
 * 示例：
 * 
 * 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
 * 满足要求的三元组集合为：
 * [
 *   [-1, 0, 1],
 *   [-1, -1, 2]
 * ]
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/3sum
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

#include <vector>
#include <algorithm>
using namespace std;

// 错误解法：用两边向中间的方法无法去重
class Solution
{
 public:
  vector<vector<int>> threeSum(vector<int> &nums)
  {
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    //int last = 0;
    for (int i = 1; i < nums.size(); i++)
    {
      int l = i - 1, r = i + 1;
      //if(!ans.empty() && nums[i]==last)
      //  continue;
      while (l >= 0 && r < nums.size())
      {
        int sum = nums[i] + nums[l] + nums[r];
        if (sum == 0)
        {
          if (l >= 1 && nums[l] == nums[l - 1])
          {
            l--;
            continue;
          }
          else if (r < (int)nums.size() - 1 && nums[r] == nums[r + 1])
          {
            r++;
            continue;
          }
          else
          {
            vector<int> tmp;
            tmp.push_back(nums[l]);
            tmp.push_back(nums[i]);
            tmp.push_back(nums[r]);
            ans.push_back(tmp);
            //last = nums[i];
            //break;
            l--, r++;
          }
        }
        else if (sum > 0)
          l--;
        else
          r++;
      }
    }
    return ans;
  }
};

// 优化
class Solution
{
 public:
  vector<vector<int>> threeSum(vector<int> &nums)
  {
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end()); // 先排序
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      //int fix = nums[i];
      if (nums[i] > 0)
        break;
      if (i > 0 && nums[i] == nums[i - 1]) // 去重
        continue;
      int l = i + 1, r = n - 1; // 左右到中间
      while (l < r)
      {
        int sum = nums[i] + nums[l] + nums[r];
        if (sum == 0)
        {
          if (l + 1 != r && nums[l] == nums[l + 1])
          {
            l++; // continue;
          }
          else if (r - 1 != l && nums[r] == nums[r - 1])
          {
            r--; // continue;
          }
          else
          {
            //vector<int> tmp;
            //tmp.push_back(nums[i]);
            //tmp.push_back(nums[l]);
            //tmp.push_back(nums[r]);
            //ans.push_back(tmp);
            ans.push_back(vector<int>{ nums[i], nums[l], nums[r] });
            l++, r--;
          }
        }
        else if (sum > 0)
          r--;
        else
          l++;
      }
    }
    return ans;
  }
};

// 写法二
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            // 剪枝，实测效率提升不大，可以去掉
            if (i + 2 < n && nums[i] + nums[i + 1] + nums[i + 2] > 0)
                break;
            if (i < n - 2 && nums[i] + nums[n - 2] + nums[n - 1] < 0)
                continue;
            if (i == 0 || nums[i] != nums[i - 1]) {
                int target = 0 - nums[i];
                int l = i + 1, r = n - 1;
                while (l < r) {
                    if (l == i + 1 || nums[l] != nums[l - 1]) {
                        if (nums[l] + nums[r] < target) {
                            ++l;
                        }
                        else if (nums[l] + nums[r] > target) {
                            --r;
                        }
                        else {
                            res.push_back({nums[i], nums[l], nums[r]});
                            ++l;
                        }
                    } else {
                        ++l;
                    }
                }
            }
        }
        return res;
    }
};