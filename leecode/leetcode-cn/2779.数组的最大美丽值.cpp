/*
 * @lc app=leetcode.cn id=2779 lang=cpp
 *
 * [2779] 数组的最大美丽值
 */

// @lc code=start
// 题解：https://leetcode.cn/problems/maximum-beauty-of-an-array-after-applying-operation/
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        // 排序不会影响结果
        sort(nums.begin(), nums.end());
        int n = nums.size(), ans = 0;

        // x 可以被替换成 [x - k, x + k] 范围内的任意一个数，
        // 那么 x 和 y 被如此替换后，相当于两个线段 [x-k, x+k] 与 [y-k, y+k] 有交集，也即  x+k ≥ y-k ，即 y-x ≤ 2k 。
        // 排序后，如果最后一个线段和第一个有交集，则所有的线段都相交
        for (int l = 0, r = 0; r < n; ++r) {
            // 注意，最后一个线段与第一个不相交，但是可能与第二个相交，所以这里必须轮询
            while (nums[r] - nums[l] > 2 * k)
                l++;
            ans = max(ans, r - l + 1);
        }

        return ans;
    }
};
// @lc code=end
