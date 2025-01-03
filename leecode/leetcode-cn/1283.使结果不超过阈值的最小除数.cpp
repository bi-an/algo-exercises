/*
 * @lc app=leetcode.cn id=1283 lang=cpp
 *
 * [1283] 使结果不超过阈值的最小除数
 */

// @lc code=start
// 二分查找
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        // 经测试，以下上下界可以通过测试，但是没有经过证明
        // long long left = 0, right = 0;
        // for (int x : nums) {
        //     left += x / threshold;
        //     right += ceil((double)x / threshold);
        // }
        // left = left == 0 ? 1 : left;
        // right = 3 * right;

        // TODO: 优化左右边界
        // right: 由于除法向上取整，被除数大于 max(nums) 和 max(nums) 得到的商是相同的
        int left = 1, right = ranges::max(nums);

        auto check = [&](int m) {
            long long sum = 0;
            for (int x : nums) {
                sum += ceil((double)x / m);
                if (sum > threshold)
                    return false;  // m 太小了
            }
            return true;
        };

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (mid == 0)
                return 1;
            if (check(mid))
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
};
// @lc code=end
