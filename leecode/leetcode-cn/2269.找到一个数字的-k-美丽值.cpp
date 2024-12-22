/*
 * @lc app=leetcode.cn id=2269 lang=cpp
 *
 * [2269] 找到一个数字的 K 美丽值
 */

// @lc code=start
class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string s = to_string(num);
        int n = s.length(), ans = 0;
        for (int i = 0; i + k - 1 < n; ++i) {
            int x = stoi(s.substr(i, k));
            if (x > 0 && num % x == 0)
                ++ans;
        }
        return ans;
    }
};
// @lc code=end
