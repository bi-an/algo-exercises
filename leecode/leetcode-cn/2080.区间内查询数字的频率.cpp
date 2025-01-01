/*
 * @lc app=leetcode.cn id=2080 lang=cpp
 *
 * [2080] 区间内查询数字的频率
 */

// @lc code=start
// 哈希表 + 二分查找
class RangeFreqQuery {
    unordered_map<int, vector<int>> pos;

public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); ++i) {
            pos[arr[i]].push_back(i);
        }
    }

    int query(int left, int right, int value) {
        if (!pos.contains(value))
            return 0;
        auto& indexes = pos[value];
        auto l = ranges::lower_bound(indexes, left);
        auto r = ranges::upper_bound(indexes, right);
        return r - l;
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
// @lc code=end
