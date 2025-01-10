/*
 * @lc app=leetcode.cn id=2226 lang=cpp
 *
 * [2226] 每个小孩最多能分到多少糖果
 */

// @lc code=start
class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        auto check = [&](int m) {
            if (m == 0)
                return true;
            long long cnt = 0;
            for (int x : candies) {
                cnt += x / m;
                if (cnt >= k)
                    return true;
            }
            return false;
        };

        // 开区间二分查找
        int left = -1, right = accumulate(candies.begin(), candies.end(), 0LL) / k + 1;
        // right = ranges::max(candies) + 1;
        while (left + 1 < right) {
            int mid = left + ((right - left) >> 1);
            (check(mid) ? left : right) = mid;
        }

        return left;
    }
};
// @lc code=end
