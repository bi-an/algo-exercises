#pragma once
#include <iostream>
#include <vector>

struct TreeLinkNode
{
  int val;
  struct TreeLinkNode *left;
  struct TreeLinkNode *right;
  struct TreeLinkNode *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

static TreeLinkNode *ConstructLinkTreeCore(std::vector<int> &pre, int startPre, int endPre, std::vector<int> &vin, int startVin, int endVin);

// 不能有相同值的节点
static TreeLinkNode *reConstructLinkTree(std::vector<int> pre, std::vector<int> vin)
{
  if (pre.size() != vin.size() || pre.empty())
    return nullptr;
  TreeLinkNode *root = ConstructLinkTreeCore(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);

  return root;
}

static TreeLinkNode *ConstructLinkTreeCore(std::vector<int> &pre, int startPre, int endPre, std::vector<int> &vin, int startVin, int endVin)
{
  // TODO
  if (startPre > endPre || startVin > endVin || endPre - startPre != endVin - startVin)
    return nullptr;
  int value = pre[startPre];
  TreeLinkNode *root = new TreeLinkNode(value);
  int posInVin = startVin;
  while (posInVin <= endVin && vin[posInVin] != value)
  {
    posInVin++;
  }
  if (posInVin > endVin)
    return nullptr;
  if (posInVin - startVin > 0)
  {
    root->left = ConstructLinkTreeCore(pre, startPre + 1, startPre + posInVin - startVin, vin, startVin, posInVin - 1);
    if (root->left)
      root->left->next = root;
  }
  if (endVin - posInVin > 0)
  {
    root->right = ConstructLinkTreeCore(pre, startPre + posInVin - startVin + 1, endPre, vin, posInVin + 1, endVin);
    root->right->next = root;
  }

  return root;
}

TreeLinkNode *KthTreeLinkNodeCore(TreeLinkNode *root, int &k);

// 中序遍历的第k个节点
static TreeLinkNode *KthTreeLinkNode(TreeLinkNode *root, int k)
{
  if (root == nullptr || k <= 0)
    return nullptr;
  return KthTreeLinkNodeCore(root, k);
}

static TreeLinkNode *KthTreeLinkNodeCore(TreeLinkNode *root, int &k)
{
  TreeLinkNode *res = nullptr;
  if (root == nullptr)
    return nullptr;
  if (root->left)
    res = KthTreeLinkNodeCore(root->left, k);
  if (k > 0)
  {
    k--;
    if (k == 0)
      res = root;
  }
  if (k > 0 && root->right)
    res = KthTreeLinkNodeCore(root->right, k);

  return res;
}
