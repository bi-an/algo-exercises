/*
 * @lc app=leetcode.cn id=2389 lang=cpp
 *
 * [2389] 和有限的最长子序列
 */

// 贪心：每次选最小的，可以得到最大长度
// 排序 + 双指针
// 时间复杂度：O(nlogn + mlogm)
// 空间复杂度：O(m)
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

namespace solution_2 {

// @lc code=start
// 官方题解：https://leetcode.cn/problems/longest-subsequence-with-limited-sum/solutions/2172081/he-you-xian-de-zui-chang-zi-xu-lie-by-le-xqox/
// 贪心：每次选最小的，可以得到最大长度
// 排序 + 前缀和 + 二分
// 时间复杂度：O((n+m)logn)
// 空间复杂度：O(n)
class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        ranges::sort(nums);

        int n = nums.size(), m = queries.size();
        vector<int> ans(m), f(n + 1);  // f 表示 nums 的前缀和

        for (int i = 0; i < n; ++i)
            f[i + 1] = f[i] + nums[i];

        int j = 0;
        for (auto x : queries) {
            auto i = ranges::upper_bound(f, x) - f.begin();
            ans[j++] = i - 1;  // 前缀和数组长度为 n+1
        }

        return ans;
    }
};
// @lc code=end

}  // namespace solution_2
