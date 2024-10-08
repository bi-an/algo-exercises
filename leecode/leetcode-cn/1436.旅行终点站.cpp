/*
 * @lc app=leetcode.cn id=1436 lang=cpp
 *
 * [1436] 旅行终点站
 */

// @lc code=start
// 哈希表
class Solution {
   public:
    string destCity(vector<vector<string>>& paths) {
        unordered_map<string, string> table;
        for (auto& path : paths) {
            table[path[0]] = path[1];
        }
        string cur = paths[0][0];
        while (table.count(cur)) {
            cur = table[cur];
        }
        return cur;

        // // 写法二
        // for (auto& path : paths) {
        //     if (!table.count(path[1]))
        //         return path[1];
        // }
        // return "";
    }
};
// @lc code=end
