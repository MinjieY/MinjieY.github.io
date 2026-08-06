ListNode *middleNode(ListNode *head){//求链表的中间节点 LeetCode876
    ListNode *fast,*slow; //快慢指针 
    fast=slow=head;
    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next; //快指针走两步 
        slow=slow->next;      //慢指针走一步 
    }
    return slow; //返回链表的中间节点 
}

ListNode *deleteMiddle(ListNode *head){//删除链表的中间节点 LeetCode2095
    if(head->next==NULL) //只有一个节点，删除后为空链表 
        return NULL;
    ListNode *fast,*slow,*pre; //快慢指针，pre指向slow的前一个节点 
    pre=NULL;
	fast=slow=head;
    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next; //快指针走两步 
        pre=slow; 
        slow=slow->next;      //慢指针走一步
	}
	pre->next=pre->next->next;//删除中间节点
	delete slow; 
    return head;
}

ListNode *getKthFromEnd(ListNode *head,int k){//求链表中倒数第k个节点 
    ListNode *fast,*slow;   //快慢指针 
	fast=slow=head;
    while(k--)           //快指针先走k步 
		fast=fast->next;
	while(fast!=NULL){    //快慢指针一起走 
        fast=fast->next;
        slow=slow->next;
	}
    return slow; //返回链表倒数第k个节点 
}

bool hasCycle(ListNode *head){//判断链表中是否有环 LeetCode141
    ListNode *fast,*slow;    //快慢指针 
    fast=slow=head;
    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next;//快指针走两步 
        slow=slow->next;     //慢指针走一步 
        if(fast==slow)       //快慢指针相遇，说明有环 
            return true;
    }
    return false;
}

ListNode *detectCycle(ListNode *head){//求链表中环的起点 LeetCode142
    ListNode *fast,*slow;      //快慢指针 
    fast=slow=head;
    while(fast!=NULL && fast->next!=NULL){
		fast=fast->next->next; //快指针走两步 
		slow=slow->next;       //慢指针走一步 
		if(fast==slow){        //找到环 
        	slow=head;
    		while(fast!=slow){//找环的起点 
				fast=fast->next;//快慢指针一起走 
				slow=slow->next;
			}
        	return slow;     //返回环的起点 
		}
    }
    return NULL; 
}

int lenCycle(ListNode *head){//求链表中环的长度 
    ListNode *fast,*slow;      //快慢指针 
    int len=0;
	fast=slow=head;
    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next; //快指针走两步 
        slow=slow->next;       //慢指针走一步 
        if(fast==slow){        //找到环 
            do{
				fast=fast->next->next; //快指针走两步 
        		slow=slow->next;       //慢指针走一步 
        		len++;
			}while(fast!=slow); 
        	return len;     //返回环的长度 
	    }
    }
    return 0; 
}
