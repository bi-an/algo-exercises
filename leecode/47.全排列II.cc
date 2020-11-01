#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief DFS + 剪枝
 * 
 * 所谓去重/剪枝，就是状态不得重复
 * 
 * 先排序，让相同的数排列到一起，然后去重：
 * if(visited[i] || i>0 && nums[i]==nums[i-1] && !visited[i-1])
 *    continue;
 * 
 * 以 abbc 为例，我们依次往permutation表格中填数：
 *    [][][][]
 * 
 * 上述条件只可能发生在：
 *    depth==1（即a[]） && 
 *    i==2（visited[i]，遍历到了第2个b位置）
 * 
 * 既然i=2，那么i=1（ab）时已经遍历过了，这个状态已经从递归返回，
 * 再计入i=2（还是ab）会使得状态重复，此时应该跳过。
 * 
 * 另外，使用以下条件也可以
 * 
 * if(visited[i] || i>0 && nums[i]==nums[i-1] && visited[i-1])
 * 
 * 总之：假设有3个重复，即bbb，将其状态编码为000~111，那么，这些状态完全相同，
 * 填写permutation表格时，我们选取其中任意一个状态，其他状态都跳过就可以去重。
 * 
 * 题外话：abbbccd的排列数计算：
 *    A(7,7)/(A(3,3)*A(2,2))
 * 其中，A(n,m)表示从n中取m个的排列
 */

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        if(nums.empty()) return res;

        sort(nums.begin(), nums.end());
        vector<bool> visited(nums.size());
        vector<int> path;
        path.reserve(nums.size());
        backtrace(res, nums, path, visited, 0);

        return res;
    }

    void backtrace(vector<vector<int>>& res, vector<int>& nums, vector<int>& path, vector<bool>& visited, int depth){
        if(path.size()==nums.size())
        {
            res.push_back(path);
            return;
        } 
        for(int i=0;i<nums.size();i++){
            if(visited[i] || i>0 && nums[i]==nums[i-1] && !visited[i-1])
                continue;
            visited[i]=true;
            path.push_back(nums[i]);
            backtrace(res, nums, path, visited, depth+1);
            visited[i] = false;
            path.pop_back();
        }
    }
};