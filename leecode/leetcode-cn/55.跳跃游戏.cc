// 贪心算法
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int index = 0, farthest = 0;
        int n = nums.size();
        for(int i=0;i<n;i++){
            farthest = max(farthest, i + nums[i]);
            // 卡住不动了
            if(farthest == i)
                break;
        }
        return farthest>=n-1;
    }
};