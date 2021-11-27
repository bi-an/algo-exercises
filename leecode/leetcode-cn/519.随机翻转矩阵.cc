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