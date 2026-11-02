#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 30
#define NUMSCORES 4
#define POWER 0
#define SPEED 1
#define STAMINA 2
#define TOTAL 3
#define BASECASESIZE 30

typedef struct Monster {
    char *name;
    char element[MAXSIZE + 1];
    int scores[NUMSCORES];
} Monster;

/* Required Function Prototypes */
int compareTo(Monster *m1, Monster *m2, int key);
void insertionSort(Monster **list, int low, int high, int key);
void mergeSort(Monster **list, int n, int key);
void mergeSortRec(Monster **list, int low, int high, int key);
void merge(Monster **list, int low, int mid, int high, int key);
void quickSort(Monster **list, int n, int key);
void quickSortRec(Monster **list, int low, int high, int key);
int partition(Monster **list, int low, int high, int key);

int compareTo(Monster *m1, Monster *m2, int key) {
    int s1 = *(m1->scores + key);
    int s2 = *(m2->scores + key);
    if (s1 > s2) return -1;
    if (s1 < s2) return 1;
    return strcmp(m1->name, m2->name);
}

/**
 * Pointer-Cursor Insertion Sort:
 * Walks Monster **base = list + low through Monster **limit = list + high.
 */
void insertionSort(Monster **list, int low, int high, int key) {
    Monster **base = list + low;
    Monster **limit = list + high;

    for (Monster **iPtr = base + 1; iPtr <= limit; iPtr++) {
        Monster *current = *iPtr;
        Monster **jPtr = iPtr - 1;
        while (jPtr >= base && compareTo(current, *jPtr, key) < 0) {
            *(jPtr + 1) = *jPtr;
            jPtr--;
        }
        *(jPtr + 1) = current;
    }
}

/**
 * Pointer-Cursor Merge:
 * Uses Monster **leftCur, **rightCur, and **outCur to merge adjacent slices.
 */
void merge(Monster **list, int low, int mid, int high, int key) {
    int size = high - low + 1;
    Monster **temp = (Monster **)malloc(size * sizeof(Monster *));
    if (temp == NULL) exit(EXIT_FAILURE);

    Monster **leftCur = list + low;
    Monster **leftEnd = list + mid;
    Monster **rightCur = list + mid + 1;
    Monster **rightEnd = list + high;
    Monster **outCur = temp;

    while (leftCur <= leftEnd && rightCur <= rightEnd) {
        if (compareTo(*leftCur, *rightCur, key) <= 0) {
            *outCur++ = *leftCur++;
        } else {
            *outCur++ = *rightCur++;
        }
    }

    while (leftCur <= leftEnd) {
        *outCur++ = *leftCur++;
    }

    while (rightCur <= rightEnd) {
        *outCur++ = *rightCur++;
    }

    Monster **destCur = list + low;
    Monster **tempEnd = temp + size;
    for (Monster **srcCur = temp; srcCur < tempEnd; srcCur++) {
        *destCur++ = *srcCur;
    }

    free(temp);
}

void mergeSortRec(Monster **list, int low, int high, int key) {
    if (high - low + 1 <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }

    int mid = low + (high - low) / 2;
    mergeSortRec(list, low, mid, key);
    mergeSortRec(list, mid + 1, high, key);
    merge(list, low, mid, high, key);
}

void mergeSort(Monster **list, int n, int key) {
    if (n <= 0) return;
    mergeSortRec(list, 0, n - 1, key);
}

/**
 * Pointer-Cursor Partition:
 * Uses Monster **storePtr and **scanPtr, returning pointer difference (storePtr - list).
 */
int partition(Monster **list, int low, int high, int key) {
    int pivotOffset = rand() % (high - low + 1);
    Monster **basePtr = list + low;
    Monster **pivotChoicePtr = basePtr + pivotOffset;
    Monster **endPtr = list + high;

    Monster *hold = *basePtr;
    *basePtr = *pivotChoicePtr;
    *pivotChoicePtr = hold;

    Monster *pivot = *basePtr;
    Monster **storePtr = basePtr;

    for (Monster **scanPtr = basePtr + 1; scanPtr <= endPtr; scanPtr++) {
        if (compareTo(*scanPtr, pivot, key) < 0) {
            storePtr++;
            Monster *swapTmp = *storePtr;
            *storePtr = *scanPtr;
            *scanPtr = swapTmp;
        }
    }

    *basePtr = *storePtr;
    *storePtr = pivot;

    return (int)(storePtr - list);
}

void quickSortRec(Monster **list, int low, int high, int key) {
    if (high - low + 1 <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }

    int pivotFinal = partition(list, low, high, key);
    quickSortRec(list, low, pivotFinal - 1, key);
    quickSortRec(list, pivotFinal + 1, high, key);
}

void quickSort(Monster **list, int n, int key) {
    if (n <= 0) return;
    quickSortRec(list, 0, n - 1, key);
}

int main(void) {
    srand((unsigned int)time(NULL));

    int N = 0;
    if (scanf("%d", &N) != 1 || N <= 0) {
        return 0;
    }

    Monster **overallList = (Monster **)malloc(N * sizeof(Monster *));
    Monster **speedList = (Monster **)malloc(N * sizeof(Monster *));
    if (overallList == NULL || speedList == NULL) {
        exit(EXIT_FAILURE);
    }

    char buffer[MAXSIZE + 1];
    Monster **ovCur = overallList;
    Monster **spCur = speedList;

    for (int i = 0; i < N; i++) {
        Monster *m = (Monster *)malloc(sizeof(Monster));
        if (m == NULL) exit(EXIT_FAILURE);

        scanf("%30s", buffer);
        m->name = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (m->name == NULL) exit(EXIT_FAILURE);
        strcpy(m->name, buffer);

        scanf("%30s", m->element);
        scanf("%d %d %d", m->scores + POWER, m->scores + SPEED, m->scores + STAMINA);
        *(m->scores + TOTAL) = *(m->scores + POWER) + *(m->scores + SPEED) + *(m->scores + STAMINA);

        *ovCur++ = m;
        *spCur++ = m;
    }

    mergeSort(overallList, N, TOTAL);
    quickSort(speedList, N, SPEED);

    printf("Overall Expedition Ranking\n");
    ovCur = overallList;
    for (int rank = 1; rank <= N; rank++, ovCur++) {
        printf("%d. %-15s %d\n", rank, (*ovCur)->name, *((*ovCur)->scores + TOTAL));
    }

    printf("\n");

    printf("Speed Challenge Ranking\n");
    spCur = speedList;
    for (int rank = 1; rank <= N; rank++, spCur++) {
        printf("%d. %-15s %d\n", rank, (*spCur)->name, *((*spCur)->scores + SPEED));
    }

    ovCur = overallList;
    for (int i = 0; i < N; i++, ovCur++) {
        free((*ovCur)->name);
        free(*ovCur);
    }
    free(overallList);
    free(speedList);

    return 0;
}
