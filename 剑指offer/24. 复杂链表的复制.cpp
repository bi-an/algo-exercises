/*
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，
另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。
（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
*/

/*struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
		label(x), next(NULL), random(NULL) {
	}
};

void PrintRandomList(RandomListNode* pHead);*/


// @Athor zzg
// 时间复杂度 O(n)
// 空间复杂度 O(1) 无辅助空间
class Solution {
public:
	RandomListNode* Clone(RandomListNode* pHead)
	{
		if (pHead == nullptr) return nullptr;
		RandomListNode *p = pHead;
		// 复制每个节点，每个新节点连接的原节点的后面，在下一个原链表节点的前面。
		// 即 A->A1->B->B1->C->C1...
		while (p) {
			RandomListNode *pNew = new RandomListNode(p->label);
			pNew->next = p->next;
			p->next = pNew;
			p = pNew->next;
		}
		//PrintList(pHead);
		// 解决random的指向
		p = pHead;
		while (p) {
			if(p->random) //防止越界
				p->next->random = p->random->next;
			p = p->next->next;
		}
		// 拆开链表
		p = pHead;
		RandomListNode *res = p->next;
		while (p) {
			RandomListNode *pTmp = p->next;
			p->next = pTmp->next;
			if (p->next)
				pTmp->next = p->next->next;
			p = p->next;
		}
		return res;
	}
};


// @Athor zzg
// 方法二：hash表
// 时间复杂度 O(n)
// 空间复杂度 O(n)
class Solution {
public:
	RandomListNode* Clone(RandomListNode* pHead)
	{
		if(pHead==nullptr) return nullptr;
		vector<RandomListNode*> hash1, hash2;
		RandomListNode* res=new RandomListNode(pHead->val);
		hash1.push_back(pHead->random);
		hash2.push_back(res);
		RandomListNode* p1=pHead->next, p2=res;
		while(p1){
			RandomListNode *pNew=new RandomListNode(p->val);
			p2->next=pNew;
			// hash1.push_back(p);
			// hash1.push_back(p->next);
			hash1.push_back(p->random);
			hash2.push_back(pNew);
			p1=p1->next;
			p2=pNew;
		}
		p1=res;
		for(int i=0;i<hash1.size();i++){
			p1->random=hash2[]
		}

	}
};

/*RandomListNode* ConstructRandomList(int* pHead,size_t len) {
	if (!pHead || len <= 0) return NULL;
	RandomListNode* head=new RandomListNode(pHead[0]);
	RandomListNode* p = head;
	head->label = pHead[0];
	for (size_t i = 1; i < len; i++) {
		RandomListNode* pNode = new RandomListNode(pHead[i]);
		p->next = pNode;
		p = p->next;
	}
	p = head;
	for (size_t i = 0; i < len; i++) {
		static default_random_engine e(time(0));//均匀分布随机数引擎
		static uniform_int_distribution<unsigned> u(0, len);
		unsigned int random = u(e);
		if (random == 0) p->random = NULL;
		else {
			RandomListNode* p1 = head;
			while (--random) {
				p1 = p1->next;
			}
			p->random = p1;
		}
		p = p->next;
	}
	return head;
}

void PrintRandomList(RandomListNode* pHead) {
	if (!pHead) return;
	RandomListNode* p = pHead;
	while (p) {
		cout << p->label<<" ";
		if (p->random)
			cout << p->random->label << " ";
		cout << "\n";
		p = p->next;
	}
}*/