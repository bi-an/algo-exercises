/*
 * @Author: your name
 * @Date: 2022-03-26 17:19:48
 * @LastEditTime: 2022-03-26 17:19:48
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\2039.网络空闲的时刻.cc
 */

// 1. 任意一个节点到达 0 节点的最近距离（定义为“距离”）
// 2. 经过两倍距离的时间，节点不再发送信息，总共发送了 (两倍距离/patience) 的信息
// 3. 等待最后一条信息：发送时间点 = (两倍距离-1) / patience * patience
//                      接收时间点 = 发送时间点 + 两倍距离 => answer
// 求距离：bfs
class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        int n = patience.size();
        vector<vector<int>> adjs(n);
        vector<int> distances(n, INT_MAX);
        vector<bool> visited(n, false);
        for (vector<int>& e : edges) {
            int u = e[0], v = e[1];
            adjs[u].push_back(v);
            adjs[v].push_back(u);
        }
        queue<int> Q;
        Q.push(0);
        int d = 0;
        while (!Q.empty()) {
            int width = Q.size();
            for (int i = 0; i < width; ++i) {
                int u = Q.front();
                Q.pop();
                for (int v : adjs[u]) {
                    if (!visited[v])
                        Q.push(v);
                }
                if (!visited[u])
                    distances[u] = d; //min(d, distances[u]); // Attention
                visited[u] = true;
            }
            ++d;
        }
        
        // for(int i = 0; i < n; ++i) {
        //     cout << distances[i] << " ";
        // }
        
        int ans = 0;
        for(int i = 1; i < n; i++) {
            int cur = (2 * distances[i] - 1) / patience[i] * patience[i] + 2 * distances[i] + 1;
            if (cur > ans)
                ans = cur;
        }
        return ans;
    }
};