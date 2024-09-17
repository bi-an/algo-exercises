/*
 * @lc app=leetcode.cn id=815 lang=cpp
 *
 * [815] 公交路线
 */

// @lc code=start
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target)
            return 0;
        
        int n = routes.size();
        vector<vector<bool>> edge(n, vector<bool>(n)); // 邻接矩阵，每条线路是一个顶点
        unordered_map<int, vector<int>> rec; // 记录经过车站的线路（即图的边）
        for (int i = 0; i < n; ++i) { // 线路标号
            for (int site : routes[i]) {
                for (int j : rec[site]) { // 对已有线路添加邻边
                    edge[i][j] = edge[j][i] = true;
                }
                rec[site].push_back(i);
            }
        }

        // 广度优先搜索，记录所有线路到达初始线路的距离
        // BFS适用于最短距离的问题
        vector<int> dis(n, -1); // 到起始线路的距离
        queue<int> que;
        for (int bus : rec[source]) { // 遍历所有经过source车站的线路
                                      // bus在此处应该翻译成线路
            dis[bus] = 1; // 即使在同一条线路上，只要source≠target，也应该乘坐一次公交
                          // 注意到，最开始时我们已经处理过source==target的情况
                          // 虽然这里我们会将source本身距离起始线路的距离也记作1，不会影响结果
            que.push(bus);
        }
        while (!que.empty()) {
            int x = que.front(); // 线路
            que.pop();
            for (int y = 0; y < n; ++y) {
                if (edge[x][y] && dis[y] == -1) { // 不得重复访问，以保证距离最短
                                                  // 并且如果重复访问，会导致循环无法退出
                    dis[y] = dis[x] + 1;
                    que.push(y); // 记录图的下一层
                }
            }
        }

        int ret = INT_MAX;
        for (int bus : rec[target]) {
            if (dis[bus] != -1) {
                ret = min(dis[bus], ret);
            }
        }

        return ret == INT_MAX ? -1 : ret;
    }
};
// @lc code=end
