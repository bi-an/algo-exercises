// 面试题13：机器人的运动范围
// 题目：地上有一个m行n列的方格。一个机器人从坐标(0, 0)的格子开始移动，它
// 每一次可以向左、右、上、下移动一格，但不能进入行坐标和列坐标的数位之和
// 大于k的格子。例如，当k为18时，机器人能够进入方格(35, 37)，因为3+5+3+7=18。
// 但它不能进入方格(35, 38)，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

class Solution
{
 public:
  int movingCount(int threshold, int rows, int cols)
  {
    int sum = 0;
    bool *visited = new bool[rows * cols]();
    //memset(visited, 0, rows*cols);
    movingCountCore(threshold, rows, cols, 0, 0, visited, sum);
    delete[] visited;
    return sum;
  }

  int getDigitSum(int number)
  {
    int sum = 0;
    while (number)
    {
      sum += number % 10;
      number /= 10;
    }
    return sum;
  }

  bool check(int threshold, int row, int col)
  {
    if (getDigitSum(row) + getDigitSum(col) <= threshold)
      return true;
    else
      return false;
  }

  void movingCountCore(int threshold, int rows, int cols, int row, int col, bool *visited, int &sum)
  {
    if (visited[row * cols + col])
      return;

    //bool res=false;
    if (row >= 0 && row < rows && col >= 0 && col < cols && !visited[row * cols + col] && check(threshold, row, col))
    {
      visited[row * cols + col] = true;
      sum++;
      movingCountCore(threshold, rows, cols, row - 1, col, visited, sum);
      movingCountCore(threshold, rows, cols, row + 1, col, visited, sum);
      movingCountCore(threshold, rows, cols, row, col - 1, visited, sum);
      movingCountCore(threshold, rows, cols, row, col + 1, visited, sum);
    }
  }
};

//写法二： 改成传值的方式，比写法一慢一些
class Solution
{
 public:
  int movingCount(int threshold, int rows, int cols)
  {
    bool *visited = new bool[rows * cols]();
    //memset(visited, 0, rows*cols);
    int sum = movingCountCore(threshold, rows, cols, 0, 0, visited);
    delete[] visited;
    return sum;
  }

  int getDigitSum(int number)
  {
    int sum = 0;
    while (number)
    {
      sum += number % 10;
      number /= 10;
    }
    return sum;
  }

  bool check(int threshold, int row, int col)
  {
    if (getDigitSum(row) + getDigitSum(col) <= threshold)
      return true;
    else
      return false;
  }

  int movingCountCore(int threshold, int rows, int cols, int row, int col, bool *visited)
  {
    if (visited[row * cols + col])
      return 0;

    int cnt = 0;
    if (row >= 0 && row < rows && col >= 0 && col < cols && !visited[row * cols + col] && check(threshold, row, col))
    {
      visited[row * cols + col] = true;
      cnt = 1 + movingCountCore(threshold, rows, cols, row - 1, col, visited) //此处应该cnt++; 所以加了一个1
            + movingCountCore(threshold, rows, cols, row + 1, col, visited) + movingCountCore(threshold, rows, cols, row, col - 1, visited)
            + movingCountCore(threshold, rows, cols, row, col + 1, visited);
    }

    return cnt;
  }
};