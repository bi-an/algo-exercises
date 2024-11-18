#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 单调栈
 * @ref labuladong
 * 
 * 处理环形数组技巧：将原数组翻倍
 * 
 */

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> res(nums.size());

        stack<int> S;
        int n = nums.size();
        // 假装将原数组翻倍了，但是空间上并没有增加
        for(int i=n*2-1;i>=0;i--){
            while(!S.empty() && S.top() <= nums[i%n])
                S.pop();
            // 在i=[2*n-1,...,n]期间，res[i]存储的值与非环形数组情况完全相同，这时的数据没有任何意义
            // 该期间的工作目标是模拟环形数组入栈
            // 在i=[n-1,...,0]时，之前存储的res[i]将被覆盖
            res[i%n] = S.empty() ? -1 : S.top();
            S.push(nums[i%n]);
        }

        return res;
    }
};