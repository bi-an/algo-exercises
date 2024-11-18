class Solution {
    vector<string> res;
    map<char, string> table {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"},
    };
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};
        string cur;
        dfs(digits, 0, cur);
        return res;
    }

    void dfs(string& digits, int depth, string& cur) {
        if (depth == digits.length())
            res.push_back(cur);
        for (char c : table[digits[depth]]) {
            cur += c;
            dfs(digits, depth + 1, cur);
            cur.pop_back();
        }
    }
};