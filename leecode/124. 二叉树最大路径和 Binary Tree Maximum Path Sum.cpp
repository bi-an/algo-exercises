/**
* Given a non-empty binary tree, find the maximum path sum.
* 
* For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. 
* The path must contain at least one node and does not need to go through the root.
* 
* Example 1:
* 
* Input: [1,2,3]
* 
*        1
*       / \
*      2   3
* 
* Output: 6
* Example 2:
* 
* Input: [-10,9,20,null,null,15,7]
* 
*    -10
*    / \
*   9  20
*     /  \
*    15   7
* 
* Output: 42
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
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        max_sum=root->val;
        maxPathSumCore(root);
        return max_sum;
    }
    
    int maxPathSumCore(TreeNode* root){
        if(root==nullptr) return 0;
        int left=maxPathSumCore(root->left);
        int right=maxPathSumCore(root->right);
        max_sum=std::max(std::max(std::max(left,right)+root->val,
                                  std::max(left+right+root->val,root->val)),max_sum);
        return std::max(std::max(left,right)+root->val,root->val);
    }
    
private:
    int max_sum=0;
};