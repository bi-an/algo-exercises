// 找出从根到叶节点的最长路径，并打印出来

class Solution
{
 public:
  int maxPathLength(TreeNode *root)
  {
    if (root == nullptr)
      return 0;
    int res = 1;
    path.push_back(root->val);
    if (TreeDepth(root->left) > TreeDepth(root->right)) // 如果左子树的深度大，则从左子树继续寻找
      res += maxPathLength(root->left);
    else
      res += maxPathLength(root->right);
    return res;
  }

  int TreeDepth(TreeNode *root)
  {
    if (root == nullptr)
      return 0;
    return std::max(TreeDepth(root->left), TreeDepth(root->right)) + 1;
  }

  void printPath()
  {
    for (int i = 0; i < path.size(); i++)
      std::cout << path[i] << " ";
    std::cout << endl;
  }

 private:
  std::vector<int> path;
};