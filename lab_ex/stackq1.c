#include <stdio.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct stack {
    node* top;
} stack;

stack* createStack(void) {
    stack* s = malloc(sizeof(stack));
    if (s == NULL) return NULL;
    return s;
}