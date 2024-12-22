/*
 * @lc app=leetcode.cn id=2762 lang=cpp
 *
 * [2762] 不间断子数组
 */

// @lc code=start
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        // 平衡树可以在增删过程中快速取出最大和最小值
        multiset<int> vis;  // visited in the window
        for (int l = 0, r = 0; r < n; ++r) {
            vis.insert(nums[r]);
            while (!vis.empty() && *vis.rbegin() - *vis.begin() > 2) {
                // vis.erase(nums[l++]); // 错误！使用 key 会将重复元素一次性全部删除
                vis.erase(vis.find(nums[l++]));  // 使用迭代器删除
            }
            ans += r - l + 1;
        }
        return ans;
    }
};
// @lc code=end
