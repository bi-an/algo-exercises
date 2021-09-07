// https://leetcode-cn.com/problems/split-a-string-in-balanced-strings/

class Solution {
public:
    int balancedStringSplit(string s) {
        int nL = 0, nR = 0; // 可以使用一个变量d，如果d==0时表示此时已经平衡
        int ans = 0;
        for(char c : s) {
            if(c == 'L')
                nL++;
            else
                nR++;
            if(nL!=0 && nL == nR) {
                ans++;
            }
        }
        return ans;
    }
};

// 写法二
class Solution {
public:
    int balancedStringSplit(string s) {
        int d = 0, ans = 0;
        for(char c : s) {
            (c == 'L') ? d++ : d--;
            if(d == 0) ans++;
        }
        return ans;
    }
};