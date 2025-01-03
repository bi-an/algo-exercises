/*
 * @lc app=leetcode.cn id=875 lang=cpp
 *
 * [875] 爱吃香蕉的珂珂
 */

// @lc code=start
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = ranges::max(piles);

        auto check = [&](int k) {
            int hours = h;
            for (int x : piles) {
                // 时间复杂度 piles[i] * piles.length ，会超时
                // while (x > 0) {
                //     x -= k;
                //     if (--hours < 0)
                //         return false;
                // }
                hours -= (x + k - 1) / k;
                if (hours < 0)
                    return false;
            }
            return true;
        };

        while (left <= right) {
            int m = left + (right - left) / 2;
            if (check(m))
                right = m - 1;
            else
                left = m + 1;
        }

        return left;
    }
};
// @lc code=end
