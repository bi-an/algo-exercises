// 注意本题允许重复，且 message 和 bannedWords 中皆可能有重复
class Solution {
public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        // 初始化时直接填充似乎效率要慢一些（690 ms)
        // unordered_set<string> banned(bannedWords.begin(), bannedWords.end());
        // 依次 insert 似乎效率高一些（590 ms)
        unordered_set<string> banned;
        for (string s : bannedWords) {
            banned.insert(s);
        }
        
        int count = 0;
        for (string s : message) {
            if (banned.count(s)) {
                count++;
                if (count >= 2)
                    return true;
            }
        }
        return false;
    }
};