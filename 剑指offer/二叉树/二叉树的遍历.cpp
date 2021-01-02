// struct TreeNode {
// 	int val;
// 	struct TreeNode *left;
// 	struct TreeNode *right;
// 	TreeNode(int x) :
// 			val(x), left(NULL), right(NULL) {
// 	}
// };

//1. 中序遍历，递归
void PrintByInorder(TreeNode *pRoot)
{
  if (!pRoot)
    return;
  if (pRoot->left)
    PrintByInorder(pRoot->left);
  cout << pRoot->val << " ";
  if (pRoot->right)
    PrintByInorder(pRoot->right);
}

//1. 中序遍历，递归
void printByInorder(TreeNode *pRoot, vector<int> &vec)
{
  if (!pRoot)
    return;
  if (pRoot->left)
    printByInorder(pRoot->left, vec);
  vec.push_back(pRoot->val);
  if (pRoot->right)
    printByInorder(pRoot->right, vec);
}
vector<int> PrintByInorder(TreeNode *pRoot)
{
  vector<int> vec;
  //if(!pRoot) return vec;
  printByInorder(pRoot, vec);
  return vec;
}

//1. 中序遍历，非递归
vector<int> PrintByInorder(TreeNode *pRoot)
{
  vector<int> vec;
  if (!pRoot)
    return vec;
  TreeNode *p = pRoot;
  stack<TreeNode *> S;
  while (p || !S.empty())
  {
    while (p)
    {
      S.push(p);
      p = p->left;
    }
    //if(!S.empty()){
    p = S.top();
    vec.push_back(p->val); //所有节点都入栈，打印从栈中打印
    S.pop();               //打印完删除节点，保证不重复打印，不至于死循环
    p = p->right;
    //}
  }
  return vec;
}

// @Athor zzg
//二叉树的中序遍历，非递归
void PrintByInorder(TreeNode *root)
{
  if (root == nullptr)
    return;

  stack<TreeNode *> S;
  TreeNode *p = root;
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
      printf("%d\t", p->val);
      S.pop();
      p = p->right;
    }
  }
  printf("\n");
}

// @Athor zzg
// 二叉树的先序遍历，非递归
void PrintByPreorder(TreeNode *root)
{
  if (root == nullptr)
    return;

  stack<TreeNode *> S;
  TreeNode *p = root;
  while (p || !S.empty())
  {
    if (p)
    {
      printf("%d\t", p->val);
      if (p->right)
        S.push(p->right);
      p = p->left;
      //S.push(p);
    }
    else
    {
      p = S.top();
      S.pop();
      //p=p->right;
    }
  }
}

// @Athor zzg
// 后序遍历，非递归
// 关键:记录最后一个访问过的节点，防止重复访问
// leetcode 145, 测试通过
void PrintByPostorder(TreeNode *root)
{
  if (root == nullptr)
    return;
  TreeNode *p = root, *pre = nullptr;
  stack<TreeNode *> S;
  while (p && p != pre || !S.empty())
  {
    if (p && p != pre)
    {
      S.push(p);
      p = p->left;
    }
    else
    {
      p = S.top();
      if (p->right && p->right != pre)
      {
        p = p->right;
      }
      else
      {
        printf("%d\t", p->val);
        pre = p;
        S.pop();
      }
    }
  }
}

// 非递归
// 巧妙解法:每次将节点两次入栈；循环体内，先弹栈，如果弹出节点等于栈顶节点，说明该节点的
// 孩子节点没有被操作过，则对其孩子节点入栈；否则直接打印。
void postorderTraversal(TreeNode *root)
{
  if (root == nullptr)
    return;

  stack<TreeNode *> S;
  S.push(root);
  S.push(root);
  TreeNode *p = nullptr;
  while (!S.empty())
  {
    p = S.top();
    S.pop();
    if (!S.empty() && p == S.top())
    {
      if (p->right)
        S.push(p->right), S.push(p->right); //先进后出，要先压入右节点，再压左节点
      if (p->left)
        S.push(p->left), S.push(p->left);
    }
    else
    {
      printf("%d\t", p->val);
      //S.pop();
    }
  }
}