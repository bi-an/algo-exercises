// 方法一：哈希表 + 平衡二叉树
// 时间复杂度：get 时间复杂度 O(logn)，put 时间复杂度 O(logn)，瓶颈在于平衡二叉树的查找、修改时间为 O(n).
// 空间复杂度：O(capacity)，平衡二叉树和哈希表都不会超过 capacity 大小。

// 方法一：写法一
// @Athor zzg
class LFUCache {
    struct Node {
        int cnt;
        int time;
        int key;
        int value;

        // 最前面是访问次数最少、访问时间最早的
        bool operator<(const Node& rhs) const {
            return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
        }
    };

    int time; // 时间戳
    int capacity;
    set<Node> nodes; // 根据 Node 排序
    unordered_map<int, Node> key_node; // 根据 key 排序

public:
    LFUCache(int capacity) : capacity(capacity) {

    }

    int get(int key) {
        auto it = key_node.find(key);
        if (it == key_node.end()) {
            return -1;
        }
        Node& node = it->second;
        nodes.erase(node);
        node.cnt++;
        node.time = ++time;
        nodes.insert(node);
        return node.value;
    }

    void put(int key, int value) {
        if (capacity == 0)
            return;
        auto it = key_node.find(key);
        if (it != key_node.end()) {
            Node& node = it->second;
            nodes.erase(node);
            node.cnt++;
            node.time = ++time;
            node.value = value;
            nodes.insert(node);
        }
        else {
            if (nodes.size() == capacity) {
                key_node.erase(nodes.begin()->key);
                nodes.erase(nodes.begin());
            }
            Node node{ 1, ++time, key, value };
            nodes.insert(node);
            key_node.emplace(key, node);
        }
    }
};

// 方法一：写法二
// @Athor 官方题解
struct Node {
    int cnt, time, key, value;

    Node(int _cnt, int _time, int _key, int _value):cnt(_cnt), time(_time), key(_key), value(_value){}
    
    bool operator < (const Node& rhs) const {
        return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};
class LFUCache {
    // 缓存容量，时间戳
    int capacity, time;
    unordered_map<int, Node> key_table;
    set<Node> S;
public:
    LFUCache(int _capacity) {
        capacity = _capacity;
        time = 0;
        key_table.clear();
        S.clear();
    }
    
    int get(int key) {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        // 如果哈希表中没有键 key，返回 -1
        if (it == key_table.end()) return -1;
        // 从哈希表中得到旧的缓存
        Node cache = it -> second;
        // 从平衡二叉树中删除旧的缓存
        S.erase(cache);
        // 将旧缓存更新
        cache.cnt += 1;
        cache.time = ++time;
        // 将新缓存重新放入哈希表和平衡二叉树中
        S.insert(cache);
        it -> second = cache;
        return cache.value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 如果到达缓存容量上限
            if (key_table.size() == capacity) {
                // 从哈希表和平衡二叉树中删除最近最少使用的缓存
                key_table.erase(S.begin() -> key);
                S.erase(S.begin());
            }
            // 创建新的缓存
            Node cache = Node(1, ++time, key, value);
            // 将新缓存放入哈希表和平衡二叉树中
            key_table.insert(make_pair(key, cache));
            S.insert(cache);
        }
        else {
            // 这里和 get() 函数类似
            Node cache = it -> second;
            S.erase(cache);
            cache.cnt += 1;
            cache.time = ++time;
            cache.value = value;
            S.insert(cache);
            it -> second = cache;
        }
    }
};

// 方法二：双哈希表
// 时间复杂度：get 时间复杂度 O(1)， put 时间复杂度 O(1)。整个过程只用到哈希表和链表的查找、插入、删除，时间复杂度均为 O(1).
// 空间复杂度：O(capacity).

// 方法二：写法一
class LFUCache {
    struct Node {
        int key, value, freq;
    };

    int capacity;
    int minFreq;
    // 两个哈希表可以互查，所以 Node 的成员需要包含 key
    unordered_map<int, list<Node>> freq_table;
    unordered_map<int, list<Node>::iterator> key_table;
    
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {

    }
    
    int get(int key) {
        if (capacity == 0)
            return -1;
        auto it = key_table.find(key);
        if (it == key_table.end())
            return -1;
        auto it2 = it->second;
        Node node = *it2;
        int freq = node.freq;
        // if (freq_table[minFreq].size() == 1 && freq == minFreq) {
        //     minFreq = freq + 1;
        // }
        freq_table[freq].erase(it2);
        // TODO: 如果 freq_table 不删掉空 list ，那么会发生什么？
        if (freq_table[freq].empty())
            freq_table.erase(freq);
        if (!freq_table.count(minFreq)) {
            minFreq = freq + 1;
        }
        node.freq = freq + 1;
        freq_table[freq + 1].push_front(node);
        key_table[key] = freq_table[freq + 1].begin();
        // cout << "get: key = " << key << ", freq = " << node.freq << ", minFreq = " << minFreq << endl;
        return node.value;
    }
    
    void put(int key, int value) {
        if (capacity == 0)
            return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 需要新增
            if (key_table.size() == capacity) {
                // 需要删除
                key_table.erase(freq_table[minFreq].back().key);
                freq_table[minFreq].pop_back();
                if (freq_table[minFreq].empty()) {
                    freq_table.erase(minFreq);
                }
            }
            minFreq = 1;
            Node node{key, value, 1};
            freq_table[1].push_front(node);
            key_table[key] = freq_table[1].begin();
        } else {
            auto it2 = it->second;
            Node node = *it2;
            int freq = node.freq;
            // if (freq == minFreq) {
            //     minFreq = freq + 1;
            // }
            node.freq = freq + 1;
            node.value = value;
            freq_table[freq].erase(it2);
            if (freq_table[freq].empty())
                freq_table.erase(freq);
            if (freq_table[minFreq].empty())
                minFreq = freq + 1;
            freq_table[freq + 1].push_front(node);
            key_table[key] = freq_table[freq + 1].begin();
        }
        // cout << "put: key = " << key << ", minFreq = " << minFreq << endl;
    }
};

// 方法二：写法二
// @Athor 官方题解
// 缓存的节点信息
struct Node {
    int key, val, freq;
    Node(int _key,int _val,int _freq): key(_key), val(_val), freq(_freq){}
};
class LFUCache {
    int minfreq, capacity;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int _capacity) {
        minfreq = 0;
        capacity = _capacity;
        key_table.clear();
        freq_table.clear();
    }
    
    int get(int key) {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        if (it == key_table.end()) return -1;
        list<Node>::iterator node = it -> second;
        int val = node -> val, freq = node -> freq;
        freq_table[freq].erase(node);
        // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (minfreq == freq) minfreq += 1;
        }
        // 插入到 freq + 1 中
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 缓存已满，需要进行删除操作
            if (key_table.size() == capacity) {
                // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
                auto it2 = freq_table[minfreq].back();
                key_table.erase(it2.key);
                freq_table[minfreq].pop_back();
                if (freq_table[minfreq].size() == 0) {
                    freq_table.erase(minfreq);
                }
            } 
            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        } else {
            // 与 get 操作基本一致，除了需要更新缓存的值
            list<Node>::iterator node = it -> second;
            int freq = node -> freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (minfreq == freq) minfreq += 1;
            }
            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};