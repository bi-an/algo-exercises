/*
 * @lc app=leetcode.cn id=1146 lang=cpp
 *
 * [1146] 快照数组
 */

// @lc code=start
class SnapshotArray {
    int id;
    // 注意到 snap_id 可能是跳跃的，例如：
    // {{snap_id=1, val=3}, {snap_id=4, val=8}, {snap_id=7, val=2}}
    // 所以我们调用 get(snap_id) 时，必须确知该 snap_id 处于区间哪个位置，可以用二分法
    // 正是以上缘故，我们使用二维哈希表是不合适的。
    unordered_map<int, vector<pair<int, int>>> snapshots;

public:
    SnapshotArray(int length) : id(0) {
    }

    void set(int index, int val) {
        snapshots[index].emplace_back(id, val);
    }

    int snap() {
        return id++;
    }

    int get(int index, int snap_id) {
        auto& snapshot = snapshots[index];
        // 我们需要查找「最后一个小于等于 snap_id 的元素」
        // pair 是字典序比较，先比较 first ，再比较 second
        // 由于我们构造的比较基准为 {snap_id, INT_MAX} ，所以 i 总是滞后一位（即使 snap_id 存在于集合中）
        // 由于构造的 pair 不可能与集合中的 pairs 相等，所以使用 lower_bound 和 upper_bound 无区别
        // auto i = ranges::lower_bound(snapshot, make_pair(snap_id, INT_MAX));
        // auto i = ranges::upper_bound(snapshot, make_pair(snap_id, INT_MAX));
        // 也可以构造 {snapshot_id+1, -1}
        auto i = ranges::lower_bound(snapshot, make_pair(snap_id + 1, -1));
        return i == snapshot.begin() ? 0 : prev(i)->second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
// @lc code=end
