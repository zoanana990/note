# 61. Rotate List

Method 1, my method
1. find the length of the linked list
2. let the linked list be circular linked list
3. k = k % length
4. find the node that is a tail and a head
5. let the circular linked list be the singly linked list, and tail->next = nullptr
6. return the head

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
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr || k == 0)
            return head;
        int count = 0;
        ListNode *tmp = head, *prev = NULL;
        while(tmp) {
            count++;
            prev = tmp;
            tmp = tmp->next;
        }

        k = k % count;

        // linked the tail to head
        tmp = head;
        prev->next = head;

        for(int i = 0; i < count - k; i++) {
            prev = tmp;
            tmp = tmp->next;
        }

        prev->next = nullptr;

        return tmp;
    }
};
```

Method 2, liked rotate the array
1. reverse all linked list
2. reverse 0 ~ k node
3. reverse k ~ n node

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
    ListNode* reverse(ListNode*& head) {
        ListNode* curr = head;
        ListNode* prev = NULL;
        while (curr) {
            ListNode* forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }
        return prev;
    }
    int len(ListNode* h) {
        int l = 0;
        while (h != NULL) {
            h = h->next;
            l++;
        }
        return l;
    }
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL)
            return head;
        int n = len(head);
        if (n < k) {
            k = k % n;
        }
        if (k == 0)
            return head;
        ListNode* temp = reverse(head);
        ListNode* head2 = temp;
        ListNode* curr = temp;
        int cnt = 1;
        while (cnt < k && curr != NULL) {
            curr = curr->next;
            cnt++;
        }
        ListNode* second;
        if (curr != NULL) {
            second = curr->next;
        }
        second = reverse(second);
        if (curr != NULL)
            curr->next = NULL;
        head2 = reverse(temp);
        temp->next = second;
        return head2;
    }
};
```