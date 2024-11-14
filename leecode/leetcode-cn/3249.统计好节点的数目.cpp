/*
 * @lc app=leetcode.cn id=3249 lang=cpp
 *
 * [3249] 统计好节点的数目
 */

// @lc code=start
class Solution {
public:
    int countGoodNodes(vector<vector<int>>& edges) {
        int n = edges.size() + 1;  // 树的顶点数等于边数加1
        // 邻接表
        vector<vector<int>> g(n);
        for (vector<int>& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int ans = 0;
        auto dfs = [&](auto&& dfs, int x, int parent) -> int {
            int size = 1, sz0 = 0;
            bool ok = true;
            for (auto y : g[x]) {
                if (y == parent)
                    continue;             // 不能递归到父节点
                int sz = dfs(dfs, y, x);  // 除了父，其他邻接顶点都是子
                if (sz0 == 0)
                    sz0 = sz;  // 第一棵子树的节点数
                else if (sz != sz0)
                    ok = false;  // 某孩子子树的节点数不等于第一个孩子子树的节点数
                                 // 注意不能break，因为要递归所有的节点
                size += sz;      // 本树的节点数
            }
            ans += ok;  // 计数好节点
            return size;
        };

        dfs(dfs, 0, -1);

        return ans;
    }
};
// @lc code=end
