// 贪心算法
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int farthest = 0, lastFarthest = 0, step = 0;
        for (int i = 0; i < n; ++i) {
            // 越过了上一次能达到的最远位置，必须增加一步才能到达此处。
            if (i > lastFarthest) {
                lastFarthest = farthest;
                ++step;
            }
            // farthest 记录下一步能到达的最远位置。
            // 只要 i 没有越过 lastFarthest，当前位置就都是上一步能达到的位置。
            farthest = max(farthest, i + nums[i]);
        }
        return step;
    }
};