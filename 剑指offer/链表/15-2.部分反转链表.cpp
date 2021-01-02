#include <iostream>
using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int val_) : val(val_), next(nullptr) {}
};

bool reverseListMN(ListNode **pRoot, int m, int n)
{
  if (pRoot == nullptr || m <= 0 || m > n) // *pRoot==nullptr
    return false;

  ListNode *p = *pRoot, *pre = nullptr;

  // 测试n是否符合要求
  int len = 0;
  while (p)
  {
    len++;
    p = p->next;
  }
  if (len < n)
    return false;

  p = *pRoot;

  int pos = 1;
  while (pos < m && p != nullptr)
  {
    pre = p;
    p = p->next;
    pos++;
  }
  if (pos != m) // 不可能有p==nullptr && pos==m，因为符合要求的p此时指向的一定不是nullptr
    return false;
  ListNode *first = pre, *second = p; // first指向第m-1个节点，second指向第m个节点
  //p = p->next;
  while (pos <= n && p != nullptr)
  {
    ListNode *post = p->next;
    p->next = pre;
    pre = p;
    p = post;
    pos++;
  }
  // if (pos <= n)
  // 	return false; // TODO
  if (m == 1)
    *pRoot = pre;
  else
    first->next = pre;
  second->next = p;
  return true;
}

ostream &operator<<(ostream &os, ListNode *root)
{
  while (root != nullptr)
  {
    os << root->val << "->";
    root = root->next;
  }
  os << "NULL";
  return os;
}

int main()
{
  ListNode *pHead = new ListNode(1);
  ListNode *p = pHead;
  for (int i = 2; i < 10; i++)
  {
    ListNode *pNew = new ListNode(i);
    p->next = pNew;
    p = p->next;
  }

  std::cout << pHead << std::endl;

  reverseListMN(&pHead, 5, 9);
  // reverseList(pHead,3, 9);

  std::cout << pHead << std::endl;

  return 0;
}