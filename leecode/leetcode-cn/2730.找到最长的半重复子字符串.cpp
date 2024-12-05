/*
 * @lc app=leetcode.cn id=2730 lang=cpp
 *
 * [2730] 找到最长的半重复子字符串
 */

#include <bits/stdc++.h>
using namespace std;

// 注意理解题意，关键词：至多一对，相邻。

// 滑动窗口
// 写法一
namespace solution_1 {

class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int ans = 0, n = s.length(), l = 0, r = 0;
        bool hasPair = false;
        while (l < n && r < n) {
            // (1) 有 0 对相邻相等；
            // (2) 已经有 1 对相邻相等，则不再允许新的对
            while (r < n && (!hasPair || hasPair && r > 0 && s[r] != s[r - 1])) {
                if (r > 0 && s[r] == s[r - 1]) {
                    hasPair = true;
                }
                ++r;
            }
            // cout << s.substr(l, r - l) << ": " << hasPair << endl;
            ans = max(ans, r - l);
            if (l + 1 < n && s[l + 1] == s[l]) {
                hasPair = false;
            }
            ++l;
        }
        return ans;
    }
};

}  // namespace solution_1


// 简洁写法：
// https://leetcode.cn/problems/find-the-longest-semi-repetitive-substring/
// 1, 循环体：
// (1) right 不断右移，并记录当前相邻相等的对数，记作 same；
// (2) 如果邻等的对数超过 1，那么不断右移 left，将一对邻等的字符移出窗口外；
// 2, 每次循环都记录当前的窗口长度。
namespace solution_2 {

class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int ans = 1, n = s.length(), same = 0;
        for (int l = 0, r = 1; r < n; ++r) {
            // 保证窗口合法
            if (s[r] == s[r - 1] && ++same == 2) {
                // 将一个邻等对移除
                for (l++; l <= r && s[l] != s[l - 1]; l++)
                    ;
                same = 1;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

}  // namespace solution_2

// @lc code=start
// 写法三：参考了评论区的更简洁写法
// 写法二的第 (2) 点中，我们记录第一个邻等对的位置即可，不需要一直移动 left 。
// 换言之，我们每次遇到一个邻等对，则将 left 移动到上一个邻等对的第二个元素，这样就消除了上一个邻等对。
class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int l = 0, pt = 0;  // pt（point）记录上一个邻等对的第二个元素位置（这是下一个合法窗口的起始位置，因为初始的“下一个窗口”即第一个，所以初始化为 0 ）
        int ans = 1, n = s.length();
        for (int r = 1; r < n; ++r) {
            // 保证窗口合法
            if (s[r] == s[r - 1]) {
                l = pt;  // left 移动到上一个连续位置，消除了一个邻等对
                pt = r;
            }
            // 及时记录当前窗口长度
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
// @lc code=end

int main() {
    Solution sol;
    cout << "test1: " << endl;
    cout << sol.longestSemiRepetitiveSubstring("52233") << endl;

    cout << "test2: " << endl;
    cout << sol.longestSemiRepetitiveSubstring("00120023") << endl;

    cout << "test3: " << endl;
    cout << sol.longestSemiRepetitiveSubstring("012002312442") << endl;

    cout << "test4: " << endl;
    cout << sol.longestSemiRepetitiveSubstring("012002312412") << endl;

    cout << "test5: " << endl;
    cout << sol.longestSemiRepetitiveSubstring("524446") << endl;

    return 0;
}