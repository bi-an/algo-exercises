/*
 * @Author: your name
 * @Date: 2022-03-26 17:10:14
 * @LastEditTime: 2022-03-26 17:10:17
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\682.棒球比赛.cc
 */
class Solution {
public:
    int calPoints(vector<string>& ops) {
        int ans = 0;
        vector<int> points;
        for (string& op : ops) {
            int n = points.size();
            switch (op[0]) {
            case 'C':
                ans -= points[n - 1];
                points.pop_back();
                break;
            case 'D':
                ans += points[n - 1] * 2;
                points.push_back(2 * points[n - 1]);
                break;
            case '+':
                ans += points[n - 2] + points[n - 1];
                points.push_back(points[n - 2] + points[n - 1]);
                break;
            default:
                ans += stoi(op);
                points.push_back(stoi(op));
                break;
            }
        }
        return ans;
    }
};