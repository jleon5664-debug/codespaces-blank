/* COP 3502C PA2 
    This program is written by: Jeronimo Leon*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// input limits
#define MAX_MONSTERS    12
#define MAX_CONSTRAINTS 100
// longest str name allowed
#define MAX_STR_LEN     30 
// +1 for '\0'
#define STR_BUF_SIZE    (MAX_STR_LEN + 1)  

// build scanf from MAX_STR_LEN, reads can never overflow
#define STR(x)  #x
#define XSTR(x) STR(x)
#define STR_FMT "%" XSTR(MAX_STR_LEN) "s"
 
// one monster name is dynamically allocated
typedef struct {
    char *name;
    char element[STR_BUF_SIZE];
} Monster;
 
// constraint types
typedef enum {
    BEFORE, IMMEDIATELY_BEFORE, POSITION,
    FIRST_ELEMENT, LAST_ELEMENT, NO_ADJACENT_ELEMENT, ELEMENT_BEFORE_ALL,
    INVALID_CONSTRAINT
} ConstraintType;
 
// one constraint, each type uses only the fields it needs
typedef struct {
    ConstraintType type;
    int monsterA;
    int monsterB;   
    int position; 
    char elementA[STR_BUF_SIZE];   
    char elementB[STR_BUF_SIZE];   
} Constraint;
 
// two global variables
Monster monsters[MAX_MONSTERS];
Constraint constraints[MAX_CONSTRAINTS];
 

// recursively searches perm for monster index
// return lineup position, or -1 if not found
int recursiveFindPos(const int perm[], int n, int idx, int i) {
    if (i >= n) return -1;                         
    if (perm[i] == idx) return i;                 
    return recursiveFindPos(perm, n, idx, i + 1); 
}
 
// returns 1 if the monster at lineup position pos has the given element
int hasElementAt(const int perm[], int pos, const char *element) {
    return strcmp(monsters[perm[pos]].element, element) == 0;
}
 
// returns 1 if monster A appears anywhere before monster B
int checkBefore(const int perm[], int n, const Constraint *con) {
    return recursiveFindPos(perm, n, con->monsterA, 0) <
           recursiveFindPos(perm, n, con->monsterB, 0);
}
 
// returns 1 if monster B is in slot directly after monster A
int checkImmediatelyBefore(const int perm[], int n, const Constraint *con) {
    return recursiveFindPos(perm, n, con->monsterA, 0) + 1 ==
           recursiveFindPos(perm, n, con->monsterB, 0);
}
 
// returns 0 if any two neighbouring monsters both have elementA
int checkNoAdjacent(const int perm[], int n, const Constraint *con) {
    for (int i = 0; i < n - 1; i++) {
        if (hasElementAt(perm, i, con->elementA) &&
            hasElementAt(perm, i + 1, con->elementA))
            return 0;
    }
    return 1;
}
 
// returns 0 if an elementA monster appears after any elementB monster
int checkElementBeforeAll(const int perm[], int n, const Constraint *con) {
    int seenB = 0;
    for (int i = 0; i < n; i++) {
        if (hasElementAt(perm, i, con->elementB))
            seenB = 1;
        else if (hasElementAt(perm, i, con->elementA) && seenB)
            return 0;
    }
    return 1;
}
 
// routes one constraint to the checker for its type
int evaluateConstraint(const int perm[], int n, const Constraint *con) {
    switch (con->type) {
        case BEFORE:
            return checkBefore(perm, n, con);
        case IMMEDIATELY_BEFORE:
            return checkImmediatelyBefore(perm, n, con);
        case POSITION:
            return perm[con->position] == con->monsterA;
        case FIRST_ELEMENT:
            return hasElementAt(perm, 0, con->elementA);
        case LAST_ELEMENT:
            return hasElementAt(perm, n - 1, con->elementA);
        case NO_ADJACENT_ELEMENT:
            return checkNoAdjacent(perm, n, con);
        case ELEMENT_BEFORE_ALL:
            return checkElementBeforeAll(perm, n, con);
        default:
            return 1;   
    }
}
 
// recursively checks constraints index
int recursiveCheckAll(const int perm[], int n, int numConstraints, int idx) {
    //every constraint passed
    if (idx == numConstraints) return 1;    
    
    if (!evaluateConstraint(perm, n, &constraints[idx]))
    // failed, skips rest
        return 0;
 
    return recursiveCheckAll(perm, n, numConstraints, idx + 1);
}
 
// print lineup as element name, one monster per line
void printLineup(const int perm[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s %s\n", monsters[perm[i]].name, monsters[perm[i]].element);
}
 

int permute(int perm[], int used[], int k, int n, int numConstraints) {
    // complete lineup has been built
    if (k == n) {
        if (recursiveCheckAll(perm, n, numConstraints, 0)) {
            printLineup(perm, n);
            return 1;
        }
        return 0;
    }
 
    // try every monster not yet placed at position k
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;       
            perm[k] = i;
 
            // unwind if solution found
            if (permute(perm, used, k + 1, n, numConstraints))

                return 1;
 
    // backtrack so i can be reused by other branches           
            used[i] = 0;
        }
    }
    return 0;
}
 
// maps input to its ConstraintType
ConstraintType parseConstraintType(const char *keyword) {
    const char *names[] = { "BEFORE", "IMMEDIATELY_BEFORE", "POSITION",
                            "FIRST_ELEMENT", "LAST_ELEMENT",
                            "NO_ADJACENT_ELEMENT", "ELEMENT_BEFORE_ALL" };
 
    for (int t = 0; t < INVALID_CONSTRAINT; t++) {
        if (strcmp(keyword, names[t]) == 0)
            return (ConstraintType)t;
    }
    return INVALID_CONSTRAINT;
}
 
// reads one constraint line into con
void readConstraint(Constraint *con) {
    char keyword[STR_BUF_SIZE];
    scanf(STR_FMT, keyword);
    con->type = parseConstraintType(keyword);
 
    switch (con->type) {
        // two monster indices
        case BEFORE:
        case IMMEDIATELY_BEFORE:
            scanf("%d %d", &con->monsterA, &con->monsterB);
            break;
 
        // monster index and a 1-based position
        case POSITION:
            scanf("%d %d", &con->monsterA, &con->position);
            con->position--;   // store 0-based so perm[position] indexes directly
            break;
 
        // one element
        case FIRST_ELEMENT:
        case LAST_ELEMENT:
        case NO_ADJACENT_ELEMENT:
            scanf(STR_FMT, con->elementA);
            break;
 
        // two elements
        case ELEMENT_BEFORE_ALL:
            scanf(STR_FMT " " STR_FMT, con->elementA, con->elementB);
            break;
 
        default:
            break;
    }
}
 
// reads one monster, name goes into a temporary buf
// copied into heap memory sized exactly to its len
void readMonster(Monster *m) {
    char nameBuf[STR_BUF_SIZE];
    scanf(STR_FMT " " STR_FMT, nameBuf, m->element);
 
    m->name = (char *)malloc(strlen(nameBuf) + 1);
    if (m->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(m->name, nameBuf);
}
 
// frees each dynamically allocated name
void recursiveFreeMonsters(int i, int n) {
    if (i >= n) return;
    free(monsters[i].name);
    recursiveFreeMonsters(i + 1, n);
}
 
// main: read input, search for the lineup, free memory
int main(void) {
    int numMonsters, numConstraints;
    int perm[MAX_MONSTERS]; 
    int used[MAX_MONSTERS] = {0};  
 
    scanf("%d", &numMonsters);
    for (int i = 0; i < numMonsters; i++)
        readMonster(&monsters[i]);
 
    scanf("%d", &numConstraints);
    for (int i = 0; i < numConstraints; i++)
        readConstraint(&constraints[i]);
 
    permute(perm, used, 0, numMonsters, numConstraints);
 
    recursiveFreeMonsters(0, numMonsters);
    return 0;
}
 