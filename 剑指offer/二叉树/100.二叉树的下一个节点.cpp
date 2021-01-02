/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/

/*
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
*/

// 思路：
// (1)如果有右子树，找到右子树的最左节点，输出；
// (2)否则一直往上回溯，直到遇到nullptr(到达根节点)或者当前节点是一个左孩子，输出当前节点的父亲。

// @Athor zzg
class Solution
{
 public:
  TreeLinkNode *GetNext(TreeLinkNode *pNode)
  {
    if (pNode == nullptr)
      return nullptr;

    //TreeLinkNode* res=nullptr;
    TreeLinkNode *p = pNode;
    if (p->right)
    {
      p = p->right;
      while (p->left)
        p = p->left;
      return p;
    }
    while (p->next)
    {
      if (p->next->left == p)
        return p->next;
      p = p->next;
    }
    return nullptr;
  }
};

//以下为测试代码
#include "LinkTree.h"
#include <Windows.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{

  Solution sol;
  int pre[] = { 6, 4, 2, 1, 3, 5, 9, 8, 7, 11, 10, 12 };
  int vin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
  int sz = sizeof(pre) / sizeof(int);
  auto root = reConstructLinkTree(vector<int>(pre, pre + sz), vector<int>(vin, vin + sz));

  //DWORD time = GetTickCount();
  //srand(time);
  //int k = rand() % (sz+1);
  //TreeLinkNode* p = KthTreeLinkNode(root,k);

  //auto res = sol.GetNext(p);

  for (int i = 0; i < sz; i++)
  {
    TreeLinkNode *p = KthTreeLinkNode(root, i);
    TreeLinkNode *pTemp = sol.GetNext(p);
    if (pTemp)
      cout << pTemp->val << " ";
    else
      cout << "NULL ";
  }

  return 0;
}