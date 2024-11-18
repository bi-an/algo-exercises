// 递归
class Solution
{
 public:
  bool isSymmetric(TreeNode *root)
  {
    return isSymmetric(root, root);
  }

  bool isSymmetric(TreeNode *leftTree, TreeNode *rightTree)
  {
    if (leftTree == nullptr || rightTree == nullptr)
      return leftTree == rightTree;
    return leftTree->val == rightTree->val
           && isSymmetric(leftTree->left, rightTree->right)
           && isSymmetric(leftTree->right, rightTree->left);
  }
};