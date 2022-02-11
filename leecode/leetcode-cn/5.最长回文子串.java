// 方法一：动态规划
class Solution {
    public String longestPalindrome(String s) {
        int len = s.length();
        if (len < 2)
            return s;
        // java 默认初始化为 false
        boolean[][] dp = new boolean[len][len];
        for (int i = 0; i < len; i++)
            dp[i][i] = true;
        int maxLen = 1;
        String ans = s.substring(0, 1);
        for (int i = len - 2; i >= 0; i--) {
            for (int j = i + 1; j < len; j++) {
                if ((s.charAt(i) == s.charAt(j)) && (j == i + 1 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    int curLen = j - i + 1;
                    if (curLen > maxLen) {
                        maxLen = curLen;
                        ans = s.substring(i, j + 1);
                    }
                }
            }
        }
        return ans;
    }
}


// 方法二：中心扩展算法
// 从中间到两边递推；不需要保存dp[]
// 本质即为：我们枚举所有的「回文中心」并尝试「扩展」，直到无法扩展为止
// 边界情况即为子串长度为 1 或 2 的情况，因为这两种情况的「回文中心」不一样
class Solution {
    public String longestPalindrome(String s) {
        int len = s.length();
        if (len < 2)
            return s;
        String ans = "";
        for (int i = 0; i < len; i++) {
            String s1 = palindrome(s, i, i);
            String s2 = palindrome(s, i, i + 1);
            String curStr = s1.length() > s2.length() ? s1 : s2;
            if (ans.length() < curStr.length())
                ans = curStr;
        }
        return ans;
    }

    public String palindrome(String s, int left, int right) {
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        return s.substring(left + 1, right);
    }
}

// 方法三：Manacher 算法
// TODO 参见官方题解
