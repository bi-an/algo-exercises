/*
 * @Author: your name
 * @Date: 2021-07-24 14:22:44
 * @LastEditTime: 2022-03-26 21:03:21
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\3.无重复字符的最长子串.cc
 */
/**
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
示例 4:

输入: s = ""
输出: 0
 

提示：

0 <= s.length <= 5 * 104
s 由英文字母、数字、符号和空格组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// 滑动窗口 + 哈希表
// 关键：当枚举 left 时，right 也是递增的。
// 因为 left 右移，必然从之前无重复子串删去了一个字符，此时剩余子串依然是无重复的，
// 但是长度必然小于之前，right 只需右移即可。
//
// 时间复杂度O(N)，因为滑动窗口遍历所有字符一次
// 空间复杂度O(C)，C的取值为0~256，也就所有char的取值数
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> hash; // 用来记录连续的无重复子串
        int n = s.length();
        int max_len = 0, end = 0;
        for(int i=0;i<n;i++) {
            while(end<=n-1 && hash.count(s[end])==0) {
                hash.emplace(s[end]); // 记录从s[i...end)的无重复子串
                end++;
            }
            int cur_len = end - i;
            if(max_len < cur_len)
                max_len = cur_len; // 以上三句使用max函数更简洁一些
            hash.erase(s[i]);
            // 关键：这里隐含了一个规律：
            // 右指针是不需要回退到i处的，因为s[i...end)已经是无重复的子串，
            // 当i右移时，少了一个字符s[i]，显然s[i+1...end]也是无重复的
            // 这样，hashtable也没有必要重置
        }
        return max_len;
    }
};

// 写法二
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window; // 记录窗口中的元素
        // 左闭右开区间
        int left = 0, right = 0, maxLen = 0;
        while (right < s.length()) {
            if (window.count(s[right])) {
                window.erase(s[left]);
                ++left;
            } else {
                window.insert(s[right]);
                maxLen = max(maxLen, right - left + 1);
                ++right;
            }
        }
        return maxLen;
    }
};