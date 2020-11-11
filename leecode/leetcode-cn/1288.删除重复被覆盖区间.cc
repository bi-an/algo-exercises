#include <bits/stdc++.h>
using namespace std;

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