// stack_queue.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

/* Stack implemented by singly linked list (push/pop at head) */
Node *stack_top = NULL;

void push(int v) {
    Node *n = malloc(sizeof(Node)); n->val=v; n->next=stack_top; stack_top=n;
}

int pop() {
    if (!stack_top) { printf("Stack empty\n"); return -1; }
    Node *t = stack_top; int v=t->val; stack_top = t->next; free(t); return v;
}

void stack_display() {
    Node *cur = stack_top;
    printf("Stack top -> ");
    while (cur){ printf("%d ", cur->val); cur=cur->next; }
    printf("\n");
}

/* Queue implemented by linked list with head/tail */
Node *q_head = NULL, *q_tail = NULL;

void enqueue(int v) {
    Node *n = malloc(sizeof(Node)); n->val=v; n->next=NULL;
    if (!q_tail) q_head = q_tail = n;
    else { q_tail->next = n; q_tail = n; }
}

int dequeue() {
    if (!q_head) { printf("Queue empty\n"); return -1; }
    Node *t = q_head; int v=t->val; q_head = t->next; if (!q_head) q_tail=NULL; free(t); return v;
}

void queue_display() {
    Node *cur = q_head;
    printf("Queue front -> ");
    while (cur){ printf("%d ", cur->val); cur=cur->next; }
    printf("\n");
}

int main() {
    int ch, v;
    while (1) {
        printf("\n1) Push 2) Pop 3) Show Stack\n4) Enqueue 5) Dequeue 6) Show Queue\n7) Exit\nChoice: ");
        if (scanf("%d",&ch)!=1) break;
        switch(ch){
            case 1: printf("Value: "); scanf("%d",&v); push(v); break;
            case 2: v = pop(); if (v!=-1) printf("Popped %d\n", v); break;
            case 3: stack_display(); break;
            case 4: printf("Value: "); scanf("%d",&v); enqueue(v); break;
            case 5: v = dequeue(); if (v!=-1) printf("Dequeued %d\n", v); break;
            case 6: queue_display(); break;
            case 7: exit(0);
            default: printf("Invalid\n");
        }
    }
    return 0;
}
