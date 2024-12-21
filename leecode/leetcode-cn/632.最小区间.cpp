/*
 * @lc app=leetcode.cn id=632 lang=cpp
 *
 * [632] 最小区间
 */

// 方法一：贪心 + 堆
// 题解：https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/solutions/2982588/liang-chong-fang-fa-dui-pai-xu-hua-dong-luih5/
//
// 贪心算法：搜索最短区间，每轮记录局部最优。
// (1) 第一轮：指针指向所有列表的左端点，最小值为区间左端点，最大值 max_val 为区间右端点，记录为答案；
// (2) 第二轮：最小值对应那个列表的指针右移，寻找本轮的最小值更新为区间左端点，最大值更新为区间右端点。如果本轮区间更短，则替换为答案。
// 最小值：可以使用最小堆快速找出；
// 最大值：因为指针移动时，排除的是最小值，所以之前的最大值仍然没有被改变，本轮的最大值只需比较 max_val 和移动后的指针所指值即可。
// (3) 第三轮及以后：类推。
// (4) 如果某列表遍历完成，则说明区间左端点不可再后移，否则将不可能包括该列表的任何值。搜索结束。
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size();
        auto comp = [&](const pair<int, int>& a, const pair<int, int>& b) {
            return nums[a.first][a.second] > nums[b.first][b.second];
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);

        int max_val = INT_MIN;
        // 将每个区间的左端点坐标（即在 nums 中的行和列标号）存入最小堆
        for (int i = 0; i < n; ++i) {
            pq.emplace(i, 0);
            max_val = max(nums[i][0], max_val);
        }

        vector<int> res{nums[pq.top().first][pq.top().second], max_val};
        while (true) {
            auto [i, j] = pq.top();
            pq.pop();
            if (j + 1 == nums[i].size())
                break;
            pq.emplace(i, j + 1);  // 此处插入了一次，所以堆一定不为空
            max_val = max(max_val, nums[i][j + 1]);
            auto& [i2, j2] = pq.top();
            if (max_val - nums[i2][j2] < res[1] - res[0]) {
                // res[0] = nums[i2][j2];
                // res[1] = max_val;
                res = {nums[i2][j2], max_val};
            }
        }

        return res;
    }
};

// 写法二：这和上面的思路是一样的，只是改变了堆中的比较器，这里的 pair 的第一个元素是值，
// 所以可以直接比较 pair 的大小，而不需要访问 nums 数组。
// 测试结果效率会快一倍。猜测原因可能与数组访问有关，例如按行遍历的效率就比按列遍历高。
namespace version_2 {

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int max_val = INT_MIN;
        for (int i = 0; i < n; i++) {
            pq.push({nums[i][0], i});
            max_val = max(max_val, nums[i][0]);
        }
        // 堆中存储的是 nums 中的值，无法得知 nums[i] 对应的 j ，所以需要额外的 idx 数组记录
        vector<int> idx(n, 0);
        vector<int> res = {pq.top().first, max_val};
        while (true) {
            int i = pq.top().second;
            pq.pop();
            idx[i]++;
            if (idx[i] == nums[i].size()) {
                break;
            }
            pq.push({nums[i][idx[i]], i});
            max_val = max(max_val, nums[i][idx[i]]);
            if (max_val - pq.top().first < res[1] - res[0]) {
                res = {pq.top().first, max_val};
            }
        }
        return res;
    }
};

}  // namespace version_2

// 方法二：排序 + 滑动窗口
// 题解：https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/solutions/2982588/liang-chong-fang-fa-dui-pai-xu-hua-dong-luih5/
// 对每个数同时记录其所属列表的编号，然后对所有数排序。
// 这样就等价于找到一个最短区间，使之至少包含每个列表一次。
// 细节：如果一个数在多个列表中出现，不会影响结果，因为我们据此更新后的区间和出现一次时相同。
// 理论上，该解法的效率比方法一更低，因为我们没有利用每个区间的有序性，导致排序效率低下。但测试结果比方法一快一倍，猜测是堆的维护成本。
namespace solution_2 {

// @lc code=start
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<pair<int, int>> sorted;
        int n = nums.size();
        // 可以利用每个区间的有序性合并区间，不需排序，方法是使用最小堆。或者直接使用红黑树。
        这样一来就和方法一区别不大了。
        for (int i = 0; i < n; i++) {
            for (int x : nums[i]) {
                sorted.push_back({x, i});
            }
        }
        // std::sort 效率似乎比 ranges::sort 高
        sort(sorted.begin(), sorted.end());

        int m = n;  // 当前未包含的列表数
        vector<int> res{sorted[0].first, sorted.back().first};
        unordered_map<int, int> cnt(n);  // 对出现过的列表计数
        for (int l = 0, r = 0; r < sorted.size(); ++r) {
            if (cnt[sorted[r].second]++ == 0)
                --m;
            // 可以一直删除出现多次的列表以缩短空间，直至仅出现一次
            while (cnt[sorted[l].second] > 1)
                --cnt[sorted[l++].second];
            if (m == 0 && sorted[r].first - sorted[l].first < res[1] - res[0])
                res = {sorted[l].first, sorted[r].first};
        }

        return res;
    }
};
// @lc code=end

}  // namespace solution_2
