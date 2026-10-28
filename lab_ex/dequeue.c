#include <stdio.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct queue {
    node* front;
    node* back;
} queue;

int dequeue(struct queue* q) {
    if (q->front == NULL) return -1; 
    node* old = q->front;
    int val = old->data;
    q->front = old->next;
    if (q->front == NULL)
    q->back = NULL;
    free(old);
    return val;
    }
