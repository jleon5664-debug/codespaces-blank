#include <stdio.h>

// stack struct
typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct stack {
    node* top;
} stack;

typedef struct queue {
    stack* inbox; // stack used for enqueue operations
    stack* outbox; // stack used for dequeue operations
} queue;

int isEmpty(stack* s) { return s->top == NULL;}
int peek(stack* s) { if (s->top == NULL) return -1; return s->top->data; }

void push(stack* s, int val) {
    // create a new node w malloc
    // newnode created is local scope, terminated after function ends
    node* newNode = malloc(sizeof(node));
    // check if pointer/node is NULL before continuing
    if (newNode == NULL) return;
    // -> passes val through dereferencing (*pointer).member
    // takes val or address to right of =  
    newNode->data = val;
    // operator or s pointer goes into struct to top address then copies it into next
    // s->top points to newnode address
    newNode->next = s->top;
    s->top = newNode;
    // values on heap
}

int pop(stack* s) {
    if (s->top == NULL) return -1;
    node* temp = s->top;
    int val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}

void enqueue(queue* q, int val) {
    push(q->inbox, val);
}

int dequeue(queue* q) {
    if (isEmpty(q->outbox)) {
        while (!isEmpty(q->inbox)) {
            push(q->outbox, pop(q->inbox));
        }
    }
    if (isEmpty(q->outbox)) return -1;
    return pop(q->outbox);
}