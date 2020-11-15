#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> res(nums.size());

        stack<int> S;
        int n = nums.size();
        for(int i=n*2-1;i>=0;i--){
            while(!S.empty() && S.top() <= nums[i%n])
                S.pop();
            res[i%n] = S.empty() ? -1 : S.top();
            S.push(nums[i%n]);
        }

        return res;
    }
};