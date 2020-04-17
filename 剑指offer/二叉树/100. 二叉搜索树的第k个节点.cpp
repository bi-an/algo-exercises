// 二叉搜索树的中序遍历时递增数列

// @Athor zzg
// 非递归 18ms
class Solution
{
 public:
  TreeNode *KthNode(TreeNode *pRoot, int k)
  {
    if (pRoot == nullptr || k <= 0)
      return nullptr;

    stack<TreeNode *> S;
    TreeNode *p = pRoot;

    int cnt = 0;

    while (p || !S.empty())
    {
      if (p)
      {
        S.push(p);
        p = p->left;
      }
      else
      {
        p = S.top();
        S.pop();
        cnt++;
        if (cnt == k)
          break;
        p = p->right;
      }
    }
    return p;
  }
};

// 递归 3ms
class Solution
{
 public:
  TreeNode *KthNode(TreeNode *pRoot, int k)
  {
    if (pRoot == nullptr || k <= 0)
      return nullptr;
    int cur = 0;
    return KthNodeCore(pRoot, k, cur);
  }

  TreeNode *KthNodeCore(TreeNode *root, int k, int &cur)
  {
    if (root == nullptr)
      return nullptr;

    TreeNode *res = nullptr;
    if (root->left)
      res = KthNodeCore(root->left, k, cur);

    if (cur < k)
    {
      cur++;
      if (cur == k)
        res = root; //确保只记录一次，保证递归退出时不会被修改
    }

    if (cur < k && root->right) //如果cur>=k，说明找到了，不需要再往下进行了
      res = KthNodeCore(root->right, k, cur);

    return res;
  }
};

// 《剑指offer》 3-4ms
class Solution
{
 public:
  TreeNode *KthNode(TreeNode *pRoot, int k)
  {
    if (pRoot == nullptr || k <= 0)
      return nullptr;

    return KthNodeCore(pRoot, k);
  }

  TreeNode *KthNodeCore(TreeNode *pRoot, int &k)
  {
    TreeNode *target = nullptr;
    if (pRoot->left)
      target = KthNodeCore(pRoot->left, k);

    if (target == nullptr)
    {
      k--;
      if (k == 0)
        target = pRoot; //确保只记录一次
    }

    if (target == nullptr && pRoot->right) //如果target被修改了，说明找到了这个节点，不需要再往下进行了
      target = KthNodeCore(pRoot->right, k);

    return target;
  }
};
