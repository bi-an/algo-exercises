// 递归
class Solution
{
 public:
  vector<string> generateParenthesis(int n)
  {
    return helper(n);
  }

  vector<string> helper(int n)
  {
    if (n == 0)
      return { "" };
    vector<string> res;
    for (int i = 0; i < n; i++)
    {
      for (string &s : helper(i))
      {
        for (string &t : helper(n - i - 1))
        {                                 // 由于本次消耗一个括号，所以-1
          string str = "(" + s + ")" + t; // 可以自定义递归规则：所有的合法括号都可以分解成该式；递归本质：重复子结构
          res.push_back(str);
        }
      }
    }
    return res;
  }
};

// 动态规划
// 时间与递归类似，内存小了一些
class Solution
{
 public:
  vector<string> generateParenthesis(int n)
  {
    vector<vector<string>> dp(n + 1);
    dp[0] = { "" };
    for (int i = 1; i <= n; i++)
    {
      for (int k = 0; k < i; k++)
      {
        for (string &s : dp[k])
        {
          for (string &t : dp[i - k - 1])
          {
            dp[i].push_back("(" + s + ")" + t);
          }
        }
      }
    }
    return dp[n];
  }
};

// dfs
class Solution
{
 public:
  vector<string> generateParenthesis(int n)
  {
    vector<string> res;
    dfs(res, "", 0, 0, n);
    return res;
  }

  // left表示左括号的个数
  void dfs(vector<string> &res, string s, int left, int right, int n)
  {
    if (left < right)
      return;
    if (left == n && left == right)
    {
      res.push_back(s);
      return;
    }
    if (left < n)
      dfs(res, s + "(", left + 1, right, n);
    if (right < n) // 这个条件判断多余，可以去掉
      dfs(res, s + ")", left, right + 1, n);
  }
};

// 递归 另一种写法
class Solution {
    vector<string> res;
public:
    vector<string> generateParenthesis(int n) {
        dfs("", 0, 2*n); // 注意：n 表示生成括号的对数，所以需要乘2
        return res;
    }
    // @param left 表示未成对的左括号的个数
    // @param n 表示当前剩余的括号个数
    void dfs(string s, int left, int n) {
        if (n == 0) {
            if (left == 0)
                res.push_back(s);
            return;
        }
        // 如果当前有未成对的左括号，则可以加上一个右括号，此时消耗掉一个左括号
        if (left > 0)
            dfs(s + ')', left - 1, n - 1);
        // 增加一个左括号
        dfs(s + '(', left + 1, n - 1);
    }
};