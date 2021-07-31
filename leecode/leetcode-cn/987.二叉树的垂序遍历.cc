/*
 * @Author: your name
 * @Date: 2021-07-31 21:11:00
 * @LastEditTime: 2021-07-31 21:19:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\987.二叉树的垂序遍历.cc
 */

/**
给你二叉树的根结点 root ，请你设计算法计算二叉树的 垂序遍历 序列。

对位于 (row, col) 的每个结点而言，其左右子结点分别位于 (row + 1, col - 1) 和 (row + 1, col + 1) 。树的根结点位于 (0, 0) 。

二叉树的 垂序遍历 从最左边的列开始直到最右边的列结束，按列索引每一列上的所有结点，形成一个按出现位置从上到下排序的有序列表。如果同行同列上有多个结点，则按结点的值从小到大进行排序。

返回二叉树的 垂序遍历 序列。

 

示例 1：


输入：root = [3,9,20,null,null,15,7]
输出：[[9],[3,15],[20],[7]]
解释：
列 -1 ：只有结点 9 在此列中。
列  0 ：只有结点 3 和 15 在此列中，按从上到下顺序。
列  1 ：只有结点 20 在此列中。
列  2 ：只有结点 7 在此列中。
示例 2：


输入：root = [1,2,3,4,5,6,7]
输出：[[4],[2],[1,5,6],[3],[7]]
解释：
列 -2 ：只有结点 4 在此列中。
列 -1 ：只有结点 2 在此列中。
列  0 ：结点 1 、5 和 6 都在此列中。
          1 在上面，所以它出现在前面。
          5 和 6 位置都是 (2, 0) ，所以按值从小到大排序，5 在 6 的前面。
列  1 ：只有结点 3 在此列中。
列  2 ：只有结点 7 在此列中。
示例 3：


输入：root = [1,2,3,4,6,5,7]
输出：[[4],[2],[1,5,6],[3],[7]]
解释：
这个示例实际上与示例 2 完全相同，只是结点 5 和 6 在树中的位置发生了交换。
因为 5 和 6 的位置仍然相同，所以答案保持不变，仍然按值从小到大排序。
 

提示：

树中结点数目总数在范围 [1, 1000] 内
0 <= Node.val <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/vertical-order-traversal-of-a-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 方法一：用set和map
// 注意：不可用unordered_map和unordered_set，因为hash表要求key能够求hash，
// 而std::hash则要求key不能为容器，key不可变且唯一
// Keys are immutable, therefore, the elements in an unordered_set cannot be modified once in the container 
// because they can be inserted and removed, though.
class Solution {
    map<int, set<vector<int>>> col2coords; // 列号->坐标，每一列有多个坐标，并且可能插入多次，故用set存储
    map<vector<int>, vector<int>> coord2vals; // 坐标->二叉树的节点值，每个坐标上可能有多个节点
    int min_col = 0, max_col = 0;

    void dfs(TreeNode* root, int x, int y) {
        if(!root) return;
        set<vector<int>>& coords = col2coords[x];
        coords.insert(vector<int>{x, y});
        col2coords[x] = coords;

        coord2vals[vector<int>{x, y}].push_back(root->val);

        if(x < min_col)
            min_col = x;
        else if(x > max_col)
            max_col = x;

        dfs(root->left, x - 1, y + 1);
        dfs(root->right, x + 1, y + 1);
    }

public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == nullptr) return ans;
        dfs(root, 0, 0);
        
        for(int i = min_col; i <= max_col; i++) {
            vector<int> vals;
            set<vector<int>>& coords = col2coords[i];
            for(const vector<int>& coord : coords) { // set中的元素不可更改，不能使用引用
                vector<int>& cur_vals = coord2vals[coord];
                std::sort(cur_vals.begin(), cur_vals.end());
                for(auto v : cur_vals) {
                    vals.push_back(v);
                }
            }
            ans.push_back(vals);
        }
        return ans;
    }
};