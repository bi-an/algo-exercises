// 时间复杂度：O(N^2)，深度优先遍历对每个节点都只访问一次，但是每次都需要
// 对 path 复制构造，复制构造时间为 O(N)。
//
// 空间复杂度：O(N^2)，考虑除了答案外的空间。
// 最坏情况下，二叉树退化成链表，递归深度为 N，第 i 层的 path 长度为 i，
// 故占用空间为 sum{1, 2, ..., N} = O(N^2).
class Solution
{
  vector<string> ans;

 public:
  vector<string> binaryTreePaths(TreeNode *root)
  {
    dfs(root, "");
    return ans;
  }

  void dfs(TreeNode *root, string path)
  {
    if (root)
    {
      path += to_string(root->val);
      if (!root->left && !root->right)
      { // 叶子节点
        ans.push_back(path);
      }
      else
      {
        path += "->";
        dfs(root->left, path);
        dfs(root->right, path);
      }
    }
  }
};