/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2022-06-24 11:11:54
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-06-24 12:07:32
 * @FilePath: \practice\leecode\leetcode-cn\91.解码方法.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

// 时间复杂度：O(2^n)。超时。
// 参考：https://leetcode.cn/problems/decode-ways/solution/gong-shui-san-xie-gen-ju-shu-ju-fan-wei-ug3dd/
// 每个位置的字符，可以作为一个独立的词，也可以与上一个字符组成一个词（不考虑分割结果的合法性），
// 相当于每个字符有两种选择。所以 n 个字符的时间复杂度是 O(2^n).
class Solution
{
  int count_ = 0;

 public:
  int numDecodings(string s)
  {
    if (s.empty())
        return 0;
    dfs(s, 0);
    return count_;
  }

  void dfs(string s, int start)
  {
      int len = s.length();
      if (start >= len) {
          ++count_;
          return;
      }

      int num = s[start] - '0';
      if (num <= 0 || num > 26)
        return;
      dfs(s, start + 1);

      if (start + 1 < len) {
        num = num * 10 + s[start + 1] - '0';
        if (num <= 0 || num > 26)
            return;
        dfs(s, start + 2);
      }
  }
};