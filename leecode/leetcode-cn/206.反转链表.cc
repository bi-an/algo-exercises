// @Athor zzg
// 递归
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr) return head;
        return helper(nullptr, head);
    }

    ListNode* helper(ListNode* pre, ListNode* head){
        ListNode* next = head->next;
        head->next = pre;
        if(next == nullptr) return head;
        return helper(head, next);
    }
};

// @Athor labuladong
// 递归
// 点评：zzg先反转，再递归，相当于循环解法；此解法反之，巧妙很多。
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;
        // 假设newHead是已经反转后的链表
        //      NULL
        //       ↑
        // 1  →  2  ←  3  ←  4
        // |                 |
        // head           newHead
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};