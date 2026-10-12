/* COP 3502C PA3
    this program is written by Jeronimo Leon */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Monster {
    char name[51];
    char element[31];
    int level;
    int hp;
} Monster;

typedef struct Node {
    Monster* monster;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* back;
    int size;
} Queue;

typedef struct WillsPC {
    Queue* storageBox;  // FIFO Queue for Will's PC Storage Box
    Node* activeRosterHead;  // Singly Linked List for sorted active roster
} WillsPC;

static inline int goesBefore(const Monster* a, const Monster* b) {
    if (a->level != b->level) return a->level > b->level;
    return a->hp > b->hp;
}

Queue* createQueue(void) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) return NULL;
    q->front = q->back = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue* q, Monster* m) {
    if (!q || !m) return;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;
    newNode->monster = m;
    newNode->next = NULL;
    
    Node** target = (q->back == NULL) ? &(q->front) : &(q->back->next);
    *target = newNode;
    q->back = newNode;
    q->size++;
}

Monster* dequeue(Queue* q) {
    if (!q || !q->front) return NULL;
    Node* temp = q->front;
    Monster* m = temp->monster;
    q->front = temp->next;
    if (!q->front) q->back = NULL;
    free(temp);
    q->size--;
    return m;
}

Node* insertRosterSorted(Node* head, Monster* m) {
    if (!m) return head;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    newNode->monster = m;
    
    Node** curr = &head;
    while (*curr != NULL && !goesBefore(m, (*curr)->monster)) {
        curr = &((*curr)->next);
    }
    newNode->next = *curr;
    *curr = newNode;
    return head;
}

Node* depositBackToPC(Node* head, Queue* q, const char* monsterName) {
    if (!head || !q || !monsterName) return head;
    Node** curr = &head;
    while (*curr != NULL && strcmp((*curr)->monster->name, monsterName) != 0) {
        curr = &((*curr)->next);
    }
    if (*curr != NULL) {
        Node* doomed = *curr;
        *curr = doomed->next;
        enqueue(q, doomed->monster);
        free(doomed);
    }
    return head;
}

Node* releaseFainted(Node* head, int minHp, int* releasedCount) {
    Node** curr = &head;
    while (*curr != NULL) {
        if ((*curr)->monster->hp < minHp) {
            Node* doomed = *curr;
            *curr = doomed->next;
            free(doomed->monster);
            free(doomed);
            (*releasedCount)++;
        } else {
            curr = &((*curr)->next);
        }
    }
    return head;
}

WillsPC* createWillsPC(void) {
    WillsPC* pc = (WillsPC*)malloc(sizeof(WillsPC));
    if (!pc) return NULL;
    pc->storageBox = createQueue();
    pc->activeRosterHead = NULL;
    return pc;
}

void releaseWillsPC(WillsPC* pc) {
    if (!pc) return;
    Monster* m = NULL;
    while ((m = dequeue(pc->storageBox)) != NULL) free(m);
    free(pc->storageBox);
    Node* cur = pc->activeRosterHead;
    while (cur) {
        Node* nextNode = cur->next;
        free(cur->monster);
        free(cur);
        cur = nextNode;
    }
    free(pc);
}

static void displayStorage(const WillsPC* pc) {
    printf("--- WILL'S PC STATUS ---\n");
    printf("Storage Box Queue (%d): ", pc->storageBox->size);
    if (!pc->storageBox->front) {
        printf("EMPTY\n");
    } else {
        for (Node* cur = pc->storageBox->front; cur != NULL; cur = cur->next) {
            printf("%s [Lv: %d]%s", cur->monster->name, cur->monster->level, cur->next ? " -> " : "");
        }
        printf("\n");
    }
    int count = 0;
    for (Node* cur = pc->activeRosterHead; cur != NULL; cur = cur->next) count++;
    printf("Active Roster (%d): ", count);
    if (!pc->activeRosterHead) {
        printf("EMPTY\n");
    } else {
        for (Node* cur = pc->activeRosterHead; cur != NULL; cur = cur->next) {
            printf("%s [Lv: %d]%s", cur->monster->name, cur->monster->level, cur->next ? " -> " : "");
        }
        printf("\n");
    }
    printf("------------------------\n");
}

int main(void) {
    WillsPC* pc = createWillsPC();
    char cmd[20];
    while (scanf("%19s", cmd) == 1) {
        if (strcmp(cmd, "DEPOSIT_PC") == 0) {
            Monster* m = (Monster*)malloc(sizeof(Monster));
            scanf("%50s %30s %d %d", m->name, m->element, &m->level, &m->hp);
            enqueue(pc->storageBox, m);
            printf("[EVENT] Deposited to Will's PC: %s (%s, Lv: %d, HP: %d)\n", m->name, m->element, m->level, m->hp);
        } else if (strcmp(cmd, "WITHDRAW_PARTY") == 0) {
            int k = 0; scanf("%d", &k);
            int moved = 0;
            while (moved < k && pc->storageBox->front != NULL) {
                Monster* m = dequeue(pc->storageBox);
                pc->activeRosterHead = insertRosterSorted(pc->activeRosterHead, m);
                moved++;
            }
            printf("[EVENT] Withdrew %d monster(s) from Will's PC to Active Roster.\n", moved);
        } else if (strcmp(cmd, "DEPOSIT_BACK") == 0) {
            char name[51]; scanf("%50s", name);
            int prevSize = pc->storageBox->size;
            pc->activeRosterHead = depositBackToPC(pc->activeRosterHead, pc->storageBox, name);
            if (pc->storageBox->size > prevSize) {
                printf("[EVENT] Returned %s from Active Roster back to Will's PC.\n", name);
            } else {
                printf("[ERROR] %s is not in the Active Roster.\n", name);
            }
        } else if (strcmp(cmd, "RELEASE_FAINTED") == 0) {
            int minHp = 0; scanf("%d", &minHp);
            int released = 0;
            pc->activeRosterHead = releaseFainted(pc->activeRosterHead, minHp, &released);
            printf("[EVENT] Released %d fainted monster(s) with HP below %d.\n", released, minHp);
        } else if (strcmp(cmd, "DISPLAY_STORAGE") == 0) {
            displayStorage(pc);
        } else if (strcmp(cmd, "LOGOFF_PC") == 0) {
            printf("[EVENT] Logged off Will's PC.\n");
            break;
        }
    }
    releaseWillsPC(pc);
    return 0;
}