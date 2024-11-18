// 方法一：哈希表
// 时间复杂度O(NL)，其中N是字符串s的长度，L=10即目标串长度
// 空间复杂度O(NL)
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int L = 10;
        vector<string> ans;
        if(s.size() < L) return ans;
        unordered_map<string, int> hash;

        for(int i = 0; i + L <= s.size(); i++) {
            string subs = s.substr(i, L);
            if(++hash[subs] == 2) {
                ans.push_back(subs);
            }
        }

        return ans;
    }
};