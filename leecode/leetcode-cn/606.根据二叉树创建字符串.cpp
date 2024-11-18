/*
 * @Author: your name
 * @Date: 2022-03-26 17:19:08
 * @LastEditTime: 2022-03-26 17:19:08
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\606.根据二叉树创建字符串.cc
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
class Solution {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr)
            return "";
        string s = to_string(root->val);
        if (root->right)
            s += "(" + tree2str(root->left) + ")"
                + "(" + tree2str(root->right) + ")";
        else if (root->left)
            s += "(" + tree2str(root->left) + ")";
        return s;
    }
};