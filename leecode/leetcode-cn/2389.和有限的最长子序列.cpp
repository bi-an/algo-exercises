/*
 * @lc app=leetcode.cn id=2389 lang=cpp
 *
 * [2389] 和有限的最长子序列
 */

// @lc code=start
// 贪心：每次选最小的，可以得到最大长度
// 排序 + 双指针
class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size(), m = queries.size(), i = 0, j = 0;
        vector<pair<int, int>> rec(m);  // 保存 queries 原先的顺序
        for (int i = 0; i < m; ++i)
            rec[i] = make_pair(queries[i], i);

        ranges::sort(nums);
        ranges::sort(rec);

        long long sum = 0;
        vector<int> ans(m);

        for (auto& [x, j] : rec) {
            while (i < n && sum + nums[i] <= x)
                sum += nums[i++];
            ans[j++] = i;
        }

        return ans;
    }
};
// @lc code=end
