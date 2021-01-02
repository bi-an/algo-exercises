// @Athor zzg
class Solution
{
 public:
  vector<vector<int>> Print(TreeNode *pRoot)
  {
    vector<vector<int>> res;
    if (pRoot == nullptr)
      return res;

    TreeNode *p = pRoot;
    queue<TreeNode *> que;
    que.push(p);
    while (!que.empty())
    {
      int width = que.size();
      vector<int> row;
      for (int i = 0; i < width; i++)
      {
        p = que.front();
        que.pop();
        row.push_back(p->val);
        if (p->left)
          que.push(p->left);
        if (p->right)
          que.push(p->right);
      }
      res.push_back(row);
    }
    return res;
  }
};

// @Athor zzg
// 分行从上到下打印二叉树
void PrintARowOneTime(TreeNode *root)
{
  if (root == nullptr)
    return;

  TreeNode *p = root;
  queue<TreeNode *> que;
  que.push(p);
  while (!que.empty())
  {
    int width = que.size(); //记录当前层的宽度
    for (int i = 0; i < width; i++)
    {
      p = que.front();
      que.pop();
      printf("%d\t", p->val);
      if (p->left)
        que.push(p->left);
      if (p->right)
        que.push(p->right);
    }
    printf("\n");
  }
}

// 方法二
// 分行从上到下打印二叉树
void PrintARowOneTime(TreeNode *root)
{
  if (root == nullptr)
    return;

  TreeNode *p = root;
  queue<TreeNode *> que;
  que.push(p);
  int curLevel = 1, nextLevel = 0; //记录当前层和下一层宽度
  while (!que.empty())
  {
    p = que.front();
    que.pop();
    printf("%d\t", p->val);
    curLevel--;
    if (p->left)
    {
      que.push(p->left);
      ++nextLevel;
    }
    if (p->right)
    {
      que.push(p->right);
      ++nextLevel;
    }
    if (curLevel == 0)
    {
      printf("\n");
      curLevel = nextLevel;
    }
  }
}