// 该题和 [15.三数之和] 没有太大不同，
// 区别是：只需要每次遍历都计算一遍当前三数之和，看看是否更接近于目标数，更接近则更新。
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = INT_MAX / 2;
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < n; ++i) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                int l = i + 1, r = n - 1;
                while (l < r) {
                    if (l == i + 1 || nums[l] != nums[l - 1]) {
                        int curSum = nums[i] + nums[l] + nums[r];
                        if (curSum == target) {
                            return target;
                        } else if (curSum < target) {
                            ++l;
                        } else {
                            --r;
                        }
                        if (abs(res - target) > abs(curSum - target)) {
                            res = curSum;
                        }
                    } else {
                        ++l;
                    }
                }
            }
        }
        return res;
    }
};