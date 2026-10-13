/* COP 3502C PA3
    this program is written by: Jeronimo Leon */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Monster {
// up to 50 characters + '\0'
    char name[51]; 
// up to 30 characters + '\0'
    char element[31]; 
    int level;          // roster sort key (descending)
    int hp;             // roster tie-break key; compared against minHp on release
} Monster;
 
// hold Monsters address
typedef struct Node {
    Monster* monster;
    struct Node* next;
} Node;
 
// FIFO queue, remove at front, add at back
typedef struct Queue {
    Node* front;
    Node* back;
    int size;
} Queue;
 
typedef struct WillsPC {
    // FIFO queue for storage box
    Queue* storageBox;
    // singly LL for sorted active roster
    Node* activeRosterHead;
} WillsPC;
 
// roster order, higher level first, equal level -> highest hp first
// returns 1 if a belongs before b, complete tie returns 0
static inline int goesBefore(const Monster* a, const Monster* b) {
    if (a->level != b->level) return a->level > b->level;
    return a->hp > b->hp;
}
 
// queue operations
 
// allocates an empty queue, returns NULL if malloc fails
Queue* createQueue(void) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) return NULL;
    q->front = q->back = NULL; 
    q->size = 0;
    return q;
}
 
// moves m to new node, attaches it at the back
void enqueue(Queue* q, Monster* m) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;
    // share the address, Monster is not copied
    newNode->monster = m;
    // becomes last node
    newNode->next = NULL; 
    // queue is empty, new node is the front
    if (q->back == NULL) q->front = newNode;
    // otherwise link after the current back
    else q->back->next = newNode;  
    q->back = newNode;
    q->size++;
}
 
// removes front Node, frees it, and returns its Monster
Monster* dequeue(Queue* q) {
    // empty queue, return null 
    if (!q->front) return NULL;
    Node* temp = q->front;
    // save Monster before freeing node
    Monster* m = temp->monster;
    q->front = temp->next;
    // queue becomes empty, back set to null 
    if (!q->front) q->back = NULL; 
    free(temp); 
    q->size--;
    return m;
}
 
//  Active roster
 
// inserts m in sorted order, return updated head
Node* insertRosterSorted(Node* head, Monster* m) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    newNode->monster = m;
 
    Node** curr = &head;
    // skips nodes that m does not go before, stops on the link where m belongs
    while (*curr != NULL && !goesBefore(m, (*curr)->monster)) {
        curr = &((*curr)->next);
    }
    // attach the rest of the list to the new node
    newNode->next = *curr;
    // points link at the new node 
    *curr = newNode;
    return head;
}
 
// moves the first Monster named monsterName from the roster to the back of q
// roster is unchanged if the name is not found
Node* depositBackToPC(Node* head, Queue* q, const char* monsterName) {
    Node** curr = &head;
    // stops on the matching node, or NULL
    while (*curr != NULL && strcmp((*curr)->monster->name, monsterName) != 0) {
        curr = &((*curr)->next);
    }
    if (*curr != NULL) {
        Node* doomed = *curr;
    // unlinks, skips match 
        *curr = doomed->next;
    // same monster, new queue node
        enqueue(q, doomed->monster);
     // frees roster node, not Monster
        free(doomed);
    }
// returns the updated head
    return head;
}
 
// frees every roster Monster with hp < minHp & its node
Node* releaseFainted(Node* head, int minHp, int* releasedCount) {
    Node** curr = &head;
    while (*curr != NULL) {
        if ((*curr)->monster->hp < minHp) {
            Node* doomed = *curr;
        // unlinks, *curr is the next unchecked node, no advance on removal
            *curr = doomed->next;  
        
            free(doomed->monster);   
            free(doomed); 
        // increment int instead of pointer          
            (*releasedCount)++; 
        } else {
        // keep, move on to nodes next link
            curr = &((*curr)->next);
        }
    }
    return head;
}
 
// Setup and teardown
 
// allocate PC with empty storage queue and roster
// return null if allocation fails
WillsPC* createWillsPC(void) {
    WillsPC* pc = (WillsPC*)malloc(sizeof(WillsPC));
    if (!pc) return NULL;
    pc->storageBox = createQueue();
    // queue allocation failed, undo & report null
    if (!pc->storageBox) {
        free(pc);
        return NULL;
    }
    pc->activeRosterHead = NULL;
    return pc;
}
 
