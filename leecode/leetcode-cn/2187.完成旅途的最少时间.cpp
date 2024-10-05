/*
 * @lc app=leetcode.cn id=2187 lang=cpp
 *
 * [2187] 完成旅途的最少时间
 */

// @lc code=start
// 二分查找
// 这题和 「3296.移山所需的最少秒数」 一样，但是测试集的数值范围扩大了，
// 所以最小堆解法无法通过测试，只能使用二分解法
class Solution {
   public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        int n = time.size();
        auto mx = ranges::max(time);

        auto check = [&](long long m) -> bool {
            long long trips = 0;
            for (int t : time) {
                trips += m / t;
            }
            return trips >= totalTrips;
        };

        // long long l = static_cast<long long>(mn_mx.min) * totalTrips / n, r = static_cast<long long>(mn_mx.max) * totalTrips / n;
        // 上面这种边界找得不对，不等式的取整除法不能直接改成乘法，会丢失一些信息
        long long l = 1, r = static_cast<long long>(mx) * totalTrips;
        // 直接将最慢的公交完成所有旅途的时间作为右边界

        while (l < r) {
            long long m = (l + r) / 2;
            if (check(m))
                r = m;
            else
                l = m + 1;
            // cout << m << " " << check(m) << endl;
        }

        return l;
    }
};
// @lc code=end
