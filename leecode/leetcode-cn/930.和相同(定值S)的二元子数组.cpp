/*
在由若干 0 和 1  组成的数组 A 中，有多少个和为 S 的非空子数组。

示例：

输入：A = [1,0,1,0,1], S = 2
输出：4
解释：
如下面黑体所示，有 4 个满足题目要求的子数组：
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-subarrays-with-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <vector>
using namespace std;

// 本题与“560.和为K的子数组”类似，但是因为数组中只有0和1
// 所以可以对hashmap优化，数组下标表示sum（因为sum不会超过n），作为hasmap的key；
// hashmap的value为前缀和出现的次数

class Solution
{
 public:
  int numSubarraysWithSum(vector<int> &A, int S)
  {
    if (A.empty())
      return 0;
    int preSum = 0;
    int *sum2times = new int[A.size() + 1](); // 初始化为0
    int ans = 0;
    for (int i = 0; i < A.size(); i++)
    {
      preSum += A[i];
      int sum_j = preSum - S;
      if (sum_j >= 0)
        ans += sum2times[sum_j];
      if (sum_j == 0)
        ans++;
      sum2times[preSum]++;
    }
    return ans;
  }
};

// 初始化技巧
// 注意到我们每次都要判断sum_j为0（即A[i]本身等于S）的情况
// 这可以通过将sum2times[0]初始为1来避免这一判断，1表示本身等于S也要计入
class Solution
{
 public:
  int numSubarraysWithSum(vector<int> &A, int S)
  {
    if (A.empty())
      return 0;
    int preSum = 0;
    int *sum2times = new int[A.size() + 1](); // 初始化为0
    sum2times[0] = 1; // 第0个元素设为1，而不是0
    int ans = 0;
    for (int i = 0; i < A.size(); i++)
    {
      preSum += A[i];
      int sum_j = preSum - S;
      if (sum_j >= 0)
        ans += sum2times[sum_j];
      // if(sum_j==0) ans++; // 这一步不需要了
      sum2times[preSum]++;
    }
    return ans;
  }
};


// 方法一：hashtable + 前缀和
// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int res = 0;
        unordered_map<int,int> cnt; // 记录前缀和的出现次数
        int sum = 0;
        for(int num : nums) {
            ++cnt[sum]; // preSum的个数+1。
                        // 特别地，初始时，cnt[0]加完等于1，因为如果从第0个到当前位置的sum恰等于goal的话，
                        // res+=cnt[preSum]，此时的cnt[preSum]要为1才行。
            sum += num;
            if(cnt.find(sum - goal) != cnt.end()) // sum - preSum == goal时，应该加上preSum的个数
                res += cnt[sum-goal];
        }
        return res;
    }
};

// 方法二：区间指针/双指针
// 时间复杂度：O(n)
// 空间复杂度：O(1)
