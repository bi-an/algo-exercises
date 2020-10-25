/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/

// 这里是单链表，如果没有环，那么一定有一个节点的next是nullptr；
// 如果有环，那么一定没有节点的next是nullptr

//第一步：用两个指针，p1每次走1步，p2每次走2步，如果有环，则p1一定能够再次与p2相遇；如果没有环，那么最终一定会到达nullptr，退出；
// 这跟操场跑步一样，只要两个人的速度不一样，不停地跑，两个人一定会相遇。
//第二步：计算环的节点数n。相遇点一定在环内，从相遇点开始，用一个指针往下走，再次到达相遇点，则计算出n;
//第三步：用两个指针，p1先走n步，之后p1、p2同时走，每次一步，当p1和p2相遇时，恰好是环的入口。
class Solution
{
 public:
  ListNode *EntryNodeOfLoop(ListNode *pHead)
  {
    ListNode *p = meetInLoop(pHead);
    if (p == nullptr)
      return nullptr; // 没有环
    int numOfLoopNode = countLoopNode(p);
    ListNode *first = pHead, *second = pHead;
    for (int i = 0; i < numOfLoopNode; i++)
    {
      first = first->next;
    }
    while (first != second)
    {
      first = first->next;
      second = second->next;
    }
    return first;
  }

  ListNode *meetInLoop(ListNode *pHead)
  {
    if (pHead == nullptr)
      return nullptr;
    ListNode *pSlow = pHead->next;
    if (pSlow == nullptr)
      return nullptr;

    ListNode *pFast = pSlow->next;

    while (pSlow != nullptr && pFast != nullptr)
    {
      if (pSlow == pFast)
        return pSlow;
      pSlow = pSlow->next;
      pFast = pFast->next;
      if (pFast != nullptr)
        pFast = pFast->next;
    }
    return nullptr;
  }

  int countLoopNode(ListNode *pBeg)
  {
    if (pBeg == nullptr)
      return 0;
    ListNode *p = pBeg->next;
    int num = 1;
    while (p != pBeg)
    {
      num++;
      p = p->next;
    }
    return num;
  }
};

// @Athor zzg
class Solution
{
 public:
  ListNode *EntryNodeOfLoop(ListNode *pHead)
  {
    ListNode *pNode = meetInLoop(pHead);
    if (pNode == nullptr)
      return nullptr;
    int cnt = countLoopNum(pNode);
    ListNode *p1 = pHead, *p2 = pHead;
    for (int i = 0; i < cnt; i++)
      p1 = p1->next;
    while (p1 != p2)
    {
      p1 = p1->next;
      p2 = p2->next;
    }
    return p1;
  }
  ListNode *meetInLoop(ListNode *pHead)
  {
    if (pHead == nullptr)
      return nullptr;
    ListNode *p1 = pHead, *p2 = pHead; // p1和p2必须从同一个起点开始
    ListNode *res = nullptr;
    while (p1 != nullptr && p2 != nullptr)
    {
      p1 = p1->next;
      if (p2->next)
        p2 = p2->next->next;
      else
        break;

      if (p1 == p2)
      {
        res = p1;
        break;
      }
    }
    return res;
  }
  int countLoopNum(ListNode *pNode)
  {
    ListNode *p = pNode;
    int cnt = 1;
    while (p->next != pNode)
    {
      cnt++;
      p = p->next;
    }
    return cnt;
  }
};