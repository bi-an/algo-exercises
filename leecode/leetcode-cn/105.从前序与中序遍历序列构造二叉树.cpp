// 分治法：这是递归，也是分治。
//
// 时间复杂度：O(n)，两个序列各自遍历了一次。
// 空间复杂度：O(n)，哈希表占用的空间。
//
// Tip: 如果不使用哈希表，而是每次都重新搜索根在中序遍历序列中的位置，那么时间复杂度为多少？
// 答：(1) 最好时间复杂度为 O(n)，此时每次搜索1步就能找到根，也就是说这是一个完全左倾的链表。
// (2) 最坏时间复杂度 O(n^2)，此时每次搜索都需要达到最后一个位置，即搜索长度依次为 n, n-1, ..., 1，
// 仅仅在中序遍历序列中搜索根就花费了 O(n^2) 时间，而建立二叉搜索树又遍历了一次，时间为 O(n).
// 总时间复杂度为 O(n^2).
//
class Solution
{
  // hash 表记录根在中序遍历序列中的位置。
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