/*
 * @Author: your name
 * @Date: 2021-07-24 20:07:23
 * @LastEditTime: 2021-07-24 20:40:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\1893.检查是否区域内所有整数都被覆盖.cc
 */
/*
给你一个二维整数数组 ranges 和两个整数 left 和 right 。每个 ranges[i] = [starti, endi] 表示一个从 starti 到 endi 的 闭区间 。

如果闭区间 [left, right] 内每个整数都被 ranges 中 至少一个 区间覆盖，那么请你返回 true ，否则返回 false 。

已知区间 ranges[i] = [starti, endi] ，如果整数 x 满足 starti <= x <= endi ，那么我们称整数x 被覆盖了。

示例 1：

输入：ranges = [[1,2],[3,4],[5,6]], left = 2, right = 5
输出：true
解释：2 到 5 的每个整数都被覆盖了：
- 2 被第一个区间覆盖。
- 3 和 4 被第二个区间覆盖。
- 5 被第三个区间覆盖。
示例 2：

输入：ranges = [[1,10],[10,20]], left = 21, right = 21
输出：false
解释：21 没有被任何一个区间覆盖。
 

提示：

1 <= ranges.length <= 50
1 <= starti <= endi <= 50
1 <= left <= right <= 50

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/check-if-all-the-integers-in-a-range-are-covered
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/**
 * └——————————┘ 
 *      └————————┘ 
 *                     └——————┘ 
 *
 * 如图，好比经历隧道，入口+1，出口-1，这样若[left,right]起点和终点都在ranges中，
 * 那么，假设某个点落在这些隧道之外，当从起点left到达这个点时，总和必然为0； (1)
 * 而，如果该点落在这些隧道之中，必然有个隧道只经历了入口，没有经历出口，此时总和必然>0. (2)
 * 
 * 特别地，如果该点恰好在某段隧道的起点，那么经历了+1，总和>0，可以归结到之前的判断(2)中；
 * 而，如果该点恰好在某段隧道的终点，此时和必然大于或等于0，显然不能等于0，这与判断(1)矛盾，
 * 所以，不能恰好在出口处-1，而必须越过出口才能-1，也就是要在出口的下一个整数处-1。
 */
class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        int n = ranges.size();
        int doors[52] = {0};

        for(auto& range: ranges) {
            ++doors[range[0]]; // 入口+1，出口-1
            --doors[range[1]+1]; // 由题意range范围为1~50，那么此处下标最大为51，这也就是数组长度选择52的原因
        }
        int cur_sum = 0;
        for(int i=0;i<52;i++) {
            cur_sum += doors[i];
            if(i>=left && i<=right && cur_sum <= 0) {
                return false;
            }
        }
        return true;
    }
};