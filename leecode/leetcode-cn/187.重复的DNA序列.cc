// 方法一：哈希表
// 时间复杂度O(NL)，其中N是字符串s的长度，L=10即目标串长度
// 空间复杂度O(NL)
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        if(s.size() < 10) return ans;
        unordered_map<string, int> hash;

        for(int i = 0; i + 10 <= s.size(); i++) {
            string subs = s.substr(i, 10);
            if(hash[subs] == 1) {
                ans.push_back(subs);
            }
            ++hash[subs];
        }

        return ans;
    }
};