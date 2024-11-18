/*
 * @Author: your name
 * @Date: 2021-08-28 10:28:12
 * @LastEditTime: 2021-08-28 10:42:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\797.所有可能的路径.cc
 */

/**
 * 给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）

二维数组的第 i 个数组中的单元都表示有向图中 i 号节点所能到达的下一些节点，空就是没有下一个结点了。

译者注：有向图是有方向的，即规定了 a→b 你就不能从 b→a 。

 

示例 1：



输入：graph = [[1,2],[3],[3],[]]
输出：[[0,1,3],[0,2,3]]
解释：有两条路径 0 -> 1 -> 3 和 0 -> 2 -> 3
示例 2：



输入：graph = [[4,3,1],[3,2,4],[3],[4],[]]
输出：[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
示例 3：

输入：graph = [[1],[]]
输出：[[0,1]]
示例 4：

输入：graph = [[1,2,3],[2],[3],[]]
输出：[[0,1,2,3],[0,2,3],[0,3]]
示例 5：

输入：graph = [[1,3],[2],[3],[]]
输出：[[0,1,2,3],[0,3]]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/all-paths-from-source-to-target
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 */

// dfs
// 时间复杂度：O(n*2^n)，最坏情况下，每个节点都可以与比它大的节点相连，把中间节点看作1~n-2的数列，
// 中间节点可选也可不选，那么总的路径数就是2^(n-2)，每条路径的长度为O(n)，其实也可以理解为n个2^(n-2)累加。
// 空间复杂度：O(n)，因为path的长度为n。其实主要是栈的开销，返回值ans不计入空间开销。
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> ans;
        vector<int> path;
        path.push_back(0);
        dfs(ans, graph, path, 0);
        return ans;
    }

    void dfs(vector<vector<int>>& ans, vector<vector<int>>& graph, vector<int>& path, int start) {
        if(start + 1 == graph.size()) {
            ans.push_back(path);
            return;
        }
        for(int next : graph[start]) {
            path.push_back(next);
            dfs(ans, graph, path, next);
            path.pop_back();
        }
    }
};