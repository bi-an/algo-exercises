/*
 * @lc app=leetcode.cn id=2300 lang=cpp
 *
 * [2300] 咒语和药水的成功对数
 */

// 排序 + 双指针
// 时间复杂度：O(mlogm + nlogn)，排序时间。
// 空间复杂度：O(m)
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int m = spells.size(), n = potions.size();

        vector<pair<int, int>> rec(m);
        for (int i = 0; i < m; ++i)
            rec[i] = make_pair(spells[i], i);

        ranges::sort(rec, greater<pair<int, int>>());
        ranges::sort(potions);

        vector<int> ans(m);
        for (int i = 0, j = 0; i < m; ++i) {
            long long x = rec[i].first;
            while (j < n && potions[j] * x < success)
                j++;
            if (j < n)
                ans[rec[i].second] = n - j;
        }

        return ans;
    }
};

namespace solution_2 {

// @lc code=start
// 排序 + 二分查找
// 时间复杂度：
// 空间复杂度：
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        ranges::sort(potions);
        int n = potions.size(), i = 0, j;
        vector<int> ans(spells.size());
        for (long long x : spells) {
            j = ranges::lower_bound(potions, (success + x - 1) / x) - potions.begin();
            ans[i++] = n - j;
        }
        return ans;
    }
};
// @lc code=end

}  // namespace solution_2
