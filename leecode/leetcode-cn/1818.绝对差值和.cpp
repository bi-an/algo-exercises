/*
 * @lc app=leetcode.cn id=1818 lang=cpp
 *
 * [1818] 绝对差值和
 */

// @lc code=start
// 排序 + 二分查找
class Solution {
    static constexpr int mod = 1'000'000'007;  // 1e9 + 7;
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), sum = 0, delta = 0;
        vector<int> rec(nums1);  // 用于存储 nums1 的副本 record
        ranges::sort(rec);
        for (int i = 0; i < n; ++i) {
            int diff = abs(nums1[i] - nums2[i]);
            sum = (sum + diff) % mod;
            // 写法一
            // auto iter = ranges::lower_bound(rec, nums2[i]);
            // auto left = iter != rec.begin() ? prev(iter) : iter;
            // auto right = iter != rec.end() ? iter : prev(iter);
            // delta = max({delta, diff - abs(*left - nums2[i]), diff - abs(*right - nums2[i])});
            // 写法二
            // 第一个大于等于 nums2[i] 的元素的下标，相当于右边界
            int j = ranges::lower_bound(rec, nums2[i]) - rec.begin();
            // 右边界
            if (j < n)
                delta = max(delta, diff - abs(rec[j] - nums2[i]));
            // 左边界
            if (j > 0)
                delta = max(delta, diff - abs(rec[j - 1] - nums2[i]));
        }
        return (sum - delta + mod) % mod;  // 防止负数
    }
};
// @lc code=end
