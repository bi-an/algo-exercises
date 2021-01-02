// https://www.nowcoder.com/question/next?pid=16516564&qid=362290&tid=36448607

#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<vector<int>> dp, dist;
  int n, b;

  cin >> n;
  dist.resize(n);
  for (int i = 0; i < n; i++)
    dist[i].resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> dist[i][j];
    }
  }

  dp.resize(n);
  b = 1 << n;
  for (int i = 0; i < n; i++) {
    dp[i].resize(b);
  }

  for (int i = 0; i < n; i++)
    dp[i][0] = dist[i][0];

  for (int j = 1; j < b; j++) {
    for (int i = 0; i < n; i++) {
      int temp = INT_MAX;
      for (int bit = 0; bit < n; bit++) {
        if ((j & (1 << bit)) == 0) // 如果j中不含有这个bit位，则跳过
          continue;
        // dp[bit][j^(1<<bit)]表示从集合j中去掉这个bit位
        int cur = dist[i][bit] + dp[bit][j ^ (1 << bit)];
        if (cur < temp)
          temp = cur;
      }
      dp[i][j] = temp;
    }
  }

  cout << dp[0][b - 1] << std::endl;

  return 0;
}

/**
 * @brief 动态规划
 * 自上而下分析，自下而上填表
 *
 * dp[i][V] 从i点出发，经过集合V中各点各一次，最后回到0点的最短路程
 * dp[i][{}] 从i点出发，不经过任何其他点，直接回到0点的最短路程，即 dist[i][0]
 *
 * 设：共有4个点，分别为0,1,2,3，要求解的即为dp[0][{1,2,3}]
 *
 * 递归式：
 *  dp[0][{1,2,3}]=min{ dist[0][1]+dp[1][{2,3}], dist[0][2]+dp[2][{1,3}],
 * dist[0][3]+dp[3][{1,2}] }
 * 说明其依赖dp[1][{2,3}]，dp[2][{1,3}]，dp[3][{1,2}]的值
 *  dp[1][{2,3}]=min{ dist[1][2]+dp[2][{3}], dist[1][3]+dp[3][{2}] }
 *  dp[2][{3}]=min{ dist[2][3]+dp[3][{}] }
 *
 * 初始条件：
 *  dp[3][{}]=dist[3][0]
 *
 * 总结一般形式：
 *  (初始条件)  dp[i][{}]=dist[i][0]
 *  (递推式)    dp[i][V]=min{ dist[i][bit]+dp[bit][V-bit] | 对所有bit }
 *
 * 提示1：填表顺序应该根据依赖关系依次填写
 *  先填初始条件dp[i][{}]=dist[i][0]
 *  再填dp[1][{2}],dp[1][{3}]， dp[2][{1}],dp[2][{3}]， dp[3][{1}],dp[3][{2}]
 *  再填dp[1][{2,3}]， dp[2][{1,3}]， dp[3][{1,2}]
 *  最后填写dp[0][{1,2,3}]
 * 
 * 提示2：
 *  V可以用二进制位表示，对应bit上为1，表示这个点在集合V中。
 */
