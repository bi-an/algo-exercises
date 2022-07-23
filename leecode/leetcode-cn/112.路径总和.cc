// 递归
// 时间复杂度：O(n)
// 空间复杂度：O(H)，H是树的高度，也就是递归深度。
class Solution
{
 public:
  bool hasPathSum(TreeNode *root, int targetSum)
  {
    // 注意，输入空树和 0，此时应该返回 false.
    if (root == nullptr)
      return false;
    if (root->left == nullptr && root->right == nullptr)
      return root->val == targetSum;
    return hasPathSum(root->left, targetSum - root->val)
           || hasPathSum(root->right, targetSum - root->val);
  }
};