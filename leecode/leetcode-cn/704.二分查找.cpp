/*
 * @lc app=leetcode.cn id=704 lang=cpp
 *
 * [704] 二分查找
 */

class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto i = ranges::lower_bound(nums, target);
        if (i == nums.end() || *i != target)
            return -1;
        return i - nums.begin();
    }
};


namespace solution_2 {

// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;
        while (left <=right) {
            int mid = left + (right - left) / 2;
            // 题目已知所有元素都不等，否则这里会随机返回一个等于 target 的位置
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return - 1;
    }
};
// @lc code=end

}  // namespace solution_2
