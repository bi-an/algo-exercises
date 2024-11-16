/*
 * @lc app=leetcode.cn id=80 lang=cpp
 *
 * [80] 删除有序数组中的重复项 II
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)  // 或 n <= 2
            return n;
        int r = 2, w = 2;  // 读写指针
        while (r < n) {
            // 这是有序数组，如果 nums[w-2] 与 nums[r] 相等，说明 nums{w-2,w-1,...,r} 都相等；
            // 如果不等，那么最多有 nums{w-2,w-1,...,r-1} 两两相等，
            // 又由于我们r和w出发时相等，所以中间的情况都被处理掉了，所以最多有 nums{w-2,w-1} 相等。
            if (nums[w - 2] != nums[r])
                nums[w++] = nums[r];
            ++r;
        }
        return w;
    }
};
// @lc code=end
