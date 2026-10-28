#include <stdio.h>

// stack struct
typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct stack {
    node* top;
} stack;

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

void sortStack(stack* s) {
    stack* tempStack = createStack();
    while (!isEmpty(s)) {
        int x = pop(s);
        while (!isEmpty(tempStack) && peek(tempStack) > x) {
            push(s, pop(tempStack));
        }
        push(tempStack, x);
    }
    while (!isEmpty(tempStack)) {
        push(s, pop(tempStack));
    }
    free(tempStack);
}