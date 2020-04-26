class Solution
{
 public:
  int TreeDepth(TreeNode *pRoot)
  {
    if (pRoot == nullptr)
      return 0;

    int left = TreeDepth(pRoot->left);
    int right = TreeDepth(pRoot->right);

    return (left > right ? left : right) + 1;
  }
};