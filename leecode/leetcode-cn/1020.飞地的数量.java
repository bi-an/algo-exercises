// 方法一：深度优先遍历
// 时间复杂度：O(n^2)
// 空间复杂度：O(n^2)，visited和递归空间
class Solution {
    private int[][] dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    private boolean[][] visited = null;
    private int m = 0;
    private int n = 0;

    public int numEnclaves(int[][] grid) {
        m = grid.length;
        n = grid[0].length;
        visited = new boolean[m][n];

        // 从边界的陆地开始遍历
        for (int i = 0; i < m; i++) {
            dfs(grid, i, 0);
            dfs(grid, i, n - 1);
        }
        for (int j = 1; j < n - 1; j++) {
            dfs(grid, 0, j);
            dfs(grid, m - 1, j);
        }

        // 如果某点为陆地，并且没有被访问过，说明为飞地
        int enclaves = 0;
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (grid[i][j] == 1 && !visited[i][j])
                    enclaves++;
            }
        }
        return enclaves;
    }

    public void dfs(int[][] grid, int row, int col) {
        if (row < 0 || row >= m || col < 0 || col >= n || visited[row][col] || grid[row][col] == 0)
            return;
        visited[row][col] = true;
        for (int i = 0; i < 4; i++)
            dfs(grid, row + dirs[i][0], col + dirs[i][1]);
    }
}

// 方法二：广度优先遍历
// TODO


// 方法三：并茶集
// TODO