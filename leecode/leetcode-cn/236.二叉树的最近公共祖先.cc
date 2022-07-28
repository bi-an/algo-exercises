/*
 * @Author: your name
 * @Date: 2020-12-14 21:46:24
 * @LastEditTime: 2022-03-26 20:23:51
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

// 递归
// 注意：先序遍历
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q)
            return root;
        // 上一步判断说明一路走到 root 都没有遇到 p 或 q.
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        // 说明 left 和 right 各自遇到了 p 和 q，那么 root 一定是父节点。
        if (left != nullptr && right != nullptr)
            return root;
        // 将 p、q 或 root 递归返回，保证最终返回的是最深处的节点，也就是“最近”的父节点。
        // 题目规定节点可以是其本身的父节点，所以这种情况也不需要特殊处理。
        return left != nullptr ? left : right;
    }
};

// 递归写法二
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

// 方法二：记录父节点
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    unordered_map<TreeNode*, TreeNode*> fa; // 记录父节点
    unordered_map<TreeNode*, bool> vis; // 记录访问过的父节点
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 记录所有父节点
        dfs(root);
        fa[root] == nullptr;
        // 从 p 出发，遍历所有父节点（注意包括自身）
        while (p != nullptr) {
            vis[p] = true;
            p = fa[p];
        }
        // 从 q 出发，遍历所有父节点（注意包括自身）
        // 则找到的第一个已经访问过的父节点是最近公共父节点
        while (q != nullptr) {
            if (vis[q])
                return q;
            q = fa[q];
        }
        return nullptr;
    }

    void dfs(TreeNode* root) {
        if (root == nullptr)
            return;
        if (root->left)
            fa[root->left] = root;
        if (root->right)
            fa[root->right] = root;
        dfs(root->left);
        dfs(root->right);
    }
};