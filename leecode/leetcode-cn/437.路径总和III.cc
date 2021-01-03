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
class Solution
{
 public:
  int pathSum(TreeNode *root, int sum)
  {
    if (root == nullptr)
      return 0;
    // 起点分别为root、root->left、root->right的路径和为sum的总路径数
    return count(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
  }
  // 从root开始的路径和为sum的路径数
  int count(TreeNode *root, int sum)
  {
    if (root == nullptr)
      return 0;
    return (root->val == sum) + count(root->left, sum - root->val) + count(root->right, sum - root->val);
  }
};