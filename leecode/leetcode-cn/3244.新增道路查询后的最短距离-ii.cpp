/*
 * @lc app=leetcode.cn id=3244 lang=cpp
 *
 * [3244] 新增道路查询后的最短距离 II
 */

// @lc code=start
//
// 题目已知：所有查询中不会存在两个查询都满足 queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1]。
// 这表示路径不可能交叉。可以使用“贪心”。
// 这也是并查集的条件。本题本意是为了考察并查集，所以将难度标记为“困难”。
// 实际上，不需要使用并查集也可以做出来，实际难度应该为“中等”。
// 由于路径不可能交叉，且路径不可能反向（即总是由小编号城市指向大编号城市，因为题目标明为“单向”道路），
// 所以如果添加了一条新路径，我们就可以将其覆盖的中间节点全部删掉（或者说标记为“已删除”）。
// 时间复杂度：O(n+q)
// 空间复杂度：O(n)，返回值不计入。
class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> next(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            next[i] = i + 1;
        }

        int m = queries.size(), cnt = n - 1;  // cnt 表示从 0 到 n-1 的最短路径长度
        vector<int> ans(m);
        for (int qi = 0; qi < m; ++qi) {
            int l = queries[qi][0], r = queries[qi][1];
            // 将新路径覆盖的所有中间节点都标记为“已删除”
            int j = next[l];
            // 题目已知路径不重复，所以最坏情况下，路径总数小于 2*(n-1)，
            // 所以两重循环的时间复杂度最大为 O(2n).
            // 所以总时间复杂度为 O(2n+q) --> O(n+q)，其中 q 是第一重循环中除去内重循环的其他计算步骤。
            while (j < r) {
                int tmp = next[j];
                next[j] = r;  // 标记为“已删除”
                // 每删除一个中间节点，cnt 就减少 1
                --cnt;
                j = tmp;
            }
            // 如果新路径被已有路径包含，则不需要处理
            if (next[l] < r)
                next[l] = r;
            ans[qi] = cnt;
        }

        return ans;
    }
};
// @lc code=end

// TODO
// 并查集
// https://algo.itcharge.cn/07.Tree/05.Union-Find/
