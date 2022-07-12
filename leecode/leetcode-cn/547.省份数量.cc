// dfs
class Solution {
public:
    void dfs(vector<vector<int>>& isConnected, vector<int>& visited, int cities, int i) {
        for (int j = 0; j < cities; j++) {
            if (isConnected[i][j] == 1 && !visited[j]) {
                visited[j] = 1;
                dfs(isConnected, visited, cities, j);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int cities = isConnected.size();
        vector<int> visited(cities);
        int provinces = 0;
        for (int i = 0; i < cities; i++) {
            if (!visited[i]) {
                dfs(isConnected, visited, cities, i);
                provinces++;
            }
        }
        return provinces;
    }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode.cn/problems/number-of-provinces/solution/sheng-fen-shu-liang-by-leetcode-solution-eyk0/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

// 并查集
// https://leetcode.cn/problems/number-of-provinces/solution/python-duo-tu-xiang-jie-bing-cha-ji-by-m-vjdr/
