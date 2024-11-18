class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string s = strs[0];
        int len = s.length();
        for (int i = 1; i < strs.size() && len > 0; ++i) {
            string& cur = strs[i];
            int j = 0;
            while (j < cur.length() && s[j] == cur[j]) {
                j++;
            }
            if (j < len)
                len = j;
        }
        return s.substr(0, len);
    }
};