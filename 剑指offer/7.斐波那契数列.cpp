class Solution
{
 public:
  int Fibonacci(int n)
  {
    if (n <= 0)
      return 0;
    if (n == 1)
      return 1;
    int first = 0, second = 1;
    int res = 0;
    for (int i = 2; i <= n; i++)
    {
      res = first + second;
      first = second;
      second = res;
    }
    return res;
  }
};

//递归：有很多重复计算：原因可以用二叉树模型画图分析
//时间复杂度：O(2^n)
//通不过牛客网测试
class Solution
{
 public:
  int Fibonacci(int n)
  {
    if (n <= 0)
      return 0;
    if (n == 1)
      return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
  }
};