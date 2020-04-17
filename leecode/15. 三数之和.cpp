
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
      int l = i + 1, r = n - 1;
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