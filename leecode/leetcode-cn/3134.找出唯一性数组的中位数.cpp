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
// 方法1：直接遍历所有子数组，则 O(n²) 会超时。
// 方法2：(1) 遍历不同元素数量为 k = 1..n 的所有情况，其中 k 就是“唯一性数组”的自变量。
//       (2) 每种情况都使用滑动窗口找一次“不同元素个数 = k”的子数组个数，
//        拆成“ ≤ k ” 减去 “ < k ” ，时间复杂度为 O(n) 。
// 改进点1：第 (2) 步改成寻找“不同元素个数 ≤ k”的子数组个数 subarr ，
//         那么 subarr 正好对应“唯一性数组”的第 subarr 项（从 1 开始计数）。
// 改进点2：“唯一性数组”是关于自变量 k 的递增数组，且由“改进点1”可以确定第 subarr 项，
//         我们可以二分查找中位数（即第 ⌈m/2⌉ 项）。
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        // 中位数下标向上取整，因为从 1 开始计数。
        long long k = ((long long)(n + 1) * n / 2 + 1) / 2;
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