// frees remaining Monsters and nodes, then the queue, then the pc
void releaseWillsPC(WillsPC* pc) {
    Monster* m = NULL;
    // dequeue frees each Node
    while ((m = dequeue(pc->storageBox)) != NULL) free(m);
    free(pc->storageBox);
    Node* cur = pc->activeRosterHead;
    while (cur) {
        // save before freeing cur
        Node* nextNode = cur->next; 
        free(cur->monster);
        free(cur);
        cur = nextNode;
    }
    // last to be freed, struct that held the other pointers
    free(pc);                        
}
 
// Display 
 
// prints one chain front-to-back, both queue & roster
static void printChain(const Node* head) {
    const Node* cur;
    if (head == NULL) {
        printf("EMPTY\n");
        return;
    }
    for (const Node* cur = head; cur != NULL; cur = cur->next) {
        // -> goes between items only, skipped after the last node
        printf("%s [Lv: %d]%s", cur->monster->name, cur->monster->level,
               cur->next ? " -> " : "");
    }
    printf("\n");
}
 
// count roster length by walking it
static int countChain(const Node* head) {
    const Node* cur;
    int count = 0;
    for (const Node* cur = head; cur != NULL; cur = cur->next) count++;
    return count;
}
 
// queue front-to-back, then roster head-to-tail
static void displayStorage(const WillsPC* pc) {
    printf("--- WILL'S PC STATUS ---\n");
    printf("Storage Box Queue (%d): ", pc->storageBox->size);
    printChain(pc->storageBox->front);
    printf("Active Roster (%d): ", countChain(pc->activeRosterHead));
    printChain(pc->activeRosterHead);
    // dashes to match header width
    printf("------------------------\n");
}
 
// Command loop, main 
 
int main(void) {
    WillsPC* pc = createWillsPC();
    if (!pc) return 1;
    char cmd[20];
    // end at LOGOFF_PC, or at end of input
    while (scanf("%19s", cmd) == 1) {    
        if (strcmp(cmd, "DEPOSIT_PC") == 0) {
            Monster* m = (Monster*)malloc(sizeof(Monster));
            // out of memory, stops reading & clean up
            if (!m) break;
            
            scanf("%50s %30s %d %d", m->name, m->element, &m->level, &m->hp);
            enqueue(pc->storageBox, m);
            printf("[EVENT] Deposited to Will's PC: %s (%s, Lv: %d, HP: %d)\n",
                   m->name, m->element, m->level, m->hp);
        } else if (strcmp(cmd, "WITHDRAW_PARTY") == 0) {
            int k = 0;
            scanf("%d", &k);
            int moved = 0;
            Monster* m;
            // moved < k tested first, so no monster is dequeued unless it will be inserted
            // if dequeue returns NULL, means the queue ran out early
            while (moved < k && (m = dequeue(pc->storageBox)) != NULL) {
                pc->activeRosterHead = insertRosterSorted(pc->activeRosterHead, m);
                moved++;
            }
            // print the number moved
            printf("[EVENT] Withdrew %d monster(s) from Will's PC to Active Roster.\n", moved);
        } else if (strcmp(cmd, "DEPOSIT_BACK") == 0) {
            char name[51];
            scanf("%50s", name);
            // depositBackToPC returns only the head, tells main nothing when match is not the head 
            // enqueues exactly once on success
            int prevSize = pc->storageBox->size;
            pc->activeRosterHead = depositBackToPC(pc->activeRosterHead, pc->storageBox, name);
            if (pc->storageBox->size > prevSize) {
                printf("[EVENT] Returned %s from Active Roster back to Will's PC.\n", name);
            } else {
                printf("[ERROR] %s is not in the Active Roster.\n", name);
            }
        } else if (strcmp(cmd, "RELEASE_FAINTED") == 0) {
            int minHp = 0;
            scanf("%d", &minHp);
            // start at 0
            int released = 0; 
            // releaseFainted only adds to this
            pc->activeRosterHead = releaseFainted(pc->activeRosterHead, minHp, &released);
            printf("[EVENT] Released %d fainted monster(s) with HP below %d.\n", released, minHp);
        } else if (strcmp(cmd, "DISPLAY_STORAGE") == 0) {
            displayStorage(pc);
        // end
        } else if (strcmp(cmd, "LOGOFF_PC") == 0) {
            // printed before freeing
            printf("[EVENT] Logged off Will's PC.\n");
            break;
        }
    }
    // frees last items left
    releaseWillsPC(pc);
    return 0;
}