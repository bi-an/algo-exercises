/*
 * @Author: your name
 * @Date: 2021-09-14 22:21:19
 * @LastEditTime: 2021-09-14 22:36:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\524.通过删除字母匹配到字典里最长单词.cc
 */

// 法一：双指针暴力求解
// 时间复杂度O(d*(m+n))，其中d为dictionay大小，m为s的长度，n为dictionary中字符串的平均长度
// 空间复杂度O(1)
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
		string ans;
		for(string ss : dictionary) {
			int i = 0, j = 0;
			while(j < ss.size() && i < s.size()) {
				if(s[i] == ss[j]) j++;
				i++;
			}
			if(j == ss.size()) {
				if(ss.length() > ans.length() || ss.length() == ans.length() && ss.compare(ans) < 0)
					ans = ss;
			}
		}
		return ans;
    }
};

// 法二：可以先对dictionary按照字符串长度逆序、字典序正序排列，这样从中找到第一个s的子序列即可
// 

// 法三：动态规划预处理
// 从法一可以看出，我们花费了很多时间在s的遍历上
// f[i][j]表示从第i个字符开始，
