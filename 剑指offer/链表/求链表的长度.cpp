int length(ListNode* head){
    if(head == nullptr) return 0;
    return length(head->next) + 1; // 1表示head占用一个长度
}