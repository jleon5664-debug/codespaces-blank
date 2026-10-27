#include <stdio.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct stack {
    node* top;
} stack;

void push(stack* s, int val) {
    node* newNode = malloc(sizeof(node));
    if (newNode == NULL) return;
    newNode->data = val;
    s->top = newNode;
}