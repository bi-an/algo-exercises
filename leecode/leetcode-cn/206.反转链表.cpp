// @Athor zzg
// 递归
class Solution
{
 public:
  ListNode *reverseList(ListNode *head)
  {
    if (head == nullptr)
      return head;
    return helper(nullptr, head);
  }

  ListNode *helper(ListNode *pre, ListNode *head)
  {
    ListNode *next = head->next;
    head->next = pre;
    if (next == nullptr)
      return head;
    return helper(head, next);
  }
};

// @Athor labuladong
// 递归
// 点评：zzg先反转，再递归，相当于循环解法；此解法反之，巧妙很多。
class Solution
{
 public:
  ListNode *reverseList(ListNode *head)
  {
    //如果链表为空或只有一个节点，直接返回
    if (head == nullptr || head->next == nullptr)
      return head;
    // 步骤拆解为： head + 已经反转好的子链表。
    // 注意：如图所示，head 还是指向原来的节点，并不是指向 newHead。
    // 因为递归调用形成子链表的过程中，无法改变图中 head 原来的指向。
    // 利用这一点，我们可以通过 head->next 找到子链表的尾节点。
    // 假设newHead是已经反转后的链表
    //      NULL
    //       ↑
    // 1  →  2  ←  3  ←  4
    // |                 |
    // head           newHead
    ListNode *newHead = reverseList(head->next);
    head->next->next = head;
    // 注意需要把原来的头节点（现在是尾节点）指向 NULL，否则有环。
    head->next = nullptr;
    return newHead;
  }
};

// 迭代
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* p = head;
        ListNode* prev = nullptr;
        while (p) {
            ListNode* next = p->next;
            p->next = prev;
            prev = p;
            p = next;
        }
        return prev;
    }
};