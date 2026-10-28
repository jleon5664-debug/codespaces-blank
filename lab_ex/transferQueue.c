#include <stdio.h>

// queue node structs
typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct queue {
    node* front;
    node* back;
} queue;

int dequeue(queue* q) {
    // empty queue
    // no node to read at front, return
    if (q->front == NULL) return -1;
    // local pointer
    // go into queue struct pass front address
    node* temp = q->front;
    // temp goes into data & copies value into int 
    int val = temp->data; 
    // temp copies next node address into front, moving it forward
    q->front = temp->next;
    // when queue empties, move & set back node to NULL at the front
    // avoid dangling pointer
    if (q->front == NULL);
        q->back = NULL;
        // free local pointer
        free(temp);
        // return int 
        return val;
}

