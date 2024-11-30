/*
 * @lc app=leetcode.cn id=1052 lang=cpp
 *
 * [1052] 爱生气的书店老板
 */

// @lc code=start
// 定长滑动窗口
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        long long tot = 0;           // 满意的客户数
        vector<int> unsatisfied(n);  // 不满意的客户数；这个空间复杂度可以去掉
        for (int i = 0; i < n; ++i) {
            if (!grumpy[i])
                tot += customers[i];
            else
                unsatisfied[i] = customers[i];
        }
        long long cnt = 0, max_cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += unsatisfied[i];
            // 窗口长度不足 minutes
            if (i < minutes - 1)
                continue;
            max_cnt = max(cnt, max_cnt);
            // 删除窗口头，准备下一次
            cnt -= unsatisfied[i - minutes + 1];
        }
        return tot + max_cnt;
    }
};
// @lc code=end

// 将法一改成空间 O(1)
namespace solution_2 {
// 定长滑动窗口
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        // s0 表示客户满意数；s1 表示窗口 minutes 内不满意数
        long long s0 = 0, s1 = 0, max_s1 = 0;
        for (int i = 0; i < n; ++i) {
            if (grumpy[i])
                s1 += customers[i];
            else
                s0 += customers[i];
            // 窗口长度不足 minutes
            if (i < minutes - 1)
                continue;
            max_s1 = max(s1, max_s1);
            // 删除窗口头，准备下一次
            s1 -= grumpy[i - minutes + 1] ? customers[i - minutes + 1] : 0;
        }
        return s0 + max_s1;
    }
};

}  // namespace solution_2
