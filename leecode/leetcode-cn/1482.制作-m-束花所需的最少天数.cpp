/*
 * @lc app=leetcode.cn id=1482 lang=cpp
 *
 * [1482] 制作 m 束花所需的最少天数
 */

// @lc code=start
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if (n < (long long)m * k)  // 总花朵数不足 m 束花
            return -1;

        // 时间复杂度 O(n)
        auto check = [&](int d) {
            int bouquets = m;  // 剩余待制作的花束数
            int flowers = k;   // 当前花束还需的花朵数
            for (int x : bloomDay) {
                if (x <= d) {                 // 已经盛开
                    if (--flowers == 0) {     // 当前花束完成
                        if (--bouquets == 0)  // 所有花束完成
                            return true;
                        flowers = k;  // 准备制作下一束
                    }
                } else {
                    flowers = k;  // 当前花束作废
                }
            }
            return false;
        };

        // 所有花都在同一天盛开时的最值：都开得最早或最晚
        auto [left, right] = ranges::minmax(bloomDay);
        while (left <= right) {
            int m = left + ((right - left) >> 1);
            if (check(m))
                right = m - 1;
            else
                left = m + 1;
        }

        return left;
    }
};
// @lc code=end
