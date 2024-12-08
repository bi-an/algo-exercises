/*
 * @lc app=leetcode.cn id=2271 lang=cpp
 *
 * [2271] 毯子覆盖的最多白色砖块数
 */

// 错误解法：
// class Solution {
// public:
//     int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
//         int n = tiles.size(), ans = 0;
//         // 题目不保证有序，先排序
//         sort(tiles.begin(), tiles.end());
//         int l = tiles[0][0], r = l + carpetLen - 1, curLen = 0;
//         for (auto& tile : tiles) {
//             // 剩余毛毯与当前区间无交集，重新开始放置
//             // 不对：需要遍历毛毯起点位于每一个区间左端点的情况，这种写法跳过了一些情况。
//             if (r < tile[0]) {
//                 l = tile[0];
//                 r = l + carpetLen - 1;
//                 curLen = 0;
//             }
//             int start = max(tile[0], l), end = min(tile[1], r);
//             curLen += end - start + 1;
//             ans = max(curLen, ans);
//         }
//         return ans;
//     }
// };

// @lc code=start

// 贪心证明:
//
// 方法一：由于覆盖多段区间时,如果毛毯左边落在区间中间,右移一格的毛毯,左侧也会损失一格,不会使结果变得更好,而左移要么增加一格,要么不变,不会使得结果变得更差,所以每次都将毛毯放在区间左侧开头
// 来源：https://leetcode.cn/problems/maximum-white-tiles-covered-by-a-carpet/solutions/1494512/// by-hu-li-hu-wai-48y7/

// 方法二：毯子右端点放在一段瓷砖中间，是不如直接放在这段瓷砖右端点的（因为从中间向右移动，能覆盖的瓷砖数不会减少）
// 来源题解：https://leetcode.cn/problems/maximum-white-tiles-covered-by-a-carpet/solutions/1496434/by-endlesscheng-kdy9/

// 将每个区间视作一个元素，用滑动窗口遍历，也即滑动窗口是在各个区间间遍历。
// (1) 用窗口右端点 right 遍历每个区间，每次将右端点对齐该区间的右边界；
// 每次都将 cover 加上该区间的长度（表示毛毯覆盖了该区间）；
// (2) 然后不断右移窗口左端点 left，直至某个区间覆盖了该毛毯的左边界（毛毯左边界为 tiles[right] - carpetLen + 1）；
// left 右移过程中，cover 中需要每次减去该区间的长度；最后一个区间，还应该减去本区间左边与毛毯左边界之间的部分。
// 这种遍历方式，可以直接忽略各个区间之间的间隙。
class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        int n = tiles.size(), ans = 0, left = 0, cover = 0;

        // 题目不保证有序，先排序
        sort(tiles.begin(), tiles.end());

        // 用窗口右端点遍历各个区间
        // for (int right = 0; right < n; ++right) {
        //     cover += tiles[right][1] - tiles[right][0] + 1;
        for (auto& tile : tiles) {
            // tr 既是区间右端点，也是毛毯右端点
            int tl = tile[0], tr = tile[1];
            cover += tr - tl + 1;  // 加上该区间长度
            int carpetLeft = tr - carpetLen + 1;
            // 右移窗口左端点，直至窗口合法
            while (tiles[left][1] < carpetLeft) {
                cover -= tiles[left][1] - tiles[left][0] + 1;  // 减去该区间长度
                ++left;
            }
            // 再减去该区间左侧没有被毛毯覆盖的部分
            // 注意 1：可能毛毯左边界不位于任何区间，此时毛毯左边界将位于第一个合法区间的左侧。
            // 注意 2：这一部分不能直接从 cover 减去。理由：假设本次毛毯左边界位于区间内，下次还位于区间中，只是右移了一些，
            // 那么第二次计算时，再使用 carpetLetf - tiles[left][0] 就不对了，因为上一次我们已经从 cover 减去了一些，
            // 这会导致第二次把第一次减去的部分又减去了一次。
            // 所以，我们应该每次重算 uncover ，而 cover 永远只累加整个区间。
            int uncover = max(carpetLeft - tiles[left][0], 0);
            ans = max(ans, cover - uncover);
        }
        return ans;
    }
};
// @lc code=end
