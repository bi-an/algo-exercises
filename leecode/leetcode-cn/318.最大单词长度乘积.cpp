// 比较两个字符串是否有相同的字符，时间的复杂度为 O(L1*L2)
// 所有字符串都这样比较的话，时间总复杂度为 O(n^2*L1*L2)，其中 n 是字符串总个数。
//
// 为了能在 O(1) 时间比较两个字符串是否有相同的字符
// 我们将所有字符放在一个int类型的掩码中，第 i ~ i+25 位分别表示 'a'~'z' 是否出现过
// 如果 mask1 & mask2 == 0 ，表示这两个字符串不存在相同的字符。
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        unordered_map<int, int> mp; // mask -> count

        for (string& s : words) {
            int mask = 0;
            for (int i = 0; i < s.size(); i++)
                mask |= (1 << (s[i] - 'a'));
            if (mp[mask] < s.size())
                mp[mask] = s.size();
        }
        
        int res = 0;
        for (auto& [k1, v1] : mp) {
            for (auto& [k2, v2] : mp) {
                if ((k1 & k2) == 0)
                    res = max(res, v1 * v2);
            }
        }
        
        return res;
    }
};