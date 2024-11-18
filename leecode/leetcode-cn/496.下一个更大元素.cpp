#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 单调栈
 * @ref labuladong 
 */
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> s;
        map<int,int> num2nextMax;
        vector<int> res(nums1.size());
        for(int i=nums2.size()-1;i>=0;i--){
            while(!s.empty() && s.top()<=nums2[i])
                s.pop();
            int nextMax = s.empty()?-1:s.top();
            num2nextMax.emplace(nums2[i], nextMax);
            s.push(nums2[i]);
        }
        for(int i=0;i<nums1.size();i++){
            res[i] = num2nextMax[nums1[i]];
        }
        return res;
    }
};

int main(){
  Solution sol;
  vector<int> nums1 = {4,1,2}, nums2 ={1,3,4,2};
  vector<int> res = sol.nextGreaterElement(nums1, nums2);

  return 0;
}
