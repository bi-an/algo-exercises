// 注意：公共节点指的是同一个节点，而不是值相同的节点
// 这两个链表只可能是"Y"字型，不可能是"X"字型。如：
// 3->4->5 
//		  ->6->7
//    1->2

class Solution(){
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		if (!pHead1 || !pHead2) return NULL;

		ListNode *p1 = pHead1;
		ListNode *p2 = pHead2;

		int len1 = 0, len2 = 0, diff = 0;
		// 记录两个链表的长度
		while (p1) {
			len1++;
			p1 = p1->next;
		}
		while (p2) {
			len2++;
			p2 = p2->next;
		}

		if (len1 > len2) {
			p1 = pHead1; // p1指向长度长的链表
			p2 = pHead2;
			diff = len1 - len2;
		}
		else {
			p1 = pHead2;
			p2 = pHead1;
			diff = len2 - len1;
		}
		
		for (int i = 0; i < diff; i++) {
			p1 = p1->next;
		}

		while (p1 && p2) {
			if (p1 == p2)
				break;
			p1 = p1->next;
			p2 = p2->next;
		}
		return p1;
	}
};


class Solution(){
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		if (!pHead1 || !pHead2) return NULL;

		stack<ListNode*> S1, S2;
		ListNode *p1 = pHead1, *p2 = pHead2;
		while (p1) {
			S1.push(p1);
			p1 = p1->next;
		}
		while (p2) {
			S2.push(p2);
			p2 = p2->next;
		}
		
		while (!S1.empty() && !S2.empty()) {
			if (S1.top() != S2.top()) {
				break;
			}
			p1 = S1.top(); S1.pop();
			p2 = S2.top(); S2.pop();
		}
		
		return p1;
	}

}