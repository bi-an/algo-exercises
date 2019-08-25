class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if (input.empty() || k<=0 || k>input.size()) return res;
        sort(input.begin(),input.end());//快排，时间复杂度为O( n*log2(n) )
        for (size_t i = 0; i < k;i++) {
            res.push_back(input[i]);
        }
        return res;
    }
};

// 最大堆（手动实现）
// 也可以使用标准算法make_heap
// #include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> result;
        int length = input.size();
        if(length <= 0 || k <= 0 || k > length){
            return result;
        }
        
        for(int i = 0; i < input.size(); i++){
            if(result.size() < k){
                result.push_back(input[i]);
            }
            else{
                for(int j = k / 2; j >= 0; j--){ // 从倒数第二层开始，调整成最大堆
                    HeadAdjust(result, j, k); // 每次调整的时间复杂度是O(h)，h是高度；总时间复杂度是O(n)，n是堆的总节点数
                }
                for(int j = k - 1; j > 0; j--){
                    swap(result[0], result[j]);
                    HeadAdjust(result, 0, j);
                }
                if(result[k-1] > input[i]){
                    result[k-1] = input[i];
                }
            }
        }
        return result;
    }
private:
    // 将根节点值不断下沉，直到找到根节点的值对应的位置
    void HeadAdjust(vector<int> &input, int parent, int length){
        int temp = input[parent]; // 保存根节点的值，这样只需要不断向上覆盖，从而避免交换
        int child = 2 * parent + 1;
        while(child < length){
            if(child + 1 < length && input[child] < input[child+1]){
                child++;
            }
            if(temp >= input[child]){
                break;
            }
            input[parent] = input[child];
            
            parent = child;
            child = 2 * parent + 1;
        }
        input[parent] = temp;
    }
};

// 最大堆（手动建立）
// @Athor zzg
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> result;
        int length = input.size();
        if(length <= 0 || k <= 0 || k > length){
            return result;
        }
        
        for(int i=0;i<k;i++){
            result.push_back(input[i]); // 复制k个值到堆空间
        }
        for(int i=k/2;i>=0;i--){
            HeadAdjust(result,i,k); // 从倒数第二层开始，调整成最大堆
        }
        for(int i=k;i<input.size();i++){
            if(result[0]>input[i]){
                swap(result[0],input[i]);
                HeadAdjust(result,0,k);
            }
        }
        return result;
    }
private:
    // 将根节点值不断下沉，直到找到根节点的值对应的位置
    void HeadAdjust(vector<int> &input, int parent, int length){
        int temp = input[parent]; // 保存根节点的值，这样只需要不断向上覆盖，从而避免交换
        int child = 2 * parent + 1;
        while(child < length){
            if(child + 1 < length && input[child] < input[child+1]){
                child++;
            }
            if(temp >= input[child]){
                break;
            }
            input[parent] = input[child];
            
            parent = child;
            child = 2 * parent + 1;
        }
        input[parent] = temp;
    }
};


//利用最大堆或者红黑树，特别适用于海量数据(n很大，k很小，这样n放在辅助存储器，k个数可以一次性读入内存)
//set和map是红黑树实现的
//时间复杂度：O(nlogk)
class Solution {
public:
    typedef multiset<int, greater<int>> setType;
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if (input.empty() || k<1 || k>input.size()) return res;

        setType myset; // multiset的迭代器是一个二叉搜索树(RB-Tree)的遍历，查找复杂度为logk;并且红黑树的增删也是logk
        int i = 0;
        for (; i < k; i++)
            myset.emplace(input[i]);

        for (; i < input.size(); i++) {
            if (*myset.begin() > input[i]) {
                myset.erase(myset.begin());
                myset.emplace(input[i]);
            }
        }

        auto itr = myset.begin();
        for (int i = 0; i < k; i++) {
            res.push_back(*itr);
            itr++;
        }

        return res;
    }
};

// 基于快排的Partition
// 缺点：Partition会改动原数组（如果传值的话，效率又低）；不适合海量数据（内存不够）。
// 时间复杂度: O(n)
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if (input.empty() || k<=0 || k>input.size()) return res; //注意:1<=k<=size
        int start = 0, end = input.size() - 1;
        int index = Partition(input, start, end);
        while (index != k-1) { // 如果k=size，那么最多只能遍历到k-1，否则越界错误
            if (index > k-1) {
                end = index - 1;
            }
            if (index < k-1) {
                start = index + 1;
            }
            index = Partition(input, start, end);
        }
        //sort(input.begin(), input.begin() + index + 1);
        for (int i = 0; i < k; i++) {
            res.push_back(input[i]);
        }
        return res;
    }

    int Partition(vector<int>& input, int start, int end) {
        if (start == end) return start;
        int index = rand() % (end - start + 1) + start;
        swap(input[index], input[end]);
        int small = start - 1;
        for (int i = start; i < end; i++) {
            if (input[i] < input[end]) {
                ++small;
                if (i != small) {
                    swap(input[small], input[i]);
                }
            }
        }
        ++small;
        swap(input[small], input[end]);
        return small;
    }

};
