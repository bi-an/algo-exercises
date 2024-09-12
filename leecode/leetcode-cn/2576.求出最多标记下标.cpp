/*
 * @lc app=leetcode.cn id=2576 lang=cpp
 *
 * [2576] 求出最多标记下标
 */

// @lc code=start
class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        // 先排序
        // 时间复杂度O(nlogn)
        // 空间复杂度O(logn)，排序需要的栈空间为O(logn)
        std::sort(nums.begin(), nums.end());
        // 需要注意的是，我们需要让最左边的一半和最右边的一半匹配
        // 否则直接使用双指针会有重复：例如[1,2,4]，会计入(1,2)和(2,4)，显然2已经被标记一次了
        // 双指针的时间复杂度O(n)；空间复杂度O(1)
        for (int i = 0, j = (n + 1) / 2; i < n && j < n; ++i, ++j) {
            while(j < n && nums[i] * 2 > nums[j]) {
                ++j;
            }
            if (j >= n)
                break;
            ans += 2;
        }
        return ans;
    }
};
// @lc code=end

