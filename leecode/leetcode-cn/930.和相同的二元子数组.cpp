/*
 * @Author: your name
 * @Date: 2021-07-09 23:16:35
 * @LastEditTime: 2021-07-09 23:37:33
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\930.和相同的二元子数组.cc
 */

/**
 * @brief 
 * 
 * 给你一个二元数组 nums ，和一个整数 goal ，请你统计并返回有多少个和为 goal 的 非空 子数组。
 * 子数组 是数组的一段连续部分。
 * 
 * 示例 1：
 * 
 * 输入：nums = [1,0,1,0,1], goal = 2
 * 输出：4
 * 解释：
 * 有 4 个满足题目要求的子数组：[1,0,1]、[1,0,1,0]、[0,1,0,1]、[1,0,1]
 * 示例 2：
 * 
 * 输入：nums = [0,0,0,0,0], goal = 0
 * 输出：15
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/binary-subarrays-with-sum
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

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
// 每一个right处，都有一段left区间满足条件
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n = nums.size(), ret = 0;
        int left1 = 0, left2 = 0, right = 0, sum1 = 0, sum2 = 0;
        while(right < n) {
            sum1 += nums[right];
            while(left1 <= right && sum1 > goal) {
                sum1 -= nums[left1];
                left1++;
            }
            sum2 += nums[right];
            while(left2 <= right && sum2 >= goal) {
                sum2 -= nums[left2];
                left2++;
            }
            ret += left2 - left1;
            right++;
        }
        return ret;
    }
};