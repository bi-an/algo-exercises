// 注意：测试集合中，后来的key-val可以将先前的key-val覆盖掉

// 暴力求解
// 时间复杂度：
//      insert：O(1)
//      sum：O(NM)，N为key的个数，M为key的最大长度
// 空间复杂度：O(NM)
class MapSum {
    unordered_map<string, int> kv;
public:
    MapSum() {

    }
    
    void insert(string key, int val) {
        kv[key] = val;
    }
    
    int sum(string prefix) {
        int res = 0;
        for(auto& [k,v] : kv) {
            if(k.substr(0, prefix.length()) == prefix)
                res += v;
        }
        return res;
    }
};

// 借助哈希表存储前缀


// 前缀树 / 字典树
