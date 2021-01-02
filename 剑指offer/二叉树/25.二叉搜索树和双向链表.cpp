/*
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
要求不能创建任何新的结点，只能调整树中结点指针的指向。
*/

/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/

// 二叉搜索树：根节点大于所有左子树节点，小于所有右子树节点。
// 所以，最左边的节点是最小的，最右边的节点是最大的。
// 对应地，最左边节点的根节点是次小的，最右边节点的左子树的最左边节点是次小的。

// 易错点：右子树最左节点要与根相连

class Solution
{
 public:
  TreeNode *Convert(TreeNode *pRootOfTree)
  {
    if (pRootOfTree == NULL)
      return pRootOfTree;
    //始终指向此刻遍历到的数字中最大的那个数
    TreeNode *pMaxInCurList = NULL;
    TreeNode *p = pRootOfTree;
    stack<TreeNode *> NodeSt;

    while (p || !NodeSt.empty())
    {
      while (p)
      {
        NodeSt.push(p);
        p = p->left;
      }

      p = NodeSt.top();
      NodeSt.pop();

      if (pMaxInCurList == NULL) //第一次
      {
        pMaxInCurList = p;
        pRootOfTree = pMaxInCurList;
      }
      else
      {
        p->left = pMaxInCurList;
        pMaxInCurList->right = p;
        pMaxInCurList = p;
      }
      p = p->right;
    }
    return pRootOfTree;
  }
};

// 写法2
class Solution
{
 public:
  TreeNode *Convert(TreeNode *pRootOfTree)
  {
    if (pRootOfTree == nullptr)
      return nullptr;
    stack<TreeNode *> S;
    TreeNode *p = pRootOfTree, *res = nullptr;

    while (p)
    {
      S.push(p);
      p = p->left;
    }
    if (!S.empty())
      res = S.top();

    TreeNode *pMax = nullptr; // 关键：保存当前最大节点
    // 易错点：右子树最左节点要与根相连

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
        p->left = pMax;
        if (pMax)
          pMax->right = p;
        pMax = p;
        p = p->right;
      }
    }

    return res;
  }
};

// 递归
class Solution
{
 public:
  TreeNode *Convert(TreeNode *pRootOfTree)
  {
    if (pRootOfTree == nullptr)
      return nullptr;
    TreeNode *pLastMax = nullptr;
    ConvertCore(pRootOfTree, pLastMax); // 退出时，pLastMax指向最右一个节点
    while (pRootOfTree && pRootOfTree->left)
    { // 这是一种优化：pRootOfTree在中间，而不是最右节点
      pRootOfTree = pRootOfTree->left;
    }
    return pRootOfTree;
  }
  void ConvertCore(TreeNode *pRoot, TreeNode *&pLastMax)
  {
    if (pRoot == nullptr)
      return;
    ConvertCore(pRoot->left, pLastMax);
    pRoot->left = pLastMax;
    if (pLastMax)
      pLastMax->right = pRoot;
    pLastMax = pRoot;
    ConvertCore(pRoot->right, pLastMax); //这一步也会改变pLastMax,所以最后一次递归（到达最右子树）的改变为pLastMax的最终值
  }
};

// 递归
class Solution
{
 public:
  TreeNode *Convert(TreeNode *pRootOfTree)
  {
    if (pRootOfTree == nullptr)
      return nullptr;

    TreeNode *pLastNode = nullptr;
    ConvertCore(pRootOfTree, &pLastNode);

    // 递归结束时，pLastNode指向最右节点
    // 我们需要得到最左节点，作为链表的头节点

    // TreeNode *pHead = pLastNode; // pLastNode在最右边
    TreeNode *pHead = pRootOfTree; // 优化：pRootOfTree在最右边的概率很小
    while (pHead && pHead->left)
    {
      pHead = pHead->left;
    }

    return pHead;
  }

  void ConvertCore(TreeNode *root, TreeNode **pLastNode)
  {
    if (root == nullptr)
      return;

    ConvertCore(root->left, pLastNode);

    root->left = *pLastNode; // 最左边节点是最小值
    if (*pLastNode)
      (*pLastNode)->right = root; // ->的优先级很高，与()相同

    *pLastNode = root; // 根节点是次小值

    ConvertCore(root->right, pLastNode);
  }
};

// 递归写法2
class Solution
{
 public:
  TreeNode *Convert(TreeNode *pRootOfTree)
  {
    if (pRootOfTree == nullptr)
      return nullptr;

    TreeNode *pLastNode = ConvertCore(pRootOfTree, nullptr);

    //TreeNode *pHead = pLastNode; // pLastNode在最右边
    TreeNode *pHead = pRootOfTree; // 优化：pRootOfTree在最右边的概率很小
    while (pHead && pHead->left)
    {
      pHead = pHead->left;
    }

    return pHead;
  }

  TreeNode *ConvertCore(TreeNode *root, TreeNode *pLastNode)
  {
    if (root == nullptr)
      return pLastNode;

    pLastNode = ConvertCore(root->left, pLastNode); // 最左边节点是最小值

    root->left = pLastNode;
    if (pLastNode)
      pLastNode->right = root;

    pLastNode = root; // 根节点是次小值
    pLastNode = ConvertCore(root->right, pLastNode);

    return pLastNode; // 返回当前最右边节点（最大值），因为比它小的节点已经处理完了。
                      // 对于左子树，返回的是左子树的最大节点，下一步连接到根节点的左边。
                      // 对于右子树，返回的是右子树的最大节点，结束。
  }
};

// 以下为测试部分
void PrintListRight(TreeNode *root)
{
  if (root == nullptr)
    return;
  TreeNode *p = root;
  while (p)
  {
    printf("%d -> ", p->val);
    p = p->right;
  }
  printf("NULL\n");
}

void PrintListLeft(TreeNode *root)
{
  if (root == nullptr)
    return;
  TreeNode *p = root;
  while (p->right)
  {
    //printf("%d->", p->val);
    p = p->right;
  }
  p = p->left;
  printf("NULL");
  while (p)
  {
    printf(" <- %d", p->val);
    p = p->left;
  }
  printf("\n");
}

int main()
{
  int pre[] = { 7, 3, 1, 4, 5, 10, 8, 14, 13 };
  int vin[] = { 1, 3, 4, 5, 7, 8, 10, 13, 14 };
  //int pre[] = { 1,2,7,3,4,2 };
  //int vin[] = { 7,2,1,4,2,3 };
  int sz = sizeof(vin) / sizeof(int);

  TreeNode *root = reConstructBinaryTree(vector<int>(pre, pre + sz), vector<int>(vin, vin + sz));
  PrintByPreorder_Iteratively(root);
  PrintByInorder_Iteratively(root);

  Solution sol;
  auto res = sol.Convert(root);
  PrintListRight(res);
  PrintListLeft(res);

  return 0;
}