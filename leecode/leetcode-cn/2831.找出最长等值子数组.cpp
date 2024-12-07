/*
 * @lc app=leetcode.cn id=2831 lang=cpp
 *
 * [2831] 找出最长等值子数组
 */

// @lc code=start
// 分组 + 滑动窗口
// 题解：https://leetcode.cn/problems/find-the-longest-equal-subarray/solutions/2396401/fen-zu-shuang-zhi-zhen-pythonjavacgo-by-lqqau/
//
// 相同的数作为一组，用哈希表或数组 posList 存储这些数在原数组中的下标。
// 然后用滑动窗口遍历每个组（记作 pos）。
// 因为我们只能删除元素，所以窗口两侧的元素不需要与等值不同的元素。
//
// 窗口内相同的数一共有 r - l + 1 个。其中，l 和 r 对应每个组内的下标。
// 窗口内对应的原数组的元素一共有 pos[r] - pos[l] + 1 个。其中 pos[i] 对应原数组中的下标。
// 需要删除的数则为 pos[r] - pos[l] - (r - l) = (pos[r] - r) - (pos - l) 个
// 这些需要删除的数不得超过 k 个
// 为了简便起见，我们可以用哈希表存储 pos[i] - i ，其中 pos[i] 对应原数组下标，i 对应每个组内下标。
class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        unordered_map<int, vector<int>> posList;

        for (int i = 0; i < nums.size(); ++i) {
            // 存储 pos[i] - i
            // pos.size() 表示插入前的 size ，也就是此次插入的元素的下标
            posList[nums[i]].push_back(i - posList[nums[i]].size());
        }

        int ans = 0;
        for (auto& [dummy, pos] : posList) {
            for (int l = 0, r = 0; r < pos.size(); ++r) {
                // 当 l = r 时，必然有 pos[r] - pos[l] = 0 ，所以下标不会越界
                while (pos[r] - pos[l] > k)
                    l++;
                ans = max(ans, r - l + 1);  // 不同的数都删除了，只剩下相同的数
            }
        }

        return ans;
    }
};
// @lc code=end
