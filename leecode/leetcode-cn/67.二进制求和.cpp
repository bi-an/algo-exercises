/*
 * @lc app=leetcode.cn id=67 lang=cpp
 *
 * [67] 二进制求和
 */

// @lc code=start
class Solution {
public:
    string addBinary(string a, string b) {
        string ans;
        int i = 0, carry = 0;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        while (i < a.length() || i < b.length()) {
            int sum = carry;
            if (i < a.length()) {
                sum += a[i] - '0';
            }
            if (i < b.length()) {
                sum += b[i] - '0';
            }
            ans.push_back(sum % 2 + '0');
            carry = sum / 2;
            ++i;
        }
        if (carry != 0)
            ans.push_back(carry + '0');
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
// @lc code=end
