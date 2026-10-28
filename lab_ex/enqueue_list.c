#include <stdio.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct queue {
    node* front;
    node* back;
} queue;

void enqueue(struct queue* q, int val) {
    // create node on heap outside of local
    // dynamically allocate
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    // check allocation
    if (temp == NULL) return;
    // local pointer goes into node struct and writes val into data
    temp->data = val;
    // local pointer goes into node struct and writes NULL into next pointer
    temp->next = NULL;

    // if  queue is empty
    // back had no value 
    if (q->back = NULL) {
        // point temp address into front pointer which is NULL, the front
        q->front = temp;
        // point temp address into back which is NULL
        // both pointers are at the first node
        q->back = temp;
        // ends enqueue function, void terminates sequence 
        return;
    } 

    // link back node next pointer to new node
    q->back->next = temp;

    // move back to node pointer to added node at the end
    q->back = temp;



}