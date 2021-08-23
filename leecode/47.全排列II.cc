#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/**
 * 给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。

示例 1：

输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
示例 2：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 

提示：

1 <= nums.length <= 8
-10 <= nums[i] <= 10

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutations-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 */

/**
 * @brief DFS + 剪枝
 * 
 * 所谓去重/剪枝，就是状态不得重复
 * 
 * 要解决重复问题，我们只要设定一个规则，保证在填第 idx 个数的时候重复数字只会被填入一次即可。
 * 而在本题解中，我们选择对原数组排序，保证相同的数字都相邻，
 * 然后每次填入的数一定是这个数所在重复数集合中「从左往右第一个未被填过的数字」，即以下判断条件
 * 
 * if(visited[i] || i>0 && nums[i]==nums[i-1] && !visited[i-1])
 *    continue;
 * 
 * 这个判断条件保证了对于重复数的集合，一定是从左往右逐个填入的。
 * 假设我们有3个重复数排完序后相邻，那么我们一定保证每次都是拿从左往右第一个未被填过的数字，
 * 即整个数组的状态其实是保证了 [未填入，未填入，未填入] 到 [填入，未填入，未填入]，再到 [填入，填入，未填入]，
 * 最后到 [填入，填入，填入] 的过程的，因此可以达到去重的目标。
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

        sort(nums.begin(), nums.end()); // 先排序，方便去重
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
            if(visited[i] || i>0 && nums[i]==nums[i-1] && !visited[i-1]) // 如果i-1没有被纳入path，那么此时i和之前的i-1的情况是完全相同的
                continue;
            visited[i]=true;
            path.push_back(nums[i]);
            backtrace(res, nums, path, visited, depth+1);
            visited[i] = false; // 这两步还原状态一定要有，因为会影响下一次循环
            path.pop_back();
        }
    }
};