// https://leetcode-cn.com/problems/zigzag-conversion/

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1) return s;
        vector<string> rows(min(numRows, int(s.length()))); // 按行保存结果
        bool goingDown = false;
        int row = 0;
        for(char c : s) {
            if(row == 0|| row == numRows -1)
                goingDown = !goingDown;
            if(goingDown)
                rows[row++] += c;
            else
                rows[row--] += c;
        }
        string ans;
        for(string& s : rows) {
            ans += s;
        }
        return ans;
    }
};