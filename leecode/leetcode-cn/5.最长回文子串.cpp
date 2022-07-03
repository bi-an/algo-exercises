/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2020-10-23 21:24:25
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-07-03 18:39:00
 * @FilePath: \practice\leecode\leetcode-cn\5.最长回文子串.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
class Solution
{
 public:
  // 时间复杂度：O(n^2)
  // 空间复杂度：O(n)
  string longestPalindrome(string s)
  {
    if (s.empty())
      return string();
    string ans;
    for (int i = 0; i < s.size(); i++)
    {
      string str1 = palindrome(s, i, i);
      string str2 = palindrome(s, i, i + 1);
      if (str1.size() > ans.size())
        ans = str1;
      if (str2.size() > ans.size())
        ans = str2;
    }
    return ans;
  }
  // 中心向两边
  // 小技巧：用两个参数l和r，而不是一个参数mid，这样可以处理字符传长度为奇数和偶数的情况，
  // 如果是偶数，则传入i和i；如果是奇数，则传入i和i+1
  string palindrome(const string &s, int l, int r)
  {
    while (l >= 0 && r < s.size() && s[l] == s[r])
    {
      l--;
      r++;
    }
    return s.substr(l + 1, r - l - 1);
  }
};

// 动态规划
// 时间复杂度为O(n^2)
// 空间复杂度为O(n^2)
// 本题是少有的动态规划非最优解法问题
// 本题还有一个巧妙的解法，时间复杂度为O(N)，算法名为Manacher's Algorithm（马拉车算法）
// 但是该算法很复杂，没有必要掌握
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        string res;
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (j - i >= 2) {
                    if (s[i] == s[j] && isPalindrome[i + 1][j - 1]) {
                        isPalindrome[i][j] = true;
                    }
                } else {
                    // 初始化
                    if (s[i] == s[j]) {
                        isPalindrome[i][j] = true;
                    }
                }
                if (isPalindrome[i][j] && res.length() < (j - i + 1)) {
                    res = s.substr(i, j - i + 1);
                }
            }
        }
        return res;
    }
};