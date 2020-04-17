// 思路：对比前序遍历序列（包括nullptr节点），如果相同，则对称。
// 注意：一定要包括nullptr节点，不然如果所有节点的val都相等，则序列一定相等，判断出错。
class Solution
{
 public:
  bool isSymmetrical(TreeNode *pRoot)
  {
    return isSymmetricalCore(pRoot, pRoot);
  }

  bool isSymmetricalCore(TreeNode *pRoot1, TreeNode *pRoot2)
  {
    // if(pRoot1 == pRoot2)
    // 	return true;
    if (pRoot1 == nullptr && pRoot2 == nullptr)
      return true;
    if (pRoot1 == nullptr || pRoot2 == nullptr)
      return false;
    if (pRoot1->val != pRoot2->val)
      return false;

    return isSymmetricalCore(pRoot1->left, pRoot2->right)     //根1的左孩子等于根2的右孩子
           && isSymmetricalCore(pRoot1->right, pRoot2->left); //根1的右孩子等于根2的左孩子
  }
};