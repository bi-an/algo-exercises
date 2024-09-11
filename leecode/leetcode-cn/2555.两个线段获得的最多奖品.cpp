/*
 * @lc app=leetcode.cn id=2555 lang=cpp
 *
 * [2555] 两个线段获得的最多奖品
 */

// @lc code=start
class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int n = prizePositions.size();
        // dp[i]表示线段右端点不超过第i个礼物处的线段所能覆盖的最多礼物数
        // 注意到此时右端点可能没有拿全该端点的所有礼物（只拿了第i个礼物）
        // 但是我们从0开始遍历所有礼物的过程中，会添加剩余的礼物
        vector<int> dp(n + 1); // 初始化为0
        int ans = 0;
        for (int right = 0, left = 0; right < n; ++right) {
            while (prizePositions[right] - prizePositions[left] > k) {
                ++left; // left从0开始收缩至线段长度尽可能接近k
                        // 我们并没有让left从right处向左扩张
                        // 这是一个长度最多为k的滑动窗口
                        // 避免了重复遍历
                        // 我们无需担心left会超过k，
                        // 因为题目保证prizePositions[right]>=prizePositions[left]
            }
            // dp[left]表示右端点不超过第left个礼物处的最多礼物数
            // 也即是第一个线段（右端点只要不超过第left个礼物即可）所能取得的最多礼物数
            // right-left+1是当前线段（也即是第二个线段）所能取得最多礼物数
            // 注意到我们在遍历第二个线段，所以第二个线段的右端点一定处于第right个礼物处
            ans = std::max(ans, right - left + 1 + dp[left]); // dp[0]=0，而礼物标号从1开始
            dp[right + 1] = std::max(dp[right], right - left + 1); // 更新为迄此线段所能覆盖的最多礼物数
        }
        return ans;
    }
};
// @lc code=end

