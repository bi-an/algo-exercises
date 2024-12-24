/*
 * @lc app=leetcode.cn id=3134 lang=cpp
 *
 * [3134] 找出唯一性数组的中位数
 */

// @lc code=start
// 二分查找 + 滑动窗口
// 官方题解：https://leetcode.cn/problems/find-the-median-of-the-uniqueness-array/solutions/2890132/zhao-chu-wei-yi-xing-shu-zu-de-zhong-wei-tdob/
// 时间：O(nlogn)
// 空间：O(n) ，哈希表的空间。
// 总共有 m = n(n+1)/2 个非空子数组，每个子数组（中不同元素的数量）对应“唯一性数组”的一项。
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        long long k = ((long long)(n + 1) * n / 2 + 1) / 2;  // 中位数下标向上取整，因为从 1 开始计数。
        int left = 1, right = n;
        // 闭区间二分查找中位数（即下标 k 对应的那个数）
        while (left <= right) {
            int mid = left + (right - left) / 2;
            // 滑动窗口统计“不同元素的数量 ≤ mid ”的子数组的个数
            // 也就是“唯一性数组”的第 subarr 个元素（从 1 开始计数）
            long long subarr = 0;
            unordered_map<int, int> cnt;  // 或命名为 freq
            for (long long l = 0, r = 0; r < n; ++r) {
                ++cnt[nums[r]];
                while (cnt.size() > k) {
                    int x = nums[l++];
                    if (--cnt[x] == 0)
                        cnt.erase(x);  // 哈希表删除元素是 O(1) 的时间
                }
                subarr += r - l + 1;
            }
            if (subarr >= k)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
};
// @lc code=end
