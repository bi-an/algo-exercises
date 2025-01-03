/*
 * @lc app=leetcode.cn id=1011 lang=cpp
 *
 * [1011] 在 D 天内送达包裹的能力
 */

// @lc code=start
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = ranges::max(weights);
        int right = accumulate(weights.begin(), weights.end(), 0);

        auto check = [&](int m) {
            int d = 1;
            long long sum = 0;
            for (int w : weights) {
                if (sum + w > m) {
                    d++;
                    sum = w;
                } else {
                    sum += w;
                }
            }
            return d <= days;
        };

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid))
                right = mid - 1;
            else
                left = mid + 1;
        }

        return left;
    }
};
// @lc code=end
