/*
 * @lc app=leetcode.cn id=3048 lang=cpp
 *
 * [3048] 标记所有下标的最早秒数 I
 */

// @lc code=start
// 题解：https://leetcode.cn/problems/earliest-second-to-mark-indices-i/solutions/2653101/er-fen-da-an-pythonjavacgo-by-endlessche-or61/
// 阅读理解：将 nums 想象成 n 门课程，标记 nums[i] 视作第 i 门课安排考试，
// 一共有 m = changeIndices.lenghth 天，每一天可以用来复习、考试或玩耍。
// 除了“考试日”都可以用于“复习”（暂不管是复习哪一门），我们用一个变量 cnt 来统计当前可用的“复习日”天数。
// 任务：修完复习天数、并完成考试的最少天数。
// 贪心：在 [1, mx] 天中，lastDay 最晚的课程最后复习。可以用二分法在 [1, mx] 中寻找。
// 时间复杂度：O(mlogm)
// 空间复杂度：O(n) ，记录每门课的 lastDay .
class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size(), m = changeIndices.size();

        vector<int> last_d(n);  // 最后考试日
        auto check = [&](int mx) {
            ranges::fill(last_d, -1);
            // 标记 lastDay ，但是不能超过 mx
            for (int d = 0; d < mx; ++d)
                last_d[changeIndices[d] - 1] = d;  // changeIndices 从 1 开始计数

            if (ranges::find(last_d, -1) != last_d.end())
                return false;  // 有课程不能安排考试

            int cnt = 0;  // 如果不是“考试日”，当前可用的“复习日”天数
            for (int d = 0; d < mx; ++d) {
                int i = changeIndices[d] - 1;  // 要改变的课程的下标
                if (d == last_d[i]) {          // 考试日
                    if (cnt < nums[i])
                        return false;  // 无法在 lastDay 之前完成复习

                    cnt -= nums[i];  // 从“复习日”中拿出 nums[i] 用于复习这门课
                } else {
                    ++cnt;  // 复习日
                }
            }
            return true;
        };

        // left：每门课都要考试一次（占一天）
        // right：最多有 m 天
        int left = n, right = m;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid))
                right = mid - 1;
            else
                left = mid + 1;  // check() 可能一直返回 false
        }

        return left > m ? -1 : left;
    }
};
// @lc code=end
