// 递归
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==nullptr) return l2;
        if(l2==nullptr) return l1;
        if(l1->val > l2->val)
            swap(l1, l2); // 保证l1是最小节点
        ListNode* head = mergeTwoLists(l1->next, l2); // 返回子链表的头
        l1->next = head;
        return l1;
    }
};

// 迭代
class Solution {
public:
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