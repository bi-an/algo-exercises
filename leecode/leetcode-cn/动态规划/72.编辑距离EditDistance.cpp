
// 题目：
// 将word1转换成word2需要的操作数（最小编辑距离）
// 你可以对一个单词进行如下三种操作：
//		1.插入一个字符
//		2.删除一个字符
//		3.替换一个字符

// 分析：动态规划, dp[i][j]表示子串word1[1~i]转换成子串word2[1~j]的最小编辑距离（最少操作数）。i=0或者j=0表示字串长度为0，即空。
// word1的第i个字符与word2的第j个字符比较：
// 1. 相等，不操作，dp[i][j]=dp[i-1][j-1];
// 2. 不相等：
//   2.1  删除，dp[i][j]=dp[i-1][j]+1;
//   2.2  替换，dp[i][j]=dp[i-1][j-1]+1;
//   2.3  插入，dp[i][j]=dp[i][j-1]+1.

// https://leetcode-cn.com/problems/edit-distance/solution/bian-ji-ju-chi-mian-shi-ti-xiang-jie-by-labuladong/
// 上面的递推式理解：
// str1: a b c
// str2: d f a c r
// 把str1变成str2
// i指针从str1的最后一个字符，逐渐向左移动；j指针从str2的最后一个字符向左移动
// i->c, j->r, str1[i]!=str2[j],
// 1. 把str1[i]删掉，则i向左移动，j不动（因为str1中还没有找到与这个字符相同的字符，没有处理完）
// 2. 把str1[i]替换为str2[j]，则i、j都向左移动（处理完这个字符了）
// 3. 在str1[i]后面插入str[j]，则i不动、j向左移动（因为c这个字符没有处理完，此时i还是指向c，所以i不动）
// 因为递归式有重复计算：
// dp[i][j]->dp[i-1][j-1]可以有两条路径：dp[i][j]=dp[i-1][j]+1,dp[i-1][j]=dp[i-1][j-1]+1和dp[i][j]=dp[i-1][j-1]
// 所以可以采用备忘录和动态规划的方法。
// 所谓备忘录，就是用全局变量记录已经计算了的表项，如果计算过，就直接跳过（continue），实际上，这并减少不了多少计算量，因为每步都要判断，
// 例如每步计算要3个时钟周期，那么现在判断备忘录中是否有这个值只要1个时钟周期。差别并不大。

// 空间复杂度: O(n^2)
class Solution
{
 public:
  int minDistance(string word1, string word2)
  {
    int m = word1.size(), n = word2.size();
    // dp[i][j]表示子串word1[1~i]转换成子串word2[1~j]的最小编辑距离（最少操作数）。i=0或者j=0表示字串长度为0，即空。
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
      dp[i][0] = i; // 子串word2为空，子串word1不为空，则编辑距离是子串word1的长度（word1不断向后插入word2的字符）
    }
    for (int j = 1; j <= n; j++)
    {
      dp[0][j] = j; // word2为空，word1不断删除自身的字符
    }

    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (word1[i - 1] == word2[j - 1])
        { // 注意：word的下标从0开始，dp的下标从1开始
          dp[i][j] = dp[i - 1][j - 1];
        }
        else
        {
          dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
        }
      }
    }

    return dp[m][n];
  }
};

// 空间优化：注意到dp[i][j]只与dp[i-1][j-1]、dp[i-1][j]和dp[i][j-1]有关
// ---------------------------------
// |  |  |(i-1,j-1)|(i-1,j)|
// ----------------------------------
// |  |  | (i,j-1) | (i,j) |
// ----------------------------------
// |  |  |		   |       |
// ----------------------------------

// 改进1: 也就是说，只与之前的一行和当前的一行有关
// 空间复杂度: O(2*n)
class Solution
{
 public:
  int minDistance(string word1, string word2)
  {
    int m = word1.size(), n = word2.size();
    vector<int> cur(n + 1), pre(n + 1); // dp[0][j]都为j

    for (int j = 0; j <= n; j++)
      pre[j] = j;

    for (int i = 1; i <= m; i++)
    {
      cur[0] = i; // dp[i][0]都为i
      for (int j = 1; j <= n; j++)
      {
        if (word1[i - 1] == word2[j - 1])
        { // 注意：下标一定要注意，debug了好久
          cur[j] = pre[j - 1];
        }
        else
        {
          cur[j] = min(pre[j - 1], min(pre[j], cur[j - 1])) + 1;
        }
      }
      fill(pre.begin(), pre.end(), 0);
      swap(cur, pre);
    }
    return pre[n]; // 因为最后一次pre和cur交换了
  }
};

// 改进2：注意到实际上cur只需要之前的一个数
// 空间复杂度: O(n+1)
class Solution
{
 public:
  int minDistance(string word1, string word2)
  {
    int m = word1.size(), n = word2.size(), cur = m > n ? m : n; // cur初始化为m和n的最大值，因为当m或者n为0时，将无法进入循环
    vector<int> pre(n + 1);

    for (int j = 0; j <= n; j++)
      pre[j] = j;

    for (int i = 1; i <= m; i++)
    {
      int temp = i; // dp[i][0]=i
      for (int j = 1; j <= n; j++)
      {
        if (word1[i - 1] == word2[j - 1])
          cur = pre[j - 1];
        else
        {
          cur = min(temp, min(pre[j - 1], pre[j])) + 1; // 加1一定不能忘记啊！！！一定要先把公式写准确再编程
        }
        pre[j - 1] = temp; // pre[j-1]下一次比较不再使用; 更新pre
        temp = cur;
      }
      pre[n] = temp; // pre最后一个元素更新
    }
    return cur;
  }
};

// 改进3：此处的cur保存上一行的结果
// 不同之处在于立即更新cur
class Solution
{
 public:
  int minDistance(string word1, string word2)
  {
    int m = word1.size(), n = word2.size(), pre;
    vector<int> cur(n + 1);

    for (int j = 0; j <= n; j++)
      cur[j] = j; // 如果n=0, cur也已经初始化了；只要m不为0，就会进入第一层循环

    for (int i = 1; i <= m; i++)
    {
      pre = cur[0]; // 此时的cur是上一次的
      cur[0] = i;   // 立即更新cur
      for (int j = 1; j <= n; j++)
      {
        int temp = cur[j]; // cur[j]表示上一行的第j个记录
        if (word1[i - 1] == word2[j - 1])
          cur[j] = pre;
        else
        {
          cur[j] = min(pre, min(cur[j - 1], cur[j])) + 1; // 右边的cur[j]表示上一行的第j个记录
        }
        pre = temp;
      }
    }

    return cur[n];
  }
};