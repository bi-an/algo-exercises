#pragma once
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//中序遍历
static void PrintByInorder_Recursively(TreeNode *root)
{
  if (root == nullptr)
    return;
  PrintByInorder_Recursively(root->left);
  printf("%d\t", root->val);
  PrintByInorder_Recursively(root->right);
}

static std::vector<int> StoreByInorder_Iteratively(TreeNode *root)
{
  std::vector<int> vec;
  if (root == nullptr)
    return vec;
  std::stack<TreeNode *> stk;
  TreeNode *p = root;
  while (p || !stk.empty())
  {
    while (p != nullptr)
    {
      stk.push(p);
      p = p->left;
    }
    p = stk.top();
    vec.push_back(p->val);
    stk.pop();
    p = p->right;
  }
  return vec;
}

static void PrintByInorder_Iteratively(TreeNode *root)
{
  if (root == nullptr)
    return;
  TreeNode *p = root;
  stack<TreeNode *> S;
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
      printf("%d\t", p->val);
      p = p->right;
    }
  }
  printf("\n");
}

//先序遍历
static void PrintByPreorder_Recursively(TreeNode *root)
{
  if (root == nullptr)
    return;
  printf("%d\t", root->val);
  PrintByPreorder_Recursively(root->left);
  PrintByPreorder_Recursively(root->right);
}

static void PrintByPreorder_Iteratively(TreeNode *root)
{
  if (root == nullptr)
    return;
  TreeNode *p = root;
  stack<TreeNode *> S;
  while (p || !S.empty())
  {
    if (p)
    {
      printf("%d\t", p->val);
      if (p->right)
        S.push(p->right);
      // if(p->left)
      // S.push(p->left);
      p = p->left;
    }
    else
    {
      p = S.top();
      S.pop();
      // p=p->right;
    }
  }
  printf("\n");
}

static std::vector<int> StoreByPreorder_Iteratively(TreeNode *root)
{
  std::vector<int> vec;
  if (root == nullptr)
    return vec;
  std::stack<TreeNode *> stk;
  TreeNode *p = root;
  while (p || !stk.empty())
  {
    while (p != nullptr)
    {
      vec.push_back(p->val);
      stk.push(p);
      p = p->left;
    }
    p = stk.top();
    p = p->right;
    stk.pop();
  }
  return vec;
}

// 后序遍历
static void PrintByPostorder_Recursively(TreeNode *root)
{
  if (!root)
    return;
  if (root->left)
    PrintByPostorder_Recursively(root->left);
  if (root->right)
    PrintByPostorder_Recursively(root->right);
  printf("%d\t", root->val);
}

static void PrintByPostorder_Iteratively(TreeNode *root)
{
  if (root == nullptr)
    return;
  TreeNode *p = root, *pre = nullptr;
  std::stack<TreeNode *> S;
  while (p && p != pre || !S.empty())
  { //用pre记录上次访问过的节点
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
        S.pop(); //访问之后才能弹栈
      }
    }
  }
}

static TreeNode *ConstructCore(vector<int> &pre, int startPre, int endPre, vector<int> &vin, int startVin, int endVin);

TreeNode *ConstructCore(vector<int> &pre, int startPre, int endPre, vector<int> &vin, int startVin, int endVin)
{
  int value = pre[startPre];
  TreeNode *root = new TreeNode(value);
  if (endPre == startPre)
  {
    if (endVin == startVin && pre[startPre] == vin[startVin])
      return root;
    else
      return nullptr;
  }

  //在中序遍历表中找根节点
  int pos = startVin;
  while (pos <= endVin && vin[pos] != value)
    pos++;

  if (pos > endVin)
    return nullptr;

  int len = pos - startVin;
  if (len > 0)
    root->left = ConstructCore(pre, startPre + 1, startPre + len, vin, startVin, startVin + len - 1);
  if (pos < endVin)
    root->right = ConstructCore(pre, startPre + len + 1, endPre, vin, pos + 1, endVin);

  return root;
}

static TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin)
{
  if (pre.empty() || vin.empty() || pre.size() != vin.size())
    return nullptr;
  return ConstructCore(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
}

static TreeNode *ConstructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder)
{
  if (startPreorder == nullptr || endPreorder < startPreorder || startInorder == nullptr || endInorder < startInorder
      || endPreorder - startPreorder != endInorder - startInorder)
    return nullptr;

  TreeNode *root = new TreeNode(startPreorder[0]);

  if (endPreorder == startPreorder)
  { //递归终止条件
    if (endInorder == startInorder && *startPreorder == *startInorder)
      return root;
    else
      return nullptr;
  }

  //在中序遍历表中找到根节点
  int *p = startInorder;
  while (p <= endInorder && *p != startPreorder[0])
  {
    p++;
  }

  if (p > endInorder)
    return nullptr;

  int len = p - startInorder;
  if (len > 0)
    root->left = ConstructCore(startPreorder + 1, startPreorder + len, startInorder, startInorder + len - 1);
  if (p < endInorder)
    root->right = ConstructCore(startPreorder + len + 1, endPreorder, p + 1, endInorder);

  return root;
}

//int main() {
//	int pre[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
//	int vin[] = { 4, 7, 2, 1, 5, 3, 8, 6 };
//	vector<int> vec_pre(pre, pre + 8);
//	vector<int> vec_vin(vin, vin + 8);
//	TreeNode* root = reConstructBinaryTree(vec_pre, vec_vin);
//	PrintByPreorder_Recursively(root);
//	printf("\n");
//	PrintByInorder_Recursively(root);
//	printf("\n");
//
//	return 0;
//}