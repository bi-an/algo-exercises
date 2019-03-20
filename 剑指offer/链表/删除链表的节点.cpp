/*
题目1：在O(1)时间内删除链表节点。
*/
struct ListNode {
	int val=0;
	ListNode* next=nullptr;
	ListNode(int _val=0):val(_val){}
};

//平均时间复杂度：(n-1)*O(1)+1*O(n)=O(1)
//因为头节点也可能被删除，所以要传入二级指针（为了将头节点变成nullptr）
//TODO: 实际上，还需要O(n)的时间去判断要删除的节点在链表中，
//但是在O(1)的时间里，只能把这个任务交给DeleteNode方法的调用者
void DeleteNode(ListNode** pHead, ListNode *pToBeDeleted) {
	if (pHead == nullptr || *pHead == nullptr || pToBeDeleted == nullptr) return;

	if (pToBeDeleted->next) {
		ListNode *pTemp = pToBeDeleted->next;
		pToBeDeleted->val = pTemp->val;
		pToBeDeleted->next = pTemp->next;

		delete pTemp;
		pTemp = nullptr;
	}
	else if (pToBeDeleted==*pHead) {
		delete pToBeDeleted;
		//pToBeDeleted = nullptr;
		*pHead = nullptr;
	}
	else{//删除尾节点
		//delete pToBeDeleted;
		//还要把前置节点的next置为nullptr
		ListNode *p = *pHead;
		while (p->next->next) {
			p = p->next;
		}
		p->next = nullptr;
		delete pToBeDeleted;
		//pToBeDeleted = nullptr;
	}

}

void PrintList(ListNode *pHead) {
	ListNode *p = pHead;
	printf("The list : ");
	while (p) {
		printf("%d->", p->val);
		p = p->next;
	}
	printf("NULL\n");
}

int main() {
	ListNode *pHead = new ListNode();
	ListNode *p = pHead;
	for (int i = 1; i < 10; i++) {
		ListNode *pNew = new ListNode(i);
		p->next = pNew;
		p = p->next;
	}
	PrintList(pHead);
	DeleteNode(&pHead, p);
	PrintList(pHead);
	DeleteNode(&pHead, pHead);
	PrintList(pHead);

	ListNode *pHead2 = new ListNode();
	PrintList(pHead2);
	DeleteNode(&pHead2, pHead);
	PrintList(pHead2);
	
	return 0;
}