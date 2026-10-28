#include <stdio.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct queue {
    node* front;
    node* back;
} queue;

typedef struct ArrayQueque {
    int* array;
    int front;
    int size;
    int capacity;
} ArrayQueque;

ArrayQueque* createArrayQueue(int capacity) {
    // local pointer q
    ArrayQueque* q = malloc(sizeof(ArrayQueque));
    // allocate memory
    if (q == NULL) return NULL;
    q->array = malloc(capacity * sizeof(int));
    if (q->array == NULL) { free(q); return NULL;}
    q->front = 0;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

int enqueueArray(ArrayQueque* q, int val) {
    if (q->size == q->capacity) return 0;
    int idx = (q->front + q->size) % q->capacity;
    q->array[idx] = val;
    q->size++;
    return 1;
}

int dequeueArray(ArrayQueque* q) {
    if (q->size == 0) return -1;
    int val = q->array[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return val;
}