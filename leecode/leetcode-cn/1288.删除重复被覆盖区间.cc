#include <bits/stdc++.h>
using namespace std;


/**
 * @ref labuladong 
 * 
 * 先按线段起点排序
 * 起点相同则按照终点倒序排序：这是为了
 * 线段1  |____________|    |________|
 * 线段2  |________|        |____________| 
 * 需要的是左边这种情况，因为右边情况下，如果先合并了线段1，那么线段2将在下一次合并，
 * 这样没有将较短的线段删除掉。
 */

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        if(intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(), comp);
        vector<int> intv = intervals[0];
        int res = intervals.size(), left = intv[0], right = intv[1];
        for(int i=1;i<intervals.size();i++){
            intv = intervals[i];
            if(intv[1]<=right)
                res--;
            else if(intv[0]<=right && intv[1]>=right)
                right = intv[1];
            else
            {
                left = intv[0];
                right = intv[1];
            }
        }
        return res;
    }

    static bool comp(vector<int>& v1, vector<int>& v2){
        if(v1[0]==v2[0]) return v1[1]>v2[1];
        return v1[0]<v2[0];
    }
};