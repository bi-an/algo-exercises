// 递归
// 这道题其实不难
class Solution {
    int n;
    vector<bool> l_diag; // 左对角线 "/" 是否有皇后
    vector<bool> r_diag; // 右对角线 "\" 是否有皇后
    vector<bool> col; // col[y] 表示第 y 列是否有皇后
    vector<vector<string>> ans;
    vector<string> matrix;
public:
    vector<vector<string>> solveNQueens(int n) {
        l_diag.resize(2 * n - 1);
        r_diag.resize(2 * n - 1);
        col = vector<bool>(n);
        matrix = vector<string>(n, string(n, '.'));
        this->n = n;

        recur(0);
        return ans;
    }

    void recur(int x) {
        if (x == n) {
            ans.push_back(matrix);
            return;
        }
        for (int y = 0; y < n; ++y) {
            if (l_diag[x + y] || r_diag[x - y + n - 1] || col[y])
                continue;

            matrix[x][y] = 'Q';
            l_diag[x + y] = true;
            r_diag[x - y + n - 1] = true;
            col[y] = true;
            recur(x + 1);
            matrix[x][y] = '.';
            l_diag[x + y] = false;
            r_diag[x - y + n - 1] = false;
            col[y] = false;
        }
    }
};