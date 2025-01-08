/*
 * @lc app=leetcode.cn id=3049 lang=cpp
 *
 * [3049] 标记所有下标的最早秒数 II
 */

// @lc code=start
// 二分查找 + 反悔贪心（即先贪心，但是可能反悔）
class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size(), m = changeIndices.size();
        long long total = n + accumulate(nums.begin(), nums.end(), 0LL);  // 最多需要的秒数

        // “快速置零”有时序约束：先快速置零，才能进行标记；并且每时刻只能标记一个。
        // 所以可能出现：（1）已经快速置零了，但是没有足够时间标记；
        // （2）由贪心可知，我们尽可能先快速置零，但可能我们一直在快速置零，导致没有足够时间进行标记。
        // 此时应该反悔，放弃一些快速置零操作，让其通过减一归零；留下的快速置零的，则及时进行标记。
        // 这是因为减一没有时序约束，而快速置零有。

        // 能够快速置零的最早秒刻
        vector<int> first_t(n, -1);
        for (int t = m - 1; t >= 0; --t) {
            int i = changeIndices[t] - 1;
            if (nums[i] > 1)  // 减一和快速置零效果相当，但是快速置零有时序约束，不如直接减一
                first_t[i] = t;
        }

        auto check = [&](int seconds) {
            // 贪心：为了快速收敛，且快速置零有时序约束，尽可能让快速置零先处理，最后剩余的再减一
            // 所以把可以减一的秒刻先预留
            int cnt = 0;             // 预留的秒刻数
            long long need = total;  // 所需秒数

            priority_queue<int, vector<int>, greater<>> pq;  // 最小堆，暂存，用于反悔

            // 为了满足时序约束，我们按时间逆序遍历
            for (int t = seconds - 1; t >= 0; --t) {
                int i = changeIndices[t] - 1;
                int v = nums[i];

                if (t != first_t[i]) {
                    cnt++;  // 预留该秒刻：可能用于任何操作
                    continue;
                }

                if (cnt == 0) {  // 无法标记：当前秒刻用于快速置零，但是需要预留的秒刻用于标记
                    if (pq.empty() || v <= pq.top()) {
                        // 没得反悔或没必要反悔，则预留当前秒刻
                        cnt++;
                        continue;
                    }
                    // 反悔：将已经快速置零的最小值（最差值）拿出来，改成处理更快收敛的（更优值）
                    need += pq.top() + 1;
                    pq.pop();
                    cnt += 2;  // 快速置零和标记各占 1 秒
                }
                // 此时 t 必然等于 first_t[i]
                need -= v + 1;
                cnt--;       // 当前秒刻用于快速置零；但是额外需要 1 秒用于标记
                pq.push(v);  // 暂存，可能被反悔
            }

            // 剩余的秒数全部用于减一和标记
            return cnt >= need;
        };

        int left = n, right = m;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid))
                right = mid - 1;  // right + 1 即 mid ，总是合法的
            else
                left = mid + 1;
        }

        return right + 1 > m ? -1 : right + 1;
    }
};
// @lc code=end
