// 拓扑排序
// 详见官方题解
class Solution
{
  vector<int> visited;
  // 邻接表存储有向图
  vector<vector<int>> edges;
  vector<int> result;
  bool valid = true;

 public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
  {
    edges.resize(numCourses);
    visited.resize(numCourses);
    for (const vector<int> &e : prerequisites)
    {
      edges[e[1]].push_back(e[0]);
    }
    for (int i = 0; i < numCourses; ++i)
    {
      if (visited[i] == 0)
      {
        dfs(i);
      }
    }
    if (valid)
    {
      std::reverse(result.begin(), result.end());
      return result;
    }
    else
    {
      return {};
    }
  }

  void dfs(int node)
  {
    visited[node] = 1;
    for (const auto &v : edges[node])
    {
      if (!valid)
        return;
      if (visited[v] == 1)
      {
        // 遇到了之前的节点，说明存在环
        valid = false;
        return;
      }
      if (visited[v] == 0)
      {
        dfs(v);
      }
    }
    visited[node] = 2;
    result.push_back(node);
  }
};