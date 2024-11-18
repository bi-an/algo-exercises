class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            // 剪枝
            if (i + 3 < n && (long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
                break;
            if (i < n - 3 && (long)nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
                continue;
            if (i == 0 || nums[i] != nums[i - 1]) {
                for (int j = i + 1; j < n; ++j) {
                    // 剪枝
                    if (j + 2 < n && (long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
                        break;
                    if (j < n - 2 && (long)nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
                        continue;
                    if (j == i + 1 || nums[j] != nums[j - 1]) {
                        int l = j + 1, r = n - 1;
                        while (l < r) {
                            if (l == j + 1 || nums[l] != nums[l - 1]) {
                                long sum = (long)nums[i] + nums[j] + nums[l] + nums[r];
                                if (sum == target) {
                                    res.push_back({nums[i], nums[j], nums[l], nums[r]});
                                    ++l;
                                } else if (sum < target) {
                                    ++l;
                                } else {
                                    --r;
                                }
                            } else {
                                ++l;
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
};