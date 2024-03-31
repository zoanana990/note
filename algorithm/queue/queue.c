#include "list.h"
#include <stdio.h>

enum {
    QUEUE_NORMAL;
    QUEUE_HEAD;
};

typedef struct {
    struct list_head node;
    int val;
    int flag;
    int count;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue *head = malloc(sizeof(MyQueue));
    head->val = -1;
    head->flag = QUEUE_HEAD;
    INIT_LIST_HEAD(&head->node);
    head->count = 0;
    return head;
}

void myQueuePush(MyQueue* obj, int x) {
    
}

int myQueuePop(MyQueue* obj) {
    
}

int myQueuePeek(MyQueue* obj) {
    
}

bool myQueueEmpty(MyQueue* obj) {
    return list_empty(&obj->node);
}

void myQueueFree(MyQueue* obj) {
    
}

int main() {

	return 0;
}
