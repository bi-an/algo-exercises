class Solution
{
  // hash 表记录数字在中序遍历序列中的位置。
  // 这是为了避免每次都重新搜寻该位置，降低时间复杂度。
  map<int, int> pos_;

 public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
  {
    int n = preorder.size();
    for (int i = 0; i < n; ++i)
      pos_[inorder[i]] = i;
    return buildTree(preorder, 0, n - 1, inorder, 0, n - 1);
  }

  TreeNode *buildTree(
      vector<int> &preorder,
      int preorder_start,
      int preorder_end,
      vector<int> &inorder,
      int inorder_start,
      int inorder_end)
  {
    if (preorder_start > preorder_end)
      return nullptr;
    int target = preorder[preorder_start];
    TreeNode *root = new TreeNode(target);
    int i = pos_[target];
    // while (inorder[i] != target)
    //     ++i;
    int len = i - inorder_start;
    root->left = buildTree(
        preorder,
        preorder_start + 1,
        preorder_start + len,
        inorder,
        inorder_start,
        inorder_start + len);
    root->right = buildTree(
        preorder,
        preorder_start + len + 1,
        preorder_end,
        inorder,
        inorder_start + len + 1,
        inorder_end);
    return root;
  }
};

// 方法二：迭代法
// 见官方题解
// TODO