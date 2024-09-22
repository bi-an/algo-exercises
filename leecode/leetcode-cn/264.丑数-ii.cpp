/*
 * @lc app=leetcode.cn id=264 lang=cpp
 *
 * [264] 丑数 II
 */

// @lc code=start

// 动态规划
// 时间复杂度：O(3n)→O(n)
// 空间复杂度：O(n)
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n + 1);  // 依次保存 n 个丑数
        dp[1] = 1;
        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; ++i) {
            int v2 = 2 * dp[p2];
            int v3 = 3 * dp[p3];
            int v5 = 5 * dp[p5];
            int m = Min(v2, v3, v5);
            dp[i] = m;
            if (m == v2)
                ++p2;  // 移动到指向更新后的丑数
            if (m == v3)
                ++p3;
            if (m == v5)
                ++p5;
        }
        return dp[n];
    }

    int Min(int a, int b, int c) {
        return min(min(a, b), c);
    }
};

namespace solution_2 {
// 最小堆
// 时间复杂度：O(nlogn)
// 空间复杂度：O(n)
class Solution {
public:
    int nthUglyNumber(int n) {
        int ugly = 0;
        // 最小堆
        // 因为堆内元素个数可能比 n 多许多，为了防止越界，使用 long
        priority_queue<long, vector<long>, greater<long>> heap;
        // 去重：在加入堆之前，先用哈希表判断是否已经存在
        unordered_set<long> seen;

        heap.push(1L);
        seen.insert(1L);

        vector<long> factors = {2, 3, 5};
        for (int i = 0; i < n; ++i) {
            long cur = heap.top();
            heap.pop();
            ugly = (int)cur;
            for (auto factor : factors) {
                long next = cur * factor;
                if (!seen.count(next)) {
                    seen.insert(next);
                    heap.push(next);
                }
            }
        }
        return ugly;
    }
};
}  // namespace solution_2

// @lc code=end
