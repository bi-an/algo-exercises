#include <bits/stdc++.h>
using namespace std;

/**
 * @ref labuladong
 * 
 */

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res;
        int i = 0, j = 0;
        
        while(i < A.size() && j < B.size()){
            int a1 = A[i][0], a2 = A[i][1];
            int b1 = B[j][0], b2 = B[j][1];
            // 有交集的情况
            if(!(a2 < b1 || a1 > b2)){
                vector<int> temp = {max(a1, b1), min(a2, b2)};
                res.push_back(temp);
            }
            // 指针移动
            if(a2 < b2)
                i++;
            else if(a2 > b2)
                j++;
            else
                i++, j++;
        }

        return res;
    }
};