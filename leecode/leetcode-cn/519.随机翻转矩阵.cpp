/**
 * @file 519.随机翻转矩阵.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// 1. 一维数组保存所有元素，元素为“(i,j)”位置，令 x=i*n+j，故i=x/n, j=x%n，实际保存x即可。
// 2. 数组初始状态为：第k个位置保存的元素为k。
// 3. 每次flip时随机产生一个k，取出其中的元素即可。
// 4. 已经访问过的元素交换到数组末尾，并将数组大小减1，这样每次产生[0,size-1]的随机数即可。
// 5. 不必真的保存每一个x，只需标记访问过的元素。 哈希表 k -> x
//
// 时间复杂度：
//  flip：O(1)，clear：O(F)，其中F表示翻转次数
// 空间复杂度：O(F)
class Solution {
    unordered_map<int,int> mp; // k -> x, pos ∈ [0,total-1]， 其中 total随flip次数减少
    int m,n,total;
public:
    Solution(int m, int n) {
        this->m = m;
        this->n = n;
        this->total = m*n;
        srand(time(NULL));
    }
    
    vector<int> flip() {
        int k = rand() % total; // 随机产生一个k
        total--;
        
        int unused;
        if(mp.count(k)) 
            unused = mp[k];
        else 
            unused = k;
        vector<int> ans = {unused / n, unused % n};

        // 将用过的元素交换到数组末尾，数组末尾的元素将舍弃
        if(mp.count(total))
            unused = mp[total];
        else
            unused = total;
        mp[k] = unused;

        return ans;
    }
    
    void reset() {
        total = m*n;
        mp.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */


// 用一维数组来保存二维矩阵
class Solution {
    int m, n, total;
    unordered_map<int, int> visited;
public:
    Solution(int m, int n) {
        this->m = m;
        this->n = n;
        total = m * n;
    }
    
    vector<int> flip() {
        int x = rand() % total;
        total--; // 注意

        vector<int> ans;
        if (visited.count(x))
            ans = { visited[x] / n, visited[x] % n };
        else
            ans = { x / n, x % n };

        // 假设一共 10 个矩阵位置
        // 第 1 次翻转：可选下标范围为 [0, 9]，若选中 8，则 visited = { 8->9 }
        // 第 2 次翻转：可选下标范围为 [0, 8]，若选中 4，则 visited = { 8->9, 4->8 }，
        // 但是数字 8 已经被选过了，所以，应该已经抛弃的范围 [8, 9] 中找到没有被选过的那个数字：
        // 4->8->9，也就是 4->9. 所以 visited = { 8->9, 4->9 }. 
        // PLUS: 由于下一次可选范围为 [0， 7]，所以 "8->9" 此后永远不会被再次访问了。
        // 这一步可以通过循环寻找直至找到没有选过的数字 9：
        // while (visited.count(x)) { x = visited[x]; }
        // 也可以一步到位，直接接管 visited[8]:
        // if (visited[total]) { visited[x] = visited[total]; }
        // 题外话：
        // 第 3 次翻转：可选下标范围为 [0, 7]，若选中 4，则 visited = { 8->9, 4->9 改成 4->7 }，
        // 因为 [7, 9] 范围内的数字都已经被删除了，8、9 都被访问过，4 应该映射成 [7, 9] 范围内没有被
        // 访问过的数字。
        if (visited.count(total))
            visited[x] = visited[total]; // 数字 total 已经被访问过，接管 total 映射的数
                                        // 该数字一定没有被访问过，否则
        else
            visited[x] = total;
        
        return ans;
    }
    
    void reset() {
        total = m * n;
        visited.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */