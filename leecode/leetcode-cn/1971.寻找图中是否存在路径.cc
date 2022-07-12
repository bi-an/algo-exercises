// dfs
class Solution
{
  vector<bool> visited;

 public:
  bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
  {
    // 邻接表使用 vector<vector<int>> 存储也一样。
    map<int, set<int>> adj;
    for (auto &e : edges)
    {
      adj[e[0]].insert(e[1]);
      adj[e[1]].insert(e[0]);
    }
    visited.resize(n);
    for (int i = 0; i < visited.size(); ++i)
    {
      visited[i] = false;
    }
    return dfs(adj, source, destination);
  }

  bool dfs(map<int, set<int>> &adj, int start, int end)
  {
    if (visited[start] && start != end)
      return false;
    if (start == end)
      return true;

    visited[start] = true;
    bool hasPath = false;
    for (auto it = adj[start].begin(); it != adj[start].end(); ++it)
    {
      if (visited[*it])
        continue;
      hasPath = hasPath || dfs(adj, *it, end);
    }
    return hasPath;
  }
};

// 并查集
// TODO