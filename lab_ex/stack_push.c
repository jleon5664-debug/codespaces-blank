#include <stdio.h>

// stack struct
typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct stack {
    node* top;
} stack;

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