// 转化思路：
// 每一步操作同时将n-1个元素加1，最终使得所有元素都相等
// 相当于每一步将1个元素减1，最终使得所有元素都相等。
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int min_val = *min_element(nums.begin(), nums.end());
        int ans = 0;
        for(int val : nums) {
            ans += abs(val - min_val);
        }
        return ans;
    }
};