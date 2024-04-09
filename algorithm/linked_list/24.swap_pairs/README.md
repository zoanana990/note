# 24. Swap pair

Original one
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == nullptr || head->next == nullptr)
            return head;
        ListNode *dummy = new ListNode(0);
        ListNode *curr = dummy;

        while(head != nullptr && head->next != nullptr) {
            curr->next = head->next;
            curr = curr->next;
            head->next = curr->next;
            curr->next = head;

            head = head->next;
            curr = curr->next;
        }

        return dummy->next;
    }
};
```

Recursion Method
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==NULL || head->next==NULL){
            return head;
        }
        ListNode* p=head;
        ListNode* q=head->next;

        p->next= swapPairs(head->next->next);
        q->next=p;
        return q;
    }
};
```