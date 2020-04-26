struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 思路：先序遍历
// 如果要遍历的节点在某节点两侧，这个节点就是最近公共父节点；
// 如果在同一侧，则该节点从左右子树返回的肯定一个是nullptr，一个是a或者b，这个节点是a和b的最近公共父节点。
// 如果只找到a或者只找到b，那么返回a或者b；如果要求这种情况返回nullptr，则可以再新定义一个函数来调用该递归函数，判断并输出。
TreeNode *findLowestCommonAncestor(TreeNode *root, TreeNode *a, TreeNode *b)
{
  if (root == nullptr)
    return nullptr;
  if (root == a || root == b)
    return root;
  TreeNode *left = findLowestCommonAncestor(root->left, a, b);
  TreeNode *right = findLowestCommonAncestor(root->right, a, b);
  if (left && right) // a和b在root两侧 当找到这个根节点，层层返回这个根(条件1)
    return root;
  return left ? left : right; // 如果到达a或者b，层层返回a或者b(条件2)，用来作为上层条件1的判断标准
}