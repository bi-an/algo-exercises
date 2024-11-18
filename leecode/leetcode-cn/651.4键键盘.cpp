/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2022-06-28 14:18:00
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-06-28 14:34:10
 * @FilePath: \practice\leecode\leetcode-cn\651.4键键盘.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * dp[i] 表示操作 i 次得到的最优结果。
 * 第 i 次的最优结果必然要比之前增加至少一个 A，所以有两个来源：
 * （1）直接输入 A：
 *    dp[i] = dp[i-1] + 1
 * （2）粘贴，并且其粘贴数据来源可能来自 [0,i-3] 的任何一个。
 * 之所以需要截止到 i-3，是因为前面一定至少有 Ctrl-A, Ctrl-C 两个操作。
 * 对于第 j 个数据来源，其粘贴了 (i-j-3+1) = (i-j-2) 次，如下图所示：
 *
 *  第 j 次: 数据来源 dp[j]
 *  第 j+1 次: [Ctrl-A]
 *  第 j+2 次: [Ctrl-C]
 *  第 j+3 次: [Ctrl-V] 开始粘贴
 *  ....
 *  第 i 次: [Ctrl-V]
 *
 * 注意，第 i 的最终结果还需要加上之前的数据来源 dp[j]：
 * 因为本来有 1 个 dp[j]，之后又粘贴了 (i-j-2) 个 dp[j]。
 *
 *    for j = 0:i-3
 *      dp[i] = max(dp[i], dp[j] * (i-j-2) + dp[j]) = max(dp[i], dp[j] * (i-j-1)) 
 *    dp[i] = max(dp[i], dp[i-1] + 1)
 *
 */

class Solution {
 public:
  int maxA(int n) {
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    // i 从 2 开始，因为：
    // 要想执行 [Ctrl-V]，前面至少执行了两步 [Ctrl-A]、[Ctrl-C].
    // 值得说明的是，即使一个字符都没有键入，依然可以执行 [Ctrl-A]、[Ctrl-C]、[Ctrl-V].
    for (int i = 2; i <= n; ++i) {
      dp[i] = dp[i - 1] + 1;  // 初始值，之后可能更新
      for (int j = 0; j < i - 2; ++j) {
        dp[i] = max(dp[i], dp[j] * (i - j - 1));
      }
    }
    return dp[n];
  }
};