#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define limits 
#define MAX_MONSTER 12
#define MAX_CON 100
#define MAX_STR_LEN 30
// add +1 for '\0'
#define STR_BUF_SIZE (MAX_STR_LEN + 1)

#define STR(x) 
#define XSTR(x) STR(x)
// expand to "%30s"
#define STR_FMT '%' XSTR(MAX_STR_LEN) "s"

typedef struct {
    char *name;
    char element[MAX_STR_LEN];
} Monster;

// group types
typedef enum {
    BEFORE, IMMED_BEFORE, POSITION,
    FIRST_ELEMENT, LAST_ELEMENT, NO_ADJ_ELEMENT, ELEMENT_BEFORE_A,
    INV_CONSTR
} constraintType;

typedef struct {
    constraintType type;
    int monsterA;
    int monsterB;
// conv at read time
    int position;
    char elementA[STR_BUF_SIZE];
    char elementB[STR_BUF_SIZE];
} Constraint;

Monster monsters[MAX_MONSTER];
Constraint constraints[MAX_CON];

int recursiveFindPos(int perm[], int n, int idx, int i) {
    if (i >= n) return -1;
    if (perm[i] == idx) return i;
    return recursiveFindPos(perm, n, idx, i + 1);
}

int evaluateConstraint(const int perm[], int n, const Constraint *con) {
    switch (con->type) {
        case BEFORE:
            return checkBefore(perm, n, con);
        case IMMED_BEFORE:
            return checkImmedBefore(perm, n, con);
        case POSITION:
            return perm[con->position] == con->monsterA;
        case FIRST_ELEMENT:
            return hasElementAt(perm, 0, con->elementA);
        case LAST_ELEMENT:
            return hasElementAt(perm, n - 1, con->elementA);
        case NO_ADJ_ELEMENT:
            return checkNoAdj(perm, n, con);
        case ELEMENT_BEFORE_A:
            return checkElementBeforeA(perm, n, con);
        defualt: 
            return 1;
    }
}

// linear recurs check con,
int recursiceCheckAll(const int perm[], int n, int numConstraints, int idx) {
// all passed
    if (idx == numConstraints) return 1;
// short cir, stops at fail
    if (!evaluateConstraint(perm, n, &constraints[idx])) return 0;

    return recursiceCheckAll(perm, n, numConstraints, idx + 1);
}

void printLineup(int perm[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s\n", monsters[perm[i]].name, monsters[perm[i]].element);
    }
}

int permute(int perm[], int used[], int k, int n, int c) {
    if (k == n) {
        if (recursiveValidateRange(perm, n, 0, c - 1)) {
            printLineup(perm, n);
            return 1;
        }
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            perm[k] = i;
            if (permute(perm, used, k + 1, n, c)) return 1;
            used[i] = 0;
        }
    }
    return 0;
}

// map input to con type
constraintType parseConstraintType(const char *keyword) {
    const char *names[] = { "BEFORE", "IMMED_BEFORE" , "POSITION",
                    "FIRST_ELEMENT", "LAST_ELEMENT", "NO_ADJ_ELEMENT", "ELEMENT_BEFORE_A"}; 
    
    for (int t = 0; t < INV_CONSTR; t++)
        if(strcmp(keyword, names[t]) == 0) return (constraintType)t;
    
    return INV_CONSTR;
}

void readConstraint(Constraint *con) {
    char keyword[STR_BUF_SIZE];
    scanf(STR_FMT, keyword);
    con->type = parseConstraintType(keyword);

    switch (con->type) {
        case BEFORE:
        case IMMED_BEFORE:
            scanf("%i" "%i", &con->monsterA, &con->monsterB);
            break;
        case POSITION
    }
}

void readMonster(Monster *m) {
    char nameBuf[STR_BUF_SIZE];
    scanf(STR_FMT " " STR_FMT, nameBuf, m->element);

// +1 to name for '\0'
    m->name = (char *)malloc(strlen(nameBuf) + 1);
    if (m->name == NULL) {
        printf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(m->name, nameBuf);
}

int main(void) {
    int numMonsters, numConstraints;
    int perm[MAX_MONSTER];
    int used[MAX_MONSTER] = {0};

    scanf("%i", &numMonsters);
    for (int i = 0; i < numMonsters; i++) readMonster(&monsters[i]);

    scanf("%i", &numConstraints);
    for (int i = 0; i < numConstraints; i++) readCon(&constraints[i]);

    permute(perm, used, 0, numMonsters, numConstraints);
    recursiveFreeMonsters(0, numMonsters);
    return 0;
}
