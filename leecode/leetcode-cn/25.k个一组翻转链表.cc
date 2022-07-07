class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* prev = dummy;
        while (prev) {
            // 将 [left, right] 范围内的链表翻转
            ListNode* left = prev->next, *right = left;
            // 移动 k - 1 次，则 right 恰好指向第 k 个节点
            for (int i = 0; i < k - 1 && right != nullptr; ++i)
                right = right->next;
            // 说明节点不足 k 个，不需要翻转了
            if (right == nullptr)
                break;
            // 暂存 next
            ListNode* next = right->next;
            // 将 [left, right] 子链表截断
            prev->next = nullptr;
            right->next = nullptr;
            // 翻转子链表
            reverseList(left);
            // 重新拼接
            prev->next = right;
            left->next = next;
            // 下一次循环
            prev = left;
        }
        return dummy->next;
    }

    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* p = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return p;
    }
};