#include <stdio.h>
#include <stdlib.h>

// typedef struct node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// node_create proto
Node *node_create(int data) {
    Node *n = malloc(sizeof(Node));
    if (n) {
        n->data = data;
        n->next = 0;
    }
    return n;
}

Node *insert_sorted(Node *head, int data)
{
    Node *n = node_create(data);
    if (!n) return head;

    /* Insert before head
       if list is empty or
       data is smallest */
    if (!head ||
        data <= head->data) {
        n->next = head;
        return n;
    }

    /* Find insertion point */
    Node *cur = head;
    while (cur->next != 0 && cur->next->data < data) {
        cur = cur->next;
    }

    /* Link new node in */
    n->next   = cur->next;
    cur->next = n;
    return head;
}

//test run
void print_list(Node *head) {
    while (head != 0) {
        printf("%i -> \n", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
int main() {
    Node *head = 0;

    head = insert_sorted(head, 30);
    head = insert_sorted(head, 10);
    head = insert_sorted(head, 20);
    head = insert_sorted(head, 5);

    print_list(head);

    return 0;
}