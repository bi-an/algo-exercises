class Solution {
  // 由于color可能与grid中的颜色相同，直接对grid修改会混淆原先的颜色矩阵
  // 官方题解使用一个vector<pair<int,int>>只存储边界，之后再对grid进行一次性修改，稍稍减少了内存空间。
  // 并且官方题解使用direction数组，将代码写得更简洁一些
  vector<vector<int>> ans;

 public:
  vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col,
                                  int color) {
    ans = grid;
    vector<vector<bool>> visited(grid.size(),
                                 vector<bool>(grid[0].size(), false));
    dfs(grid, visited, color, grid[row][col], row, col);
    return ans;
  }

  void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int color,
           int raw, int x, int y) {
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() ||
        grid[x][y] != raw || visited[x][y])
      return;

    visited[x][y] = true;
    if (x == 0 || x + 1 == grid.size() || y == 0 || y + 1 == grid[0].size() ||
        grid[x + 1][y] != raw || grid[x - 1][y] != raw ||
        grid[x][y + 1] != raw || grid[x][y - 1] != raw)
      ans[x][y] = color;

    dfs(grid, visited, color, raw, x + 1, y);
    dfs(grid, visited, color, raw, x - 1, y);
    dfs(grid, visited, color, raw, x, y + 1);
    dfs(grid, visited, color, raw, x, y - 1);
  }
};

// 参考官方题解
class Solution {
  vector<pair<int, int>> borders;  // 边界点的坐标
  int m, n;
  static constexpr int direc[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

 public:
  vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col,
                                  int color) {
    m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    dfs(grid, row, col, visited, grid[row][col]);
    for (auto& [x, y] : borders) {
      grid[x][y] = color;
    }
    return grid;
  }

  void dfs(vector<vector<int>>& grid, int x, int y,
           vector<vector<bool>>& visited, int originalColor) {
    bool isBorder = false;
    // 遍历originalColor的连通分量
    for (int i = 0; i < 4; i++) {
      int nx = x + direc[i][0], ny = y + direc[i][1];
      // 只有四个方向上都有邻点，且这些邻点与其颜色都相同，该点才不是边界。
      if (!(nx >= 0 && nx < m && ny >= 0 && ny < n &&
            grid[nx][ny] == originalColor)) {
        // (x,y)是边界点。同时也意味着(nx,ny)与(x,y)互为边界，
        // 所以没有必要遍历(nx,ny)了，我们要遍历的是与originalColor的连通分量，
        // 而(nx,ny)要么超出grid范围，要么颜色与originalColor不同。
        isBorder = true;  // 标记当前点(x,y)为边界点
      } else if (!visited[nx][ny]) {
        visited[nx][ny] = true;
        dfs(grid, nx, ny, visited, originalColor);
      }
    }
    if (isBorder) borders.push_back({x, y});
  }
};