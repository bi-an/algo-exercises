/*
 * @Author: your name
 * @Date: 2021-07-29 00:44:44
 * @LastEditTime: 2021-07-29 00:48:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\剑指offer\二叉树\BinaryTree.h
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <iostream>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BinaryTree {
    TreeNode* root = NULL;
public:
    BinaryTree(){}

    void construct(const std::vector<int>& nodes) {
        
    }

    void construct(std::string nodes) {
        
    }

};