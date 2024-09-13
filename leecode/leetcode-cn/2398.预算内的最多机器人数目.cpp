/*
 * @lc app=leetcode.cn id=2398 lang=cpp
 *
 * [2398] 预算内的最多机器人数目
 */

// @lc code=start
// 这一题的描述有点问题，不论是中文还是英文。
// 其中的“consecutive robots”表示下标连续，也就是子区间，而不是子序列。
class Solution {
public:
    int maximumRobots(vector<int> &chargeTimes, vector<int> &runningCosts, long long budget) {
        int n = chargeTimes.size();
        long long sum = 0;
        int ans = 0;
        deque<int> Q;  // 单调递减队列，front最大，back最小
        // 快慢指针的技巧：先遍历快指针，然后不断让慢指针接近快指针
        // 反则不容易处理边界，如果我们针对每个慢指针去移动快指针，需要处理快指针到达右边界的特殊情况
        // i是快指针，j是慢指针
        for (int i = 0, j = 0; i < n; ++i) {
            while (!Q.empty() && chargeTimes[Q.back()] <= chargeTimes[i]) {
                Q.pop_back();
            }
            Q.push_back(i);
            sum += runningCosts[i];
            // 缩小窗口直至长度为0或满足条件；i是右边界，j是左边界
            while (j <= i && sum * (i - j + 1) + chargeTimes[Q.front()] > budget) {
                if (!Q.empty() && Q.front() == j) {
                    Q.pop_front();
                }
                sum -= runningCosts[j++];
            }
            // i允许超过j，此时表示窗口长度为0
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
// @lc code=end
