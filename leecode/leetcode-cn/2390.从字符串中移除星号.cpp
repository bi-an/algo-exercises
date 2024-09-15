/*
 * @lc app=leetcode.cn id=2390 lang=cpp
 *
 * [2390] 从字符串中移除星号
 */

// @lc code=start
// 逆序遍历
class Solution {
public:
    string removeStars(string s) {
        string ans;
        reverse(s.begin(), s.end());
        int numStar = 0;
        for (char c : s) {
            if (c == '*') {
                ++numStar;
            } else if (numStar == 0) {
                ans += c;
            } else {
                --numStar;
            }
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

// 正序模拟
namespace solution_2
{

class Solution {
public:
    string removeStars(string s) {
        string ans;
        for (char c : s) {
            if (c == '*') {
                ans.pop_back();
            } else {
                ans += c;
            }
        }
        return ans;
    }
};

} // namespace solution_2

// 正序模拟，c语言版本
char* removeStars(char* s) {
    int n = strlen(s);
    char* ans = (char*)malloc(n + 1);
    int len = 0;
    for (int i = 0; i < n /* s[i] != '\0' */; ++i) {
        if (s[i] == '*') {
            --len;
        } else {
            ans[len++] = s[i];
        }
    }
    ans[len] = '\0';
    return ans;
}

// @lc code=end
