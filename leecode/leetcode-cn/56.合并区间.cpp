/*
 * @Author: your name
 * @Date: 2020-11-12 09:21:03
 * @LastEditTime: 2020-11-12 09:36:30
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\56.合并区间.cc
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        if (intervals.empty()) return res;

        sort(intervals.begin(), intervals.end(), comp);
        res.push_back(intervals[0]);
        vector<int> cur;
        for (int i = 1; i < intervals.size(); i++) {
            cur = intervals[i];
            vector<int>& last = res[res.size() - 1];
            if (cur[0] <= last[1] && cur[1]>=last[1]) {
                last[1] = cur[1];
            }
            else if (cur[0] > last[1]) {
                res.push_back(cur);
            }
        }
        return res;
    }

    static bool comp(vector<int>& v1, vector<int>& v2) {
        if (v1[0] == v2[0]) return v1[1] > v2[1];
        return v1[0] < v2[0];
    }
};