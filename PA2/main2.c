#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 12
#define MAXC 100
#define MAXLEN 31

#define BEFORE 0
#define IMM_BEFORE 1
#define POSITION 2
#define FIRST_ELEM 3
#define LAST_ELEM 4
#define NO_ADJ_ELEM 5
#define ELEM_BEF_ALL 6

typedef struct {
    char *name;
    char element[MAXLEN];
} Monster;

typedef struct {
    int type;
    int a;
    int b;
    char eA[MAXLEN];
    char eB[MAXLEN];
} Constraint;

Monster monsters[MAXN];
Constraint constraints[MAXC];

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

int recursiveCheckPrefixForElement(int perm[], const char *elemB, int s, int k) {
    if (s >= k) return 0;
    if (strcmp(monsters[perm[s]].element, elemB) == 0) return 1;
    return recursiveCheckPrefixForElement(perm, elemB, s + 1, k);
}

int recursivePartialCheck(int perm[], int used[], int k, int n, int c, int ci) {
    if (ci >= c) return 1;
    Constraint *con = &constraints[ci];
    int m = perm[k];

    switch (con->type) {
        case FIRST_ELEM:
            if (k == 0 && strcmp(monsters[m].element, con->eA) != 0) return 0;
            break;
        case BEFORE:
            if (m == con->b && !used[con->a]) return 0;
            break;
        case IMM_BEFORE:
            if (m == con->b && (k == 0 || perm[k - 1] != con->a)) return 0;
            if (k > 0 && perm[k - 1] == con->a && m != con->b) return 0;
            break;
        case NO_ADJ_ELEM:
            if (k > 0 && strcmp(monsters[m].element, con->eA) == 0 &&
                strcmp(monsters[perm[k - 1]].element, con->eA) == 0) return 0;
            break;
        case ELEM_BEF_ALL:
            if (strcmp(monsters[m].element, con->eA) == 0) {
                if (recursiveCheckPrefixForElement(perm, con->eB, 0, k)) return 0;
            }
            break;
    }
    return recursivePartialCheck(perm, used, k, n, c, ci + 1);
}

int recursiveCheckAll(int perm[], int n, int c, int ci) {
    if (ci >= c) return 1;
    Constraint *con = &constraints[ci];
    switch (con->type) {
        case BEFORE:
            if (recursiveFindPos(perm, n, con->a, 0) >= recursiveFindPos(perm, n, con->b, 0)) return 0;
            break;
        case IMM_BEFORE:
            if (recursiveFindPos(perm, n, con->a, 0) + 1 != recursiveFindPos(perm, n, con->b, 0)) return 0;
            break;
        case POSITION:
            if (perm[con->b] != con->a) return 0;
            break;
        case FIRST_ELEM:
            if (strcmp(monsters[perm[0]].element, con->eA) != 0) return 0;
            break;
        case LAST_ELEM:
            if (strcmp(monsters[perm[n - 1]].element, con->eA) != 0) return 0;
            break;
        case NO_ADJ_ELEM:
            for (int s = 0; s < n - 1; s++) {
                if (strcmp(monsters[perm[s]].element, con->eA) == 0 &&
                    strcmp(monsters[perm[s + 1]].element, con->eA) == 0) return 0;
            }
            break;
        case ELEM_BEF_ALL: {
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