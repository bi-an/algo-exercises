// 将所有情况排列成n个有序列表：
// 
// list 0: []
// list 1: arr[0]/arr[1]
//  ...
// list j: arr[0]/arr[j], arr[1]/arr[j], ..., arr[j-1]/arr[j]
//  ...
// list n-1: arr[0]/arr[n-1], arr[1]/arr[n-1], ..., arr[n-2]/arr[n-1]
// 
// 利用小顶堆合并n个有序列表的思想，当合并到第k个数时，就是第k小的数
// 由于list0为空集，所以可以直接忽略
//
// 时间复杂度：O(klogn)
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        auto comp = [&](pair<int,int>& a, pair<int,int>& b) {
            return arr[a.first] * arr[b.second] > arr[a.second] * arr[b.first];
        };
        // 小顶堆
        priority_queue<pair<int,int>,vector<pair<int,int>>, decltype(comp)> Q(comp);
        /// 合并n-1个有序列表
        for(int j=1;j<n;j++) {
            Q.emplace(0, j);
        }
        pair<int,int> ans;
        while(--k > 0) {
            auto [i,j] = Q.top();
            Q.pop();
            if(i+1 < j)
                Q.emplace(i+1, j); // 该有序列表中元素被选中，指针移动到下一个元素
        }
        auto [i,j] = Q.top();
        return {arr[i], arr[j]};
    }
};