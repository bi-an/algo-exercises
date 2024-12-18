// 用一个双向链表存储cache，最近访问的在链表头，最早访问的在链表尾
// unordered_map（哈希map）存储key-list::iterator，目的是为了在O(1)时间内找到list的某个节点。

class LRUCache
{
 public:
  LRUCache(int capacity)
  {
    cap = capacity;
  }

  int get(int key)
  {
    auto it = map.find(key);
    if (it == map.end())
      return -1;
    auto kv = *map[key];
    //cache.pop_back();
    cache.erase(map[key]);
    cache.push_front(kv);
    map[key] = cache.begin();
    return kv.second;
  }

  void put(int key, int value)
  {
    auto it = map.find(key);
    if (it == map.end())
    {
      if (cache.size() == cap)
      {
        auto kv = cache.back();
        map.erase(kv.first);
        cache.pop_back();
      }
      cache.push_front(make_pair(key, value));
      map[key] = cache.begin();
    }
    else
    {
      cache.erase(map[key]);
      cache.push_front(make_pair(key, value));
      map[key] = cache.begin();
    }
  }

 private:
  int cap;
  list<pair<int, int>> cache;                             // key-value
  unordered_map<int, list<pair<int, int>>::iterator> map; // key-iterator
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */