/*
 * @Author: your name
 * @Date: 2021-08-26 23:46:54
 * @LastEditTime: 2021-08-27 00:05:17
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\881.救生艇.cc
 */

/**
 * 第 i 个人的体重为 people[i]，每艘船可以承载的最大重量为 limit。

每艘船最多可同时载两人，但条件是这些人的重量之和最多为 limit。

返回载到每一个人所需的最小船数。(保证每个人都能被船载)。

 

示例 1：

输入：people = [1,2], limit = 3
输出：1
解释：1 艘船载 (1, 2)
示例 2：

输入：people = [3,2,2,1], limit = 3
输出：3
解释：3 艘船分别载 (1, 2), (2) 和 (3)
示例 3：

输入：people = [3,5,3,4], limit = 5
输出：4
解释：4 艘船分别载 (3), (3), (4), (5)
提示：

1 <= people.length <= 50000
1 <= people[i] <= limit <= 30000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/boats-to-save-people
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// 注意：本题的数据量非常大，贪心算法（每次尽可能带走最重的人并且尽量带走最大的重量）会超时
// 但是本题有一个关键“每艘船最多可同时载两人”，这使得贪心的要求可以放松：
// 如果可能，带走最重的人+最轻的人就足够了，没必要带走最大的重量。
// 因为次轻的人如果能跟最重的人走，那么他一定也可以跟次重的人走，没有区别，我们只要保证每艘船尽可能装满2人就行。
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end(), [](int a, int b){return a > b;});
        int heavy = 0, light = (int)people.size() - 1, count = 0;
        if(people[heavy] > limit)
            return -1;
        while(heavy <= light) {
            int weight = limit;
            if(people[heavy] + people[light] <= limit) {
                heavy++, light--;
            } else {
                heavy++;
            }
            count++;
        }
        return count;
    }
};