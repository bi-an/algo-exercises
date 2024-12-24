/*
 * @lc app=leetcode.cn id=930 lang=cpp
 *
 * [930] 和相同的二元子数组
 */

// @lc code=start
// 恰好型滑动窗口
// "= goal" 等价于 "≤ goal" 减去 "< goal"
class Solution {
public:
    int numSubarraysWithSum(vector<int> &nums, int goal) {
        int n = nums.size(), ans = 0, sum1 = 0, sum2 = 0;
        // 遍历窗口右端点
        for (int left1 = 0, left2 = 0, right = 0; right < n; ++right) {
            int x = nums[right];
            sum1 += x;
            sum2 += x;
            // 小于等于
            while (left1 <= right && sum1 > goal)
                sum1 -= nums[left1++];
            // 小于
            while (left2 <= right && sum2 >= goal)
                sum2 -= nums[left2++];
            // ans += (right - left1 + 1) - (right - left2 + 1);
            ans += left2 - left1; // 差集
        }
        return ans;
    }
};
// @lc code=end


/**************************************************/
/********************* 历史解法 ********************/
/**************************************************/

class Solution {
public:
    int numSubarraysWithSum(vector<int> &A, int S) {
        if (A.empty())
            return 0;
        int preSum = 0;
        int *sum2times = new int[A.size() + 1]();  // 初始化为0
        int ans = 0;
        for (int i = 0; i < A.size(); i++) {
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
class Solution {
public:
    int numSubarraysWithSum(vector<int> &A, int S) {
        if (A.empty())
            return 0;
        int preSum = 0;
        int *sum2times = new int[A.size() + 1]();  // 初始化为0
        sum2times[0] = 1;                          // 第0个元素设为1，而不是0
        int ans = 0;
        for (int i = 0; i < A.size(); i++) {
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
    int numSubarraysWithSum(vector<int> &nums, int goal) {
        int res = 0;
        unordered_map<int, int> cnt;  // 记录前缀和的出现次数
        int sum = 0;
        for (int num : nums) {
            ++cnt[sum];  // preSum的个数+1。
                         // 特别地，初始时，cnt[0]加完等于1，因为如果从第0个到当前位置的sum恰等于goal的话，
                         // res+=cnt[preSum]，此时的cnt[preSum]要为1才行。
            sum += num;
            if (cnt.find(sum - goal) != cnt.end())  // sum - preSum == goal时，应该加上preSum的个数
                res += cnt[sum - goal];
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
    int numSubarraysWithSum(vector<int> &nums, int goal) {
        int n = nums.size(), ret = 0;
        int left1 = 0, left2 = 0, right = 0, sum1 = 0, sum2 = 0;
        while (right < n) {
            sum1 += nums[right];
            while (left1 <= right && sum1 > goal) {
                sum1 -= nums[left1];
                left1++;
            }
            sum2 += nums[right];
            while (left2 <= right && sum2 >= goal) {
                sum2 -= nums[left2];
                left2++;
            }
            ret += left2 - left1;
            right++;
        }
        return ret;
    }
};