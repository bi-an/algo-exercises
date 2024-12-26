/*
 * @lc app=leetcode.cn id=2856 lang=cpp
 *
 * [2856] 删除数对后的最小数组长度
 */

// 题解：https://leetcode.cn/problems/minimum-array-length-after-pair-removals/solutions/2446146/olog-n-tan-xin-er-fen-cha-zhao-pythonjav-t3qn/
// 证明要看视频讲解。
// 题意就是不同的数就可以成对被消除。
// 从特例出发，发现：最后剩下的数一定是值相同的，并且似乎总是出现次数最多的数。
// 设 a 出现次数最多，其出现次数为 maxCnt ：
// （1）如果 maxCnt·2 == n ，那么其他的数都可以与之配对全部被消除，剩余的数个数为 0 ；
// （2）如果 maxCnt·2 > n ，那么其他数一定可以与之配对消除，但是其本身将剩下
// maxCnt - (n - maxCnt) = 2·maxCnt - n 个；
// （3）如果 maxCnt·2 < n ，那么我们假设有三种数分别为 a, b, c，其出现次数分别为 x, y, z ，其中 x ≥ y ≥ z 。
// a）由于 maxCnt 不足 n 的一半，那么如果优先消除 x 的话，x 可以被完全消除。
// b）先让 y 和 z 互相消除一部分，剩下的数如果和 x 的个数相等，那么所有数都能被消除。
// 显然，我们可以做到 y 和 z 互消之后只剩 y - z 个。如果我们能证明 y - z ≤ x ，那么所有的数都可以被消除。
// 即 y ≤ x + z ，由于 x 是出现次数最多的数，该式显然成立。
// 综合 a）和 b），如果 n 是偶数，那么所有的数都能被消除，剩余 0 个。
// 如果 n 是奇数，那么任何条件下都会剩余一个不能成对，此时会剩下 1 个。
// 由（1）、（2）、（3）知，关键在于 maxCnt 。

// 如果 2·maxCnt - n 不是正数，那么就会小于 0 ，正好对应情形（1）或（3），
// 所以可以取 answer = max(2·maxCnt - n, 0 或 1) ，n 为偶数取 0，n 为奇数取 1 。

// 方法一：O(n) 时间
class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int maxCnt = 0, n = nums.size();
        for (auto x : nums)
            maxCnt = max(++cnt[x], maxCnt);
        return max(2 * maxCnt - n, n & 1);
    }
};

// @lc code=start
// 方法二：O(logn)
// 由上面的讨论可知，只有情形（2）（即 maxCnt·2 > n）时，答案才为 2·maxCnt - n ，否则为 0 或 1 ，
// 题目已知 nums 是非递减的，所以此时的众数一定会横跨中点，换言之，中点一定是众数。
// 已知了出现次数最多的数的值，那么可以用二分查找找出其最左和最右的位置，就可以计数。
// 这就是力扣题「34. 在排序数组中查找元素的第一个和最后一个位置」。
class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        int n = nums.size(), x = nums[n / 2];
        // lower_bound：第一个 i ≤ x 的 i
        // upper_bound：第一个 i > x 的 i
        // 简记：左闭右开区间
        int maxCnt = ranges::upper_bound(nums, x) - ranges::lower_bound(nums, x);
        return max(2 * maxCnt - n, n & 1);
    }
};
// @lc code=end
