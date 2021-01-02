#include <iostream>

struct ListNode
{
  int val;
  ListNode *next = nullptr;
  ListNode() {}
  ListNode(int _val) : val(_val) {}
};

static void printList(ListNode *pHead)
{
  ListNode *p = pHead;
  while (p != nullptr)
  {
    printf("%d ", p->val);
    p = p->next;
  }
  printf("\n");
}

static void AddToHead(ListNode **pHead, int value)
{
  if (pHead == nullptr)
    return;
  ListNode *pNew = new ListNode(value);
  pNew->next = *pHead;
  *pHead = pNew;
}

static void AddToTail(ListNode **pHead, int value)
{
  if (pHead == nullptr)
    return;
  ListNode *pNew = new ListNode(value);
  if (*pHead == nullptr)
  {
    *pHead = pNew;
  }
  else
  {
    ListNode *p = *pHead;
    while (p->next != nullptr)
    {
      p = p->next;
    }
    p->next = pNew;
  }
}

static void RemoveNode(ListNode **pHead, int value)
{
  if (pHead == nullptr || *pHead == nullptr)
    return;
  ListNode *pToBeDeleted = nullptr;
  if ((*pHead)->val == value)
  {
    pToBeDeleted = *pHead;
    *pHead = (*pHead)->next;
  }
  else
  {
    ListNode *p = *pHead;
    while (p->next != nullptr && p->next->val != value)
      p = p->next;
    if (p->next != nullptr)
    { // && p->next->val == value) {
      pToBeDeleted = p->next;
      p->next = p->next->next;
    }
  }
  if (pToBeDeleted != nullptr)
  {
    delete pToBeDeleted;
    pToBeDeleted = nullptr;
  }
}

int main()
{
  ListNode *pHead = nullptr; //=new ListNode(0);
  for (int i = 0; i < 10; i++)
  {
    AddToTail(&pHead, i);
  }
  printList(pHead);
  RemoveNode(&pHead, 5);
  printList(pHead);
  return 0;
}