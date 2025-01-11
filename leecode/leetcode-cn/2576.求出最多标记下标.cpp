/*
 * @lc app=leetcode.cn id=2576 lang=cpp
 *
 * [2576] 求出最多标记下标
 */

// 方法一：排序 + 同向双指针
// 时间复杂度O(nlogn)
// 空间复杂度O(logn)，排序需要的栈空间为O(logn)
class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        // 先排序
        // 时间复杂度O(nlogn)
        // 空间复杂度O(logn)，排序需要的栈空间为O(logn)
        std::sort(nums.begin(), nums.end());

        // 贪心算法：尽可能让 nums[i] 和 nums[j] ，才能尽可能多地找到合法对。
        // 需要注意的是，我们需要让最左边的一半和最右边的一半匹配
        // 否则直接使用双指针会有重复：例如[1,2,4]，会计入(1,2)和(2,4)，显然2已经被标记一次了
        // j 的起始点要向上取整，保证 i 和 j 严格对称
        // 双指针的时间复杂度O(n)；空间复杂度O(1)

        // // 写法一
        // for (int i = 0, j = (n + 1) / 2; i < n && j < n; ++i, ++j) {
        //     while (j < n && nums[i] * 2 > nums[j]) {
        //         ++j;
        //     }
        //     if (j >= n)
        //         break;
        //     ans += 2;
        // }
        // return ans;

        // 写法二
        int i = 0;
        for (int j = (n + 1) / 2; j < n; ++j) {
            // 2 * nums[i] ≤ 2 * 10⁹ ≤ 2 * (2¹⁰)³ = 2³¹ ，没有超过 int 的范围
            if (nums[i] * 2 <= nums[j])
                i++;
        }
        return i * 2;
    }
};

namespace solution_2 {

// @lc code=start
// 方法二：排序 + 二分查找答案
// 该方法效率比方法一更低，因为会有重复验证
class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        ranges::sort(nums);

        int n = nums.size();

        auto check = [&](int k) {
            for (int i = 0; i < k; ++i) {
                if (nums[i] * 2 > nums[n - k + i])
                    return false;
            }
            return true;
        };

        // 二分查找答案（下标对的个数）
        int left = 0, right = n / 2 + 1;  // 开区间
        // 如果 n = 0 ，不需要查找，直接返回 0 .
        while (left + 1 < right) {
            int mid = left + ((right - left) >> 1);
            (check(mid) ? left : right) = mid;
        }

        return left * 2;
    }
};
// @lc code=end

}  // namespace solution_2
