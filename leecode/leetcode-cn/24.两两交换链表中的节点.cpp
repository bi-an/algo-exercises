// 迭代
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode(), *p = dummy;
        dummy->next = head;
        while (p) {
            ListNode* p1 = p->next;
            // 只有 p1->next != nullptr 才需要交换
            if (p1 && p1->next) {
                p->next = p1->next;
                p1->next = p1->next->next;
                p->next->next = p1;
            } else {
                break;
            }
            p = p1;
        }
        return dummy->next;
    }
};

// 法2：递归
// 递归本质上是拆解步骤，也就是找出迭代式。
// 函数功能是返回两两交换后的新链表。可以拆解为：前两个节点交换，再接上其他节点交换后的结果（调用一次函数即可得到）。
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // 如果链表为空或者只有1个节点，就没必要交换了
        if (head && head->next) {
            ListNode* p = head->next;
            head->next = swapPairs(p->next);
            p->next = head;
            return p;
        } else {
            return head;
        }
    }
};