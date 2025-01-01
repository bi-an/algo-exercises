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
        // // 写法一
        // if (!tms.contains(key))
        //     return "";
        // auto& values = tms[key];
        // auto i = ranges::upper_bound(values, make_pair(timestamp, ""));
        // string ans;
        // // 答案可能在 i 处，也可能在 i - 1 处，取靠后的
        // if (i != values.begin() && prev(i)->first <= timestamp)
        //     ans = prev(i)->second;
        // if (i != values.end() && i->first <= timestamp)
        //     ans = i->second;
        // return ans;

        // 写法二
        auto& values = tms[key];                                                    // 有可能为空
        auto i = ranges::upper_bound(values, make_pair(timestamp, string({127})));  // 使用一个大于所有字符的值，127 是控制字符 DEL
        if (i != values.begin())                                                    // values 有可能为空
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
