/*
 * @lc app=leetcode.cn id=1385 lang=cpp
 *
 * [1385] 两个数组间的距离值
 */

// @lc code=start
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans = 0;
        ranges::sort(arr2);
        for (auto x : arr1) {
            // i 总是靠右，所以也需要检查前一个数
            // 使用 upper_bound 也行，判定条件不变
            auto i = ranges::upper_bound(arr2, x);
            // auto i = ranges::lower_bound(arr2, x);
            if (i != arr2.end() && abs(*i - x) <= d || i != arr2.begin() && abs(*prev(i) - x) <= d)
                continue;
            ++ans;
        }
        return ans;
    }
};
// @lc code=end
