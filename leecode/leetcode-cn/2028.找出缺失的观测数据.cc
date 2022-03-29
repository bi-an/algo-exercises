/*
 * @Author: your name
 * @Date: 2022-03-29 22:12:16
 * @LastEditTime: 2022-03-29 22:12:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\2028.找出缺失的观测数据.cc
 */

class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int miss = mean * (m + n) - accumulate(rolls.begin(), rolls.end(), 0);
        if (miss <= 0 || miss < n || miss > n * 6)
            return vector<int>();
        int init = miss / n;        
        vector<int> ans(n, init);
        for (int i = 0; i < miss - init * n; ++i) {
            ++ans[i];
        }

        return ans;
    }
};