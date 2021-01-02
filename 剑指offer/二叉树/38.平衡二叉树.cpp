// 平衡二叉树：任意节点的左右子树高度不超过1

// 基于后序遍历，每个节点只访问一次
// 后序遍历，由于遍历某个节点时，已经遍历了它的左右节点，所以每个节点只访问了一次。
// 而我们要做是在遍历每个节点的时候，记录它的深度，一边遍历一边判断二叉树是不是平衡的。
class Solution
{
 public:
  bool IsBalanced_Solution(TreeNode *pRoot)
  {
    if (!pRoot)
      return true;
    int depth = 0;
    return IsBalanced_Solution(pRoot, &depth);
  }

  bool IsBalanced_Solution(TreeNode *pRoot, int *pDepth)
  {
    if (!pRoot)
    {
      *pDepth = 0;
      return true;
    }
    int left = 0, right = 0;
    if (IsBalanced_Solution(pRoot->left, &left) && IsBalanced_Solution(pRoot->right, &right))
    {
      int diff = left - right;
      if (diff <= 1 && diff >= -1)
      {
        *pDepth = 1 + (left > right ? left : right);
        return true;
      }
    }
    return false;
  }
};

//每次访问树的深度，这样节点会被重复访问
class Solution
{
 public:
  bool IsBalanced_Solution(TreeNode *pRoot)
  {
    if (!pRoot)
      return true;
    int left = TreeDepth(pRoot->left);
    int right = TreeDepth(pRoot->right);
    int diff = left - right;
    if (diff > 1 || diff < -1)
      return false;
    return true;
  }

  int TreeDepth(TreeNode *pRoot)
  {
    if (!pRoot)
      return 0;
    int left = TreeDepth(pRoot->left);
    int right = TreeDepth(pRoot->right);
    return 1 + (left > right ? left : right);
  }
};