/*
 * @Author: your name
 * @Date: 2021-07-24 22:31:52
 * @LastEditTime: 2021-07-24 22:34:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\138.复制带随机指针的链表.cc
 * 
 * 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

返回复制链表的头节点。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/copy-list-with-random-pointer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

// TODO 链表的问题，用递归更优雅
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        Node* p1 = head->next, *p2 = new Node(head->val), *pHead = p2;
        unordered_map<Node*,Node*> raw2new;
        raw2new.emplace(head,pHead);
        while(p1) {
            p2->next = new Node(p1->val);
            raw2new.emplace(p1, p2->next);
            p1 = p1->next;
            p2 = p2->next;
        }
        p1 = head, p2 = pHead;
        while(p1) {
            p2->random = raw2new[p1->random];
            p1 = p1->next;
            p2 = p2->next;
        }
        return pHead;
    }
};