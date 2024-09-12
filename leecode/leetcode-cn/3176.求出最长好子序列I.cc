// TODO: 动态规划优化：参加[3177]题

// 动态规划
// 动态规划的递推公式可能不止一个，只要选一个结果正确的即可。
namespace solution_1 {
// solution_1的初始化过程难以理解，建议先看solution_2
// 时间：O(n^2*k)
// 空间：O(nk)
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        // dp[i][j] 以nums[i]结尾的有j个与其后项不等的项构成的最长序列的长度，其中j<=k。
        int len = nums.size();
        vector<vector<int>> dp;
        int ans = 0; // ans是最大的dp[i][j]
        dp.resize(len, vector<int>(k + 1, -1)); // 初始值无关紧要；这里目的是resize.
        for (int i = 0; i < len; ++i) {
            dp[i][0] = 1; // {nums[i]}只有1个项，满足“与其后项不等”。长度为1.
                          // 这是初始值，不是最终值，之后会被更新。
                          // 除了dp[0][0]，其他的dp[i][0]都应该被更新。
            for (int j = 0; j <= k; ++j) {
                for (int l = 0; l < i; ++l) {
                    if (nums[i] == nums[l]) {
                        // 可以加在 {...,nums[l]}（序列有j个项满足“与后项不等”）之后，
                        // 即{..., nums[l], nums[j]}，序列长度加1.
                        dp[i][j] = std::max(dp[i][j], dp[l][j] + 1); // j==0, nums[i]==nums[l]时，
                                                                     // 照样会更新dp[i][0]
                    } else if (j > 0) {
                        // 可以加在 {..., nums[l]} （序列有j-1个项满足“与后项不等”）之后，
                        // 即{..., nums[l], nums[j]}，序列长度加1.
                        dp[i][j] = std::max(dp[i][j], dp[l][j-1] + 1);
                    }
                }
                ans = std::max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};

} // namespace solution_1


namespace solution_2 {

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        // dp[i][j] 以nums[i]结尾的有j个与其后项不等的项构成的最长序列的长度，其中j<=k。
        int len = nums.size();
        vector<vector<int>> dp;
        int ans = 0; // ans是最大的dp[i][j]
        dp.resize(len, vector<int>(k + 1, -1)); // 初始值无关紧要,但是要初始化为最小值,以便dp更新时找最大值；这里目的是resize.

        // 鉴于solution_1的初始化难以理解，这里将初始化过程单独提出来
        // j==0,意味着"只有0个项与后项不等",也就是"所有项都与后项相等",数学归纳法可知,
        //      这时"所有项都相等",此时序列可以无限延长.
        for (int i = 0; i < len; ++i) {
            dp[i][0] = 1; // {nums[i]}只有1个项，满足“与其后项不等”。长度为1.
                          // 这是初始值，不是最终值，之后会被更新。
                          // 除了dp[0][0]，其他的dp[i][0]都应该被更新。
            for (int l = 0; l < i; l++) {
                // 所有项都相等的序列，每一项都满足“本项与后项不等”，可以无限加长。
                if (nums[i] == nums[l]) {
                    dp[i][0] = std::max(dp[i][0], dp[l][0] + 1);
                }
            }
            ans = std::max(ans, dp[i][0]);
        }

        for (int i = 0; i < len; ++i) {
            for (int j = 1; j <= k; ++j) { // j=0的情况上面已经计算过了
                for (int l = 0; l < i; ++l) {
                    if (nums[i] == nums[l]) {
                        // 可以加在 {...,nums[l]}（序列有j个项满足“与后项不等”）之后，
                        // 即{..., nums[l], nums[j]}，序列长度加1.
                        dp[i][j] = std::max(dp[i][j], dp[l][j] + 1); // max{dp[l][j]+1 | l}
                    } else {
                        // 可以加在 {..., nums[l]} （序列有j-1个项满足“与后项不等”）之后，
                        // 即{..., nums[l], nums[j]}，序列长度加1.
                        dp[i][j] = std::max(dp[i][j], dp[l][j-1] + 1); // max{dp[l][j-1]+1 | l}
                    }
                }
                ans = std::max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};

} // namespace solution_2
