/*
 * @lc app=leetcode.cn id=2799 lang=cpp
 *
 * [2799] 统计完全子数组的数目
 */

// @lc code=start
class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int k = unordered_set<int>(nums.begin(), nums.end()).size();
        // m 记录滑动窗口中有多少个数没有被访问，以避免对哈希表频繁删除，
        // 因为哈希表底层可能是数组，随机删除数组元素会导致数据搬移，代价较大。
        // left 滑动窗口左端点
        int ans = 0, m = k, left = 0;
        for (int x : nums) { // 枚举滑动窗口右端点指向的元素
            m -= cnt[x]++ == 0;
            // 先找最小区间
            while (m == 0)
                m += --cnt[nums[left++]] == 0;
            // left 指向最小区间左端点的下一个位置
            ans += left;
        }
        return ans;
    }
};
// @lc code=end
