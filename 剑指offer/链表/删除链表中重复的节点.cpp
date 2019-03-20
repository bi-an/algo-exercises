//排序的链表，删除其重复的节点

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if (pHead == nullptr) return nullptr;
        ListNode *pPre = nullptr, *pNode = pHead;
        ListNode *pNewHead = pHead;
        while (pNode) {
            ListNode* pNext = pNode->next;
            if (pNext && pNext->val == pNode->val) {
                int value = pNode->val;
                while (pNode && pNode->val == value) {
                    pNext = pNode->next;
                    delete pNode;
                    pNode = pNext;
                }
                if (pPre == nullptr) {
                    pNewHead = pNode;
                }
                else {
                    pPre->next = pNode;
                }
                if (pNode == nullptr) {
                    break;
                }
            }
            else {
                pPre = pNode;
                pNode = pNext;
            }
        }
        return pNewHead;
    }
};