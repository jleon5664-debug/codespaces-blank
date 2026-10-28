#include <stdio.h>

// stack struct
typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct stack {
    node* top;
} stack;

int pop(stack* s) {
    if (s->top == NULL) return -1;
    node* temp = s->top;
    int val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}