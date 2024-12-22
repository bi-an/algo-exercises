
// #include <iostream>
// #include <queue> // priority_queue
// using namespace std;

// //*Definition for singly - linked list.
// struct ListNode
// {
//   int val;
//   ListNode *next;
//   ListNode(int x) : val(x), next(NULL) {}
// };


// 法1：优先级队列
// 将 k 个链表头存入一个最小堆，每次删除堆顶，并且向堆中存入原先堆顶的下一个节点。
// 时间复杂度：O(knlogk)，其中 n 表示每个链表的最长长度，一共 k 个链表。
// 空间复杂度：O(k)
class Solution
{
  struct cmp
  {
    bool operator()(ListNode *l1, ListNode *l2)
    {
      return l1->val > l2->val;
    }
  };

 public:
  ListNode *mergeKLists(vector<ListNode *> &lists)
  {
    ListNode *phead = new ListNode(0);
    ListNode *p = phead;
    if (lists.size() == 0)
      return nullptr;
    priority_queue<ListNode *, vector<ListNode *>, cmp> MinHeap;
    for (int i = 0; i < lists.size(); i++)
      if (lists[i] != nullptr)
        MinHeap.push(lists[i]);
    while (!MinHeap.empty())
    {
      p->next = MinHeap.top();
      p = p->next;
      if (MinHeap.top()->next != nullptr)
        MinHeap.push(MinHeap.top()->next);
      MinHeap.pop();
    }
    return phead->next;
  }
};

// 优先队列：写法2
class Solution
{
  static bool comp(ListNode *p1, ListNode *p2)
  {
    return p1->val > p2->val;
  }

 public:
  ListNode *mergeKLists(vector<ListNode *> &lists)
  {
    int k = lists.size();
    // 最小堆
    priority_queue<
        ListNode *,
        vector<ListNode *>,
        bool (*)(ListNode *, ListNode *)>
        q(comp);
    ListNode *head = new ListNode(), *p = head;
    for (ListNode *list : lists)
    {
      if (list != nullptr)
        q.push(list);
    }
    while (!q.empty())
    {
      ListNode *cur = q.top();
      p = p->next = cur;
      q.pop();
      if (cur->next != nullptr)
      {
        q.push(cur->next);
      }
    }
    return head->next;
  }
};

// 法2：顺序合并
// 写一个函数合并两个链表，再将合并后的链表与剩余的链表依次两两合并。
// 时间复杂度：O(k^2*n)，第一次合并时间为 2n，第二次合并时间为 3n，...，第 k - 1次合并时间为 kn.
// 空间复杂度：O(1)
//
// TODO:

// 法3：分治合并
// 递归地将所有链表一分为二，分别合并，然后将合并好的两个大链表合并。
// 时间复杂度：O(knlogk)，递归深度为 logk；递归每一层都将所有链表合并了一次，也就是时间为 O(kn)。详解 md 文档。
// 空间复杂度：O(logk)，递归深度为 logk，但是每一递归层都没有使用额外的空间，所以总空间复杂度为 O(logk)。
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, (int)lists.size() - 1);
    }

    ListNode* merge(vector<ListNode*>& lists, int l, int r) {
        if (l == r)
            return lists[l];
        if (l > r)
            return nullptr;
        int mid = (l + r) / 2;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = new ListNode(), *p = head;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                p = p->next = list1;
                list1 = list1->next;
            } else {
                p = p->next = list2;
                list2 = list2->next;
            }
        }
        p->next = list1 != nullptr ? list1 : list2;
        return head->next;
    }
};