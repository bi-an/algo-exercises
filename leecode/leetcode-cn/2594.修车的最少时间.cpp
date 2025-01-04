/*
 * @lc app=leetcode.cn id=2594 lang=cpp
 *
 * [2594] 修车的最少时间
 */

// @lc code=start
class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        int n = ranks.size();
        auto [mi, ma] = ranges::minmax(ranks);
        // 最多和最少时间分别在所有人都是最低效率或最高效率时
        // 此时所有人所修的车辆数相同，都是 x
        long long x = (cars + n - 1) / n;  // 必须向上取整
        x *= x;
        long long left = mi * x, right = ma * x;

        auto check = [&](long long t) {
            long long remain = cars;
            // 该 check 函数需要频繁调用，所以可以进一步优化：
            // 因为相同 rank 工人能修的车辆数相同，可以用哈希表统计 rank 的出现频次，
            // 然后遍历哈希表（而不是 ranks），可以少循环几次
            // 题解：https://leetcode.cn/problems/minimum-time-to-repair-cars/solutions/2177199/er-fen-da-an-pythonjavacgo-by-endlessche-keqf/
            for (int r : ranks) {
                remain -= (int)sqrt(t / r);
                if (remain <= 0)
                    return true;
            }
            return false;
        };

        while (left <= right) {
            long long m = left + (right - left) / 2;
            if (check(m))
                right = m - 1;
            else
                left = m + 1;
        }

        return left;
    }
};
// @lc code=end
