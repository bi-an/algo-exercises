/*
 * @lc app=leetcode.cn id=3171 lang=cpp
 *
 * [3171] 找到按位或最接近 K 的子数组
 */

#include <bits/stdc++.h>
using namespace std;

// @lc code=start
//
// 方法一：滑动窗口 + 后缀数组
// 题解：https://leetcode.cn/problems/find-subarray-with-bitwise-or-closest-to-k/solutions/2798206/li-yong-and-de-xing-zhi-pythonjavacgo-by-gg4d
//
// 因为都是正整数，所以参与 OR 运算的数越多， OR 值越大，具有单调性（随着数字个数的增加而增加），可以考虑滑动窗口。
// 我们要求 OR 值与 k 的差的最小绝对值：
//  (1) 当 OR 值 > k 时，应该缩小窗口，使得 OR 值变小，逐渐接近 k （这个过程中应该更新答案）；
//  (2) 当 OR 值 ≤ k 时，应该扩大窗口，使得 OR 值变大，逐渐接近 k （这个过程中应该更新答案）。
// 但是与加法不同， OR 运算没有逆运算，我们可以用额外的后缀数组来减少重复运算。
// 假设我们已经有一个窗口 [left, right] ，
//  (1) 当缩小窗口，即 left 不断右移时，我们一次性将原窗口中的后缀 OR 值从右到左计算出来保存到数组中，即
//         suffix[right] = nums[right] ；
//         suffix[right-1] = nums[right] | nums[right-1] ；
//         suffix[right-2] = nums[right] |  nums[right - 1] | nums[right-2] ；
//         ...
//         suffix[left] = nums[right] | ... | nums[left] 。
//      这样当 left 右移时，suffix[left+1] 就是从 left+1 到 right 的 OR 运算的结果。
//  (2) 当扩大窗口，即 right 不断右移时，显然之前保存的后缀数组的每个数都需要与新的 nums[right] 进行一次 OR 运算，时间复杂度为 O(n)；
//      为了避免这种计算，我们保持后缀数组不变，用一个 right_or 来计算从原来的 right 到新的 right 的 OR 值，
//      这样整个窗口被分成了左、右两个半部，整个窗口的 OR 值 = suffix[left] | right_or 。
// 注意到，因为我们已经把结果都保存到了后缀数组中，左半部的数已经不会再使用了，所以我们可以直接在原数组中保存 suffix 的结果，降低空间复杂度。
class Solution {
   public:
    int minimumDifference(vector<int>& nums, int k) {
        // mid 是后缀数组的右边界
        // right_or 表示右半部的 OR 值
        int n = nums.size(), left = 0, mid = 0, right_or = 0, ans = INT_MAX;
        for (int right = 0; right < n; ++right) {
            right_or |= nums[right];
            // 缩小窗口
            while (left <= right && (nums[left] | right_or) > k) {
                ans = min(ans, (nums[left] | right_or) - k);  // 更新答案
                left++;
                // left 已经越过了后缀数组右边界，意味着窗口左半部已经计算完毕
                if (mid < left) {
                    // 现在右半部全部纳入左半部
                    for (int i = right - 1; i >= left; --i) {
                        nums[i] |= nums[i + 1];
                    }
                    // 现在右半部全部纳入了左半部
                    right_or = 0;
                    mid = right;
                }
            }
            // 窗口依然有效
            // 现在窗口内的 OR 值 ≤ k
            if (left <= right)
                ans = min(ans, k - (nums[left] | right_or));  // 更新答案，因为窗口被
                                                              // 扩大了一次（right右移）
        }
        return ans;
    }
};
// @lc code=end


void test1() {
    vector<int> nums = {1,2,4,5};
    int k = 3;
    Solution sol;
    int ans = sol.minimumDifference(nums, k);
    cout << ans << endl;
}

int main() {

    test1();

    return 0;
}