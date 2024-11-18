/*
 * @Author: your name
 * @Date: 2021-08-22 20:55:00
 * @LastEditTime: 2021-08-22 20:57:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\789.逃脱阻碍者.cc
 */

// 自己到target的距离 < 所有ghosts到target, 就能成功逃脱；否则不能。
class Solution {
public:
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        vector<int> my_start = {0,0};
        int my_steps = getSteps(my_start, target);
        for(vector<int>& ghost : ghosts) {
            int ghost_steps = getSteps(ghost, target);
            if(ghost_steps <= my_steps) {
                return false;
            }
        }

        return true;
    }

    int getSteps(vector<int>& start, vector<int>& target) {
        return abs(start[0]-target[0]) + abs(start[1]-target[1]);
    }
};