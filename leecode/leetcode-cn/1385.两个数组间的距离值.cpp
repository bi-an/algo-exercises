/*
 * @lc app=leetcode.cn id=1385 lang=cpp
 *
 * [1385] 两个数组间的距离值
 */

// 排序 + 二分查找
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans = 0;
        ranges::sort(arr2);
        for (auto x : arr1) {
            // 尽可能接近 x
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

namespace solution_2 {

// @lc code=start
// 排序 + 双指针
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        ranges::sort(arr1);
        ranges::sort(arr2);

        int n = arr2.size(), ans = 0, j = 0;
        for (auto x : arr1) {
            // 尽可能接近 x
            // 找到第一个 大于等于 x 的元素
            while (j < n && arr2[j] < x)
                ++j;
            int diff = INT_MAX;
            if (j < n)
                diff = min(diff, abs(x - arr2[j]));
            if (j > 0)
                diff = min(diff, abs(x - arr2[j - 1]));
            if (diff > d)
                ++ans;
        }

        return ans;
    }
};
// @lc code=end

}  // namespace solution_2
