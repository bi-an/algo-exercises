#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

/// 人为定义几个概念，以便区分：
///
/// grid：网格，表示容器（代填位置）
/// box / block：块，表示容器
/// matrix：矩阵，数阵
/// blockMatrix：块矩阵
/// gridMatrix：网格矩阵
class Solution
{
  bool rowBit[9][9]; // rowBit[i][digit] 表示第 i 行数字 digit 是否出现过
  bool colBit[9][9];  // 同上表示列
  bool matrixUsed[9]; // matrixUsed[i] 表示矩阵 grid[i] 是否使用过
  // matrixId 矩阵在 grid 中的位置编号为 0~8。
  // matrixIdPerBlock[boxId] 表示第 boxId 个 box 的填充矩阵的 matrixId。
  int matrixIdPerBlock[9];
  bool found; // 是否找到答案

  bool isConflict(int row, int col, int digit)
  {
    if (rowBit[row][digit] || colBit[col][digit])
      return true;
    return false;
  }

  // 将 matrix 填入 boxId 处
  // 仅仅标记是否访问过，不实际填充矩阵
  // boxId: 从左至右、从上至下编号粗线宫的待填区域为 0~8。
  void fillMatrix(const string &matrix, int boxId)
  {
    // i: matrixId
    for (int i = 0; i < 9; ++i)
    {
      int digit = matrix[i] - '1';
      rowBit[boxId / 3 * 3 + i / 3][digit] = true;
      colBit[boxId % 3 * 3 + i % 3][digit] = true;
    }
  }

  void unfillMatrix(const string &matrix, int boxId)
  {
    for (int i = 0; i < 9; ++i)
    {
      int digit = matrix[i] - '1';
      rowBit[boxId / 3 * 3 + i / 3][digit] = false;
      colBit[boxId % 3 * 3 + i % 3][digit] = false;
    }
  }

  /// <summary>
  /// 回溯 + 递归
  /// </summary>
  /// <param name="grid"></param>
  /// <param name="boxId"></param>
  void findOrder(const vector<string> &grid, int boxId)
  {
    if (boxId >= 9)
    {
      found = true;
      return;
    }
    for (int i = 0; i < 9; ++i)
    {
      if (matrixUsed[i])
        continue;
      bool needFill = true;
      const string &matrix = grid[i];
      for (int j = 0; j < 9; ++j)
      {
        int row = boxId / 3 * 3 + j / 3;
        int col = boxId % 3 * 3 + j % 3;
        if (isConflict(row, col, matrix[j] - '1'))
        {
          needFill = false;
          break;
        }
      }
      if (needFill)
      {
        fillMatrix(matrix, boxId);
        matrixUsed[i] = true;
        matrixIdPerBlock[boxId] = i;
        findOrder(grid, boxId + 1);
        if (found)
        {
          return;
        }
        unfillMatrix(matrix, boxId);
        matrixUsed[i] = false;
        matrixIdPerBlock[boxId] = i;
      }
    }
  }

 public:
  vector<vector<string>> getValidSudoku(vector<string> &grid)
  {
    memset(rowBit, 0, sizeof rowBit);
    memset(colBit, 0, sizeof colBit);
    memset(matrixUsed, 0, sizeof matrixUsed);
    memset(matrixIdPerBlock, 0, sizeof matrixIdPerBlock);
    found = false;

    findOrder(grid, 0);

    vector<vector<string>> ans;
    if (found)
    {
      for (int i = 0; i < 3; ++i)
      {
        vector<string> curr;
        for (int j = 0; j < 3; ++j)
        {
          curr.push_back(grid[matrixIdPerBlock[i * 3 + j]]);
        }
        ans.push_back(curr);
      }
    }
    return ans;
  }
};

/// TEST
int main()
{
  Solution solution;
  vector<string> grid
      = { "423791856", "284635179", "537419286", "912348567", "859426713",
          "761853924", "534672198", "678195342", "961287345" };
  auto ans = solution.getValidSudoku(grid);

  // 打印结果
  for (int i = 0; i < ans.size(); ++i)
  {
    for (int j = 0; j < ans[0].size(); ++j)
    {
      cout << ans[i][j] << ", ";
    }
    cout << endl;
  }

  cout << endl << endl;

  // 按 block / box 打印结果
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      int boxRow = i / 3;
      int boxCol = j / 3;
      int indexInBox = i % 3 * 3 + j % 3;
      cout << ans[boxRow][boxCol][indexInBox] << " ";
      if (j % 3 == 2)
        cout << " ";
    }
    cout << endl;
    if (i % 3 == 2)
      cout << endl;
  }

  return 0;
}