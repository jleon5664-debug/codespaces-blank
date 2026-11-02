#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[32];
    int num_stops;
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* back;
    int size;
} Queue;

// Helper function to create a new queue node
Node* create_node(const char* name, int num_stops) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    strncpy(new_node->data.name, name, 31);
    new_node->data.name[31] = '\0';
    new_node->data.num_stops = num_stops;
    new_node->next = NULL;
    return new_node;
}

// Helper function to enqueue a student into the queue
void enqueue(Queue* q, const char* name, int num_stops) {
    Node* new_node = create_node(name, num_stops);
    if (q->back == NULL) {
        q->front = q->back = new_node;
    } else {
        q->back->next = new_node;
        q->back = new_node;
    }
    q->size++;
}

// FUNCTION TO IMPLEMENT
Student* dispatch_citronaut_express(Queue* q, int min_stops, int* out_count) {
    // TODO: Traverse queue to count students with num_stops > min_stops.
    
    // TODO: Allocate dynamic array of Student structs (or return NULL if count == 0).
    Student* s = malloc(sizeof(Student));
    if (s == 0) return NULL;

    // TODO: Unlink matching nodes from Queue

    // TODO: Copy student data to array, free unlinked nodes, set out_count, and return array.

    if(q->s == NULL) { return ; }

    return NULL;
}

int main(void) {
    // TEST CASE 1
    Queue q1 = {NULL, NULL, 0};

    // Queue setup: (Student Name, Num Stops)
    enqueue(&q1, "Alice", 2);
    enqueue(&q1, "Bob", 6);
    enqueue(&q1, "Charlie", 1);
    enqueue(&q1, "Diana", 8);
    enqueue(&q1, "Evan", 4);

    int count1 = 0;
    int threshold1 = 3;

    printf("=== TEST CASE 1 (Threshold > %d) ===\n", threshold1);
    printf("Initial Queue Size: %d\n", q1.size);

    Student* express1 = dispatch_citronaut_express(&q1, threshold1, &count1);

    printf("\nBoarded Express Shuttle (%d students):\n", count1);
    for (int i = 0; i < count1; i++) {
        printf("  - %s (%d stops)\n", express1[i].name, express1[i].num_stops);
    }

    printf("\nRemaining Standard Line (%d students):\n", q1.size);
    for (Node* curr = q1.front; curr != NULL; curr = curr->next) {
        printf("  - %s (%d stops)\n", curr->data.name, curr->data.num_stops);
    }
    if (q1.front)
        printf("  Front: %s\n", q1.front->data.name);
    if (q1.back)
        printf("  Back:  %s\n", q1.back->data.name);

    // Clean up Test Case 1
    free(express1);
    while (q1.front != NULL) {
        Node* temp = q1.front;
        q1.front = q1.front->next;
        free(temp);
    }

    // TEST CASE 2: Head-Removal
    Queue q2 = {NULL, NULL, 0};

    // Queue setup: First two students exceed threshold
    enqueue(&q2, "Knight_First", 10); 
    enqueue(&q2, "Knight_Second", 7); 
    enqueue(&q2, "Knight_Third", 3);  
    enqueue(&q2, "Knight_Fourth", 2); 

    int count2 = 0;
    int threshold2 = 5;

    printf("\n\n=== TEST CASE 2 (Threshold > %d) ===\n", threshold2);
    printf("Initial Queue Size: %d\n", q2.size);

    Student* express2 = dispatch_citronaut_express(&q2, threshold2, &count2);

    printf("\nBoarded Express Shuttle (%d students):\n", count2);
    for (int i = 0; i < count2; i++) {
        printf("  - %s (%d stops)\n", express2[i].name, express2[i].num_stops);
    }

    printf("\nRemaining Standard Line (%d students):\n", q2.size);
    for (Node* curr = q2.front; curr != NULL; curr = curr->next) {
        printf("  - %s (%d stops)\n", curr->data.name, curr->data.num_stops);
    }
    if (q2.front)
        printf("  New Front: %s\n", q2.front->data.name);
    if (q2.back)
        printf("  New Back:  %s\n", q2.back->data.name);

    // Clean up Test Case 2
    free(express2);
    while (q2.front != NULL) {
        Node* temp = q2.front;
        q2.front = q2.front->next;
        free(temp);
    }

    return 0;
}