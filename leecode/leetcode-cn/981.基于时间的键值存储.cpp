/*
 * @lc app=leetcode.cn id=981 lang=cpp
 *
 * [981] 基于时间的键值存储
 */

// @lc code=start
// 哈希表 + 二分查找
class TimeMap {
    unordered_map<string, vector<pair<int, string>>> tms;  // "tms" means "timestamp"
public:
    TimeMap() {
    }

    void set(string key, string value, int timestamp) {
        tms[key].emplace_back(timestamp, value);
    }

    // 寻找 小于等于 timestamp 的元素
    string get(string key, int timestamp) {
        // 防止插入不存在的键值对
        if (!tms.contains(key))
            return "";
        auto& pairs = tms[key];

        // // 写法一
        // auto i = ranges::upper_bound(pairs, make_pair(timestamp, ""));
        // string ans;
        // // 答案可能在 i 处，也可能在 i - 1 处，取靠后的
        // if (i != pairs.begin() && prev(i)->first <= timestamp)
        //     ans = prev(i)->second;
        // if (i != pairs.end() && i->first <= timestamp)
        //     ans = i->second;
        // return ans;

        // 写法二
        // 使用一个大于所有字符的值，127 是控制字符 DEL
        // char 的表示范围为 [-128, 127] ，如果用 128 初始化，
        // 在某些系统中，可能会被强制转化为 -128 （二进制形式均为 1000'0000）
        auto i = ranges::upper_bound(pairs, make_pair(timestamp, string({127})));
        // 指向 begin() 所有数都大于 timestamp ，都不合法
        if (i != pairs.begin())
            return (i - 1)->second;
        return "";
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
// @lc code=end
