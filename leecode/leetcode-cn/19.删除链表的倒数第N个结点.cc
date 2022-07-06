// 解法一：两个指针，第一个指针比第二个指针先走 n + 1 步，然后同时移动。
// 这样，当第一个指针到达 NULL，第二个指针恰好指向待删除节点的前一个节点。
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* first = dummy, *second = dummy;
        for (int i = 0; i < n + 1 && first != NULL; ++i) {
            first = first->next;
        }
        while (first != NULL) {
            first = first->next;
            second = second->next;
        }
        ListNode* p = second->next;
        ListNode* post = p->next;
        delete p;
        second->next = post;
        return dummy->next;
    }
};

// 解法二：先遍历一次，找出长度。再遍历一次，删除第 (len - n + 1) 个节点。

// 解法三：栈。用栈保存之前遍历的节点，然后弹栈 n 次。