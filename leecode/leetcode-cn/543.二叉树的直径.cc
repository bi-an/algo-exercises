// 时间复杂度：O(N)。每个节点仅需访问一次。
// 空间复杂度：O(Height)。栈递归最大深度为 O(Height).
class Solution
{
  int res;

 public:
  int diameterOfBinaryTree(TreeNode *root)
  {
    res = 0;
    dfs(root);
    return res;
  }

  // @return 从 root 出发的路径长度
  int dfs(TreeNode *root)
  {
    if (root == nullptr)
      return 0;
    int left = dfs(root->left);
    int right = dfs(root->right);

    if (root->left)
      left = left + 1;
    else
      left = 0;

    if (root->right)
      right = right + 1;
    else
      right = 0;

    // 用全局变量记录下最长直径
    // （已经遍历过的所有节点中任意两点间距离最长的，可能包含 root，也可能不包含 root）
    res = max(res, left + right);

    return max(left, right);
  }
};