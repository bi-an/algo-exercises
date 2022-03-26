/*
 * @Author: your name
 * @Date: 2020-12-14 21:46:24
 * @LastEditTime: 2022-03-26 20:01:38
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\236.二叉树的最近公共祖先.cc
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 注意：后序遍历保证这是“最近”的公共祖先
class Solution
{
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  {
    // 关键点
    if (root == p || root == q || root == nullptr)
      return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left != nullptr && right != nullptr)
      return root;
    if (left != nullptr)
      return left;
    if (right != nullptr)
      return right;
    return nullptr;
  }
};

// 写法二
class Solution {
    TreeNode* ans;
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);
        return ans;        
    }

    // @return 子树中是否包含 p 或 q
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr)
            return false;
        bool inRoot = root == p || root == q;
        bool inLeft = dfs(root->left, p, q);
        bool inRight = dfs(root->right, p, q);
        // 关键判断
        if ((inLeft && inRight) || (inRoot && (inLeft || inRight)))
            ans = root;
        return inLeft || inRight || inRoot;
    }
};