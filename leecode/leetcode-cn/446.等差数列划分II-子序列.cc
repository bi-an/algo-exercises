/**
 * 给你一个整数数组 nums ，返回 nums 中所有 等差子序列 的数目。

如果一个序列中 至少有三个元素 ，并且任意两个相邻元素之差相同，则称该序列为等差序列。

例如，[1, 3, 5, 7, 9]、[7, 7, 7, 7] 和 [3, -1, -5, -9] 都是等差序列。
再例如，[1, 1, 2, 5, 7] 不是等差序列。
数组中的子序列是从数组中删除一些元素（也可能不删除）得到的一个序列。

例如，[2,5,10] 是 [1,2,1,2,4,1,5,10] 的一个子序列。
题目数据保证答案是一个 32-bit 整数。

 

示例 1：

输入：nums = [2,4,6,8,10]
输出：7
解释：所有的等差子序列为：
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]
示例 2：

输入：nums = [7,7,7,7,7]
输出：16
解释：数组中的任意子序列都是等差子序列。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// 官方题解: 动态规划 + 哈希表
/**
方法一：动态规划 + 哈希表
我们首先考虑至少有两个元素的等差子序列，下文将其称作弱等差子序列。

由于尾项和公差可以确定一个等差数列，因此我们定义状态 f[i][d] 表示尾项为 nums[i]  ，公差为 d 的弱等差子序列的个数。

我们用一个二重循环去遍历 nums  中的所有元素对 {nums[i], nums[j]}  ，其中 j<i。将 nums[i]  和 nums[j]  分别当作等差数列的尾项和倒数第二项，
则该等差数列的公差 d = nums[i] - nums[j]  。由于公差相同，我们可以将 nums[i]  加到以 nums[j]  为尾项，公差为 d 的弱等差子序列的末尾，
这对应着状态转移 f[i][d] += f[j][d]。

说明：(1) 子序列{..., nums[j]}的个数与子序列{...,nums[j],nums[i]}的个数应该相同，所以应该有 f[i][d] = f[j][d]；
(2) 其中，j ∈ [0, ..., i-1]，每一个 j 都可以构成(1)中表示的一个子序列，所以应该累加起来，也就是使用累加符号（"+=")，即 f[i][d] += f[j][d] 。

同时，(nums[i],nums[j]}  这一对元素也可以当作一个弱等差子序列，故有状态转移

f[i][d] += f[j][d] + 1

由于题目要统计的等差子序列至少有三个元素，我们回顾上述二重循环，其中「将 nums[i]  加到以 nums[j]  为尾项，公差为 d 的弱等差子序列的末尾」这一操作，
实际上就构成了一个至少有三个元素的等差子序列，因此我们将循环中的 f[j][d] 累加，即为答案。

代码实现时，由于 nums[i]  的范围很大，所以计算出的公差的范围也很大，我们可以将状态转移数组 f 的第二维用哈希表代替。
 */
class Solution
{
 public:
  int numberOfArithmeticSlices(vector<int> &nums)
  {
    int n = nums.size(), ans = 0;
    vector<unordered_map<long long, int>> dp(n);

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < i; j++)
      {
        long long d = 1LL * nums[i] - nums[j];
        auto it = dp[j].find(d);
        int cnt = it == dp[j].end() ? 0 : it->second; // 如果dp[j][d]，那么初始化为0
        ans += cnt; // 把nums[i]加在以nums[j]为尾项、d为公差的假等差数列末尾，那么就构成一个新的真等差数列
        dp[i][d] += dp[j][d] + 1; // 不断累加，以更新当前的dp[i][d]
      }
    }

    return ans;
  }
};


// 解法二：常规动态规划。
// 来自leetcode-cn用户 @加油！！！欧里给
// TODO: 没细看，有时间再研究。

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        using ll = long long;
        int n = nums.size();
        if(n<3)return 0;
        unordered_map<ll,vector<int>>check;
        //记录值对应的下标，由于存在重复，所以用数组存
        for(int i=0;i<nums.size();i++){
            check[nums[i]].emplace_back(i);
        }
        //dp[i][j]表示以i和j下标对应最后两元素的等差数列个数，所以存在转移关系:
        //dp[i][j] += dp[j][k]+1;而k是怎么来的呢?
        //nums[j] - nums[k] = nums[i] - nums[j]=>nums[k] = 2*nums[j]-nums[i]
        //一旦存在这样的下标k便可进行状态转移
        int dp[n][n];
        int res = 0;
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                ll target = (ll)2*nums[j]-nums[i];
                vector<int>& t = check[target];
                for(auto&& k:t){
                    if(k<j)
                        dp[i][j] += (dp[j][k]+1);
                }
                res += dp[i][j];
            }
        }
        return res;
    }
};