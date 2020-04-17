// 技巧1：前缀和技巧，例如求nums[i]~num[j]，
// 即可以用preSum[i+1]-preSum[j]来计算
// 其中preSum[i+1]表示nums[0]~nums[i]的和，preSum[0]不用

// 技巧2：使用hashmap存储之前的前缀和

// 时间复杂度: O(n)
// 空间复杂度: O(n)
class Solution
{
 public:
  int subarraySum(vector<int> &nums, int k)
  {
    if (nums.empty())
      return 0;
    vector<int> preSum = vector<int>(nums.size() + 1);
    preSum[0] = 0; // 第0位不用，设置这个位是为了for循环中处理方便
    map<int, int> sum2times;
    int ans = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      preSum[i + 1] = preSum[i] + nums[i];
      int sum_j = preSum[i + 1] - k; // 技巧2
      auto it = sum2times.find(sum_j);
      if (it != sum2times.end())
      {
        ans += it->second;
      }
      if (sum_j == 0) // 如果nums[i]==k，即nums[i]单个数的和等于k，也是满足题意的
        ans++;
      auto it2 = sum2times.find(preSum[i + 1]);
      if (it2 != sum2times.end())
        it2->second++;
      else
        sum2times.emplace(preSum[i + 1], 1);
    }
    return ans;
  }
};

// 进一步优化：从上面来看，发现preSum只用到了preSum[i+1]和preSum[i]，只要用一个数字来保存就可以了，不需要使用数组
class Solution
{
 public:
  int subarraySum(vector<int> &nums, int k)
  {
    if (nums.empty())
      return 0;

    int preSum = 0;
    map<int, int> sum2times;
    int ans = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      preSum += nums[i];
      int sum_j = preSum - k;
      auto it = sum2times.find(sum_j);
      if (it != sum2times.end())
      {
        ans += it->second;
      }
      if (sum_j == 0) // 如果nums[i]==k，即nums[i]单个数的和等于k，也是满足题意的
        ans++;
      auto it2 = sum2times.find(preSum);
      if (it2 != sum2times.end())
        it2->second++;
      else
        sum2times.emplace(preSum, 1);
    }
    return ans;
  }
};