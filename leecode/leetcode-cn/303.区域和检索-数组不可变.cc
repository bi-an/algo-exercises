/*
 * @Author: your name
 * @Date: 2022-03-26 17:16:51
 * @LastEditTime: 2022-03-26 17:17:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\303. 区域和检索 - 数组不可变.cc
 */

// 前缀和
class NumArray {
    vector<long> preSum;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        preSum.resize(n + 1);
        preSum[0] = 0;
        // preSum[i] 为 nums[0], ..., nums[i-1] 之和
        for (int i = 1; i <= n; ++i) {
            preSum[i] = preSum[i - 1] + nums[i - 1];
        }
    }
    
    int sumRange(int left, int right) {
        return preSum[right + 1] - preSum[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */