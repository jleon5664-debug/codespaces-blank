#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define limits 
#define MAX_MONSTER 12
#define MAX_CON 100
#define MAX_STR_LEN 30
// add +1 for '\0'
#define STR_BUF_SIZE (MAX_STR_LEN + 1)

#define STR(x) #x
#define XSTR(x) STR(x)
// expand to "%30s"
#define STR_FMT '%' XSTR(MAX_STR_LEN) "s"

#define STR(x) 
#define XSTR(x) STR(x)
// expand to "%30s"
#define STR_FMT '%' XSTR(MAX_STR_LEN) "s"


typedef struct {
    char *name;
    char element[MAX_STR_LEN];
} Monster;

// constraint types
typedef enum {
    BEFORE, IMMEDIATELY_BEFORE, POSITION,
    FIRST_ELEMENT, LAST_ELEMENT, NO_ADJACENT_ELEMENT, ELEMENT_BEFORE_ALL,
    INVALID_CONSTRAINT
} ConstraintType;

typedef struct {
    ConstraintType type;
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

int positionAllows(int i, int k, int c) {
    for (int ci = 0; ci < c; ci++) {
        if (constraints[ci].type == POSITION) {
            if (constraints[ci].a == i && constraints[ci].b != k) return 0;
            if (constraints[ci].b == k && constraints[ci].a != i) return 0;
        }
    }
    return 1;
}

// return 1 on any unused mon index >=j
int recursiveHasUnusedElement(const int used[], int n, const char *element, int j) {
    if (j >= n) return 0;
    if (!used[j] && hasElement(j, element)) return 1;
    return recursiveHasUnusedElement(used, n, element, j + 1);
}

int evaluatePartial(const int perm[],const int used[], int k, int n, const Constraint *con) {
// monster placed
    int m = perm[k];
// monster before, -1 if empty
    int prev = (k > 0) ? perm[k - 1] : -1;

    switch (con->type) {
        case FIRST_ELEMENT:
            if (k == 0 && !hasElement(m, con->elementA)) return 0;
            break;
        case LAST_ELEMENT:
            if (k == n - 1 && !hasElement(m, con->elementA)) return 0;
            break;
        case BEFORE:
// place B & cond for A to come after 
            if (m == con->monsterB && !used[con->monsterA]) return 0;
            break;
        case IMMEDIATELY_BEFORE:
// B before A
            if (m == con->monsterB && prev != con->monsterA) return 0;
// A followed by wrong monster
            if (prev == con->monsterA && m != con->monsterB) return 0;
// A in last slot
            if (m == con->monsterA && k == n - 1) return 0;
            break;
        case ELEMENT_BEFORE_ALL:
// B placed while A is unused
            if (hasElement(m, con->elementB) &&
                recursiveHasUnusedElement(used, n, con->elementA, 0)) return 0;
            break;
        case POSITION:
        default:
            break;
}
    return 1;
}

int recursiveCheckAll(int perm[], int n, int c, int ci) {
    if (ci >= c) return 1;
    Constraint *con = &constraints[ci];
    switch (con->type) {
        case BEFORE:
            if (recursiveFindPos(perm, n, con->a, 0) >= recursiveFindPos(perm, n, con->b, 0)) return 0;
            break;
        case IMMEDIATELY_BEFORE:
            if (recursiveFindPos(perm, n, con->a, 0) + 1 != recursiveFindPos(perm, n, con->b, 0)) return 0;
            break;
        case POSITION:
            if (perm[con->b] != con->a) return 0;
            break;
        case FIRST_ELEMENT:
            if (strcmp(monsters[perm[0]].element, con->eA) != 0) return 0;
            break;
        case LAST_ELEMENT:
            if (strcmp(monsters[perm[n - 1]].element, con->eA) != 0) return 0;
            break;
        case NO_ADJACENT_ELEMENT:
            for (int s = 0; s < n - 1; s++) {
                if (strcmp(monsters[perm[s]].element, con->eA) == 0 &&
                    strcmp(monsters[perm[s + 1]].element, con->eA) == 0) return 0;
            }
            break;
        case ELEMENT_BEFORE_ALL: {
            int seenB = 0;
            for (int s = 0; s < n; s++) {
                if (strcmp(monsters[perm[s]].element, con->eB) == 0) seenB = 1;
                else if (strcmp(monsters[perm[s]].element, con->eA) == 0 && seenB) return 0;
            }
            break;
        }
    }
    return recursiveCheckAll(perm, n, c, ci + 1);
}

void printLineup(int perm[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s\n", monsters[perm[i]].name, monsters[perm[i]].element);
    }
}

int permute(int perm[], int used[], int k, int n, int c) {
    if (k == n) {
        if (recursiveCheckAll(perm, n, c, 0)) {
            printLineup(perm, n);
            return 1;
        }
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        if (!positionAllows(i, k, c)) continue;

        used[i] = 1;
        perm[k] = i;

        if (recursivePartialCheck(perm, used, k, n, c, 0)) {
            if (permute(perm, used, k + 1, n, c)) return 1;
        }
        used[i] = 0;
    }
    return 0;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    char temp[MAXLEN];
    for (int i = 0; i < n; i++) {
        scanf("%s %s", temp, monsters[i].element);
        monsters[i].name = (char *)malloc(strlen(temp) + 1);
        strcpy(monsters[i].name, temp);
    }

    int c;
    if (scanf("%d", &c) != 1) return 0;
    char kw[MAXLEN];
    for (int i = 0; i < c; i++) {
        scanf("%s", kw);
        if (strcmp(kw, "BEFORE") == 0) {
            constraints[i].type = BEFORE;
            scanf("%d %d", &constraints[i].a, &constraints[i].b);
        } else if (strcmp(kw, "IMMEDIATELY_BEFORE") == 0) {
            constraints[i].type = IMM_BEFORE;
            scanf("%d %d", &constraints[i].a, &constraints[i].b);
        } else if (strcmp(kw, "POSITION") == 0) {
            constraints[i].type = POSITION;
            scanf("%d %d", &constraints[i].a, &constraints[i].b);
            constraints[i].b--;
        } else if (strcmp(kw, "FIRST_ELEMENT") == 0) {
            constraints[i].type = FIRST_ELEM;
            scanf("%s", constraints[i].eA);
        } else if (strcmp(kw, "LAST_ELEMENT") == 0) {
            constraints[i].type = LAST_ELEM;
            scanf("%s", constraints[i].eA);
        } else if (strcmp(kw, "NO_ADJACENT_ELEMENT") == 0) {
            constraints[i].type = NO_ADJ_ELEM;
            scanf("%s", constraints[i].eA);
        } else if (strcmp(kw, "ELEMENT_BEFORE_ALL") == 0) {
            constraints[i].type = ELEM_BEF_ALL;
            scanf("%s %s", constraints[i].eA, constraints[i].eB);
        }
    }

    int perm[MAXN], used[MAXN] = {0};
    permute(perm, used, 0, n, c);

    for (int i = 0; i < n; i++) {
        free(monsters[i].name);
    }
    return 0;
}