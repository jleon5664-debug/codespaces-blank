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

int evaluateConstraint(int perm[], int n, int ci) {
    Constraint *c = &constraints[ci];
    if (c->type == BEFORE) {
        return recursiveFindPos(perm, n, c->a, 0) < recursiveFindPos(perm, n, c->b, 0);
    } else if (c->type == IMM_BEFORE) {
        return recursiveFindPos(perm, n, c->a, 0) + 1 == recursiveFindPos(perm, n, c->b, 0);
    } else if (c->type == POSITION) {
        return perm[c->b] == c->a;
    } else if (c->type == FIRST_ELEM) {
        return strcmp(monsters[perm[0]].element, c->eA) == 0;
    } else if (c->type == LAST_ELEM) {
        return strcmp(monsters[perm[n - 1]].element, c->eA) == 0;
    } else if (c->type == NO_ADJ_ELEM) {
        for (int i = 0; i < n - 1; i++) {
            if (strcmp(monsters[perm[i]].element, c->eA) == 0 &&
                strcmp(monsters[perm[i + 1]].element, c->eA) == 0) return 0;
        }
        return 1;
    } else if (c->type == ELEM_BEF_ALL) {
        int seenB = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(monsters[perm[i]].element, c->eB) == 0) seenB = 1;
            else if (strcmp(monsters[perm[i]].element, c->eA) == 0 && seenB) return 0;
        }
        return 1;
    }
    return 1;
}

int recursiveValidateRange(int perm[], int n, int left, int right) {
    if (left > right) return 1;
    if (left == right) return evaluateConstraint(perm, n, left);
    int mid = left + (right - left) / 2;
    if (!recursiveValidateRange(perm, n, left, mid)) return 0;
    return recursiveValidateRange(perm, n, mid + 1, right);
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
