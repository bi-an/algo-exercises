// 滑动窗口 + 哈希表
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans, sCount(26), pCount(26); // 注意这个哈希表技巧
        int i, pLen = p.length(), sLen = s.length();

        if(sLen < pLen)
            return ans;

        for(int i=0;i<pLen;i++) {
            ++sCount[s[i]-'a'];
            ++pCount[p[i]-'a'];
        }

        if(sCount == pCount)
            ans.emplace_back(0);

        for(i=0;i<sLen-pLen;i++) {
            --sCount[s[i]-'a'];
            ++sCount[s[i+pLen]-'a'];

            if(sCount == pCount)
                ans.emplace_back(i+1);
        }

        return ans;
    }
};