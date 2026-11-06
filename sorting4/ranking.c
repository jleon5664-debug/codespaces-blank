/* COP 3502C PA4
This program is written by: Jeronimo Leon */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 30
#define NUMSCORES 4
#define POWER 0
#define SPEED 1
#define STAMINA 2
#define TOTAL 3
#define BASECASESIZE 30

// Monster struct
typedef struct Monster {
    char *name;
    char element[MAXSIZE + 1];
    int scores[NUMSCORES];
} Monster;

// Prototypes 
int compareTo(Monster *m1, Monster *m2, int key);
void insertionSort(Monster **list, int low, int high, int key);
void mergeSort(Monster **list, int n, int key);
void mergeSortRec(Monster **list, int low, int high, int key);
void merge(Monster **list, int low, int mid, int high, int key);
void quickSort(Monster **list, int n, int key);
void quickSortRec(Monster **list, int low, int high, int key);
void swap(Monster **list, int a, int b);
int partition(Monster **list, int low, int high, int key);


 // Single Source of Truth for Monster Ordering
 // Returns < 0 if m1 comes before m2 larger score in 'key', or alphabetical tie-break
 // Returns > 0 if m2 comes before m1
 // Returns 0 if identical 
 
int compareTo(Monster *m1, Monster *m2, int key) {
    // Larger score ranks earlier
    if (m1->scores[key] > m2->scores[key]) {
        return -1; 
    }
    // Smaller score ranks later
    if (m1->scores[key] < m2->scores[key]) {
        return 1;  
    }
    // Alphabetical tie-breaker, ascending by first letter
    return strcmp(m1->name, m2->name);
}
 
 
 //Sorts slice list[low..high] inclusive in-place using Insertion Sort.
 //Strictly bounded by j >= low so recursive calls never bleed into adjacent slices.
 
void insertionSort(Monster **list, int low, int high, int key) {
    for (int i = low + 1; i <= high; i++) {
        Monster *current = list[i];
        int j = i - 1;
        while (j >= low && compareTo(current, list[j], key) < 0) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = current;
    }
}
 
 
 //Combines two adjacent sorted slices list[low..mid] and list[mid+1..high]
 //into a single sorted slice list[low..high] using a dynamically allocated pointer buffer.
 
void merge(Monster **list, int low, int mid, int high, int key) {
    int size = high - low + 1;
    // local pointer 
    // alocate Monster size 
    Monster **temp = (Monster **)malloc(size * sizeof(Monster *));
    // ensure allocation
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
 
    int leftIndex = low;
    int rightIndex = mid + 1;
    int tempIndex = 0;
 
    while (leftIndex <= mid && rightIndex <= high) {
        if (compareTo(list[leftIndex], list[rightIndex], key) <= 0) {
            temp[tempIndex++] = list[leftIndex++];
        } else {
            temp[tempIndex++] = list[rightIndex++];
        }
    }
 
    while (leftIndex <= mid) {
        temp[tempIndex++] = list[leftIndex++];
    }
 
    while (rightIndex <= high) {
        temp[tempIndex++] = list[rightIndex++];
    }
 
    for (int k = 0; k < tempIndex; k++) {
        list[low + k] = temp[k];
    }
 
    free(temp);
}
 
// Recursive Hybrid Merge Sort on list[low..high] 
void mergeSortRec(Monster **list, int low, int high, int key) {
    int size = high - low + 1;
    // base case
    if (size <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
 
    int mid = low + (high - low) / 2;   // same midpoint form as the lecture's MergeSort
    mergeSortRec(list, low, mid, key);
    mergeSortRec(list, mid + 1, high, key);
    merge(list, low, mid, high, key);
}
 
 //Wrapper for Merge Sort over list[0..n-1].
 
void mergeSort(Monster **list, int n, int key) {
    if (n <= 0) return;
    mergeSortRec(list, 0, n - 1, key);
}
 
 
/*
 * swap
 * Exchanges the two pointers stored at list[a] and list[b].
 * The Monster structs themselves never move.
 */
void swap(Monster **list, int a, int b) {
    Monster *hold = list[a];
    list[a] = list[b];
    list[b] = hold;
}
 
/*
 * partition  (two-counter in-place scheme from lecture)
 * Precondition:  low <= high.
 * Postcondition: the pivot sits at the returned index pivotFinal;
 *                every element in list[low..pivotFinal-1] comes before it,
 *                every element in list[pivotFinal+1..high] comes after it.
 *
 * Steps:
 *   1. pick a random index in [low, high] and swap that monster into list[low]
 *   2. left counter starts just after the pivot, right counter starts at high
 *   3. move left forward while its element comes before (or equals) the pivot
 *      move right backward while its element comes after the pivot
 *      if the counters have not crossed, both stopped on a misplaced element: swap them
 *   4. when the counters cross, right rests on the last element that comes
 *      before the pivot: swap the pivot into that slot and return it
 */
int partition(Monster **list, int low, int high, int key) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(list, low, pivotIndex);          // park the pivot at list[low]
    int pivotPos = low;                   // where the pivot is parked
 
    int left = low + 1;                   // scans forward
    int right = high;                     // scans backward
 
    while (left <= right) {
        // advance left past elements that belong on the left (come before or equal pivot)
        while (left <= right && compareTo(list[left], list[pivotPos], key) <= 0) {
            left++;
        }
        // retreat right past elements that belong on the right (come after pivot)
        while (right >= left && compareTo(list[right], list[pivotPos], key) > 0) {
            right--;
        }
        // both counters stopped on a misplaced element and have not crossed
        if (left < right) {
            swap(list, left, right);
        }
    }
 
    // right now marks the last element that comes before the pivot
    swap(list, pivotPos, right);
    return right;
}
 
// Recursive Hybrid Quick Sort over list[low..high].
// Switches to insertionSort when slice size <= BASECASESIZE (30).
 
void quickSortRec(Monster **list, int low, int high, int key) {
    int size = high - low + 1;
    // switch to insertionSort when base base <= 30
    if (size <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
 
    int pivotFinal = partition(list, low, high, key);
    quickSortRec(list, low, pivotFinal - 1, key);
    quickSortRec(list, pivotFinal + 1, high, key);
}
 
 
 // Wrapper for Quick Sort over list[0..n-1].
 
void quickSort(Monster **list, int n, int key) {
    if (n <= 0) return;
    quickSortRec(list, 0, n - 1, key);
}
 
// main body 
int main(void) {
    srand((unsigned int)time(NULL));
 
    int N = 0;
    if (scanf("%d", &N) != 1 || N <= 0) {
        return 0;
    }
 
    // allocate the two local pointer arrays
    Monster **overallList = (Monster **)malloc(N * sizeof(Monster *));
    Monster **speedList = (Monster **)malloc(N * sizeof(Monster *));
    // allocation check 
    // if either null return EXIT_FAILURE
    if (overallList == NULL || speedList == NULL) {
        exit(EXIT_FAILURE);
    }
 
    // allocate each Monster struct once 
    // use exact-size name string + 1 for '\0'
    char buffer[MAXSIZE + 1];
    for (int i = 0; i < N; i++) {
        Monster *m = (Monster *)malloc(sizeof(Monster));
        if (m == NULL) {
            exit(EXIT_FAILURE);
        }
 
        scanf("%30s", buffer);
        m->name = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (m->name == NULL) {
            exit(EXIT_FAILURE);
        }
        strcpy(m->name, buffer);
 
        scanf("%30s", m->element);
        scanf("%d %d %d", &m->scores[POWER], &m->scores[SPEED], &m->scores[STAMINA]);
        m->scores[TOTAL] = m->scores[POWER] + m->scores[SPEED] + m->scores[STAMINA];
 
        // Documented Coupling: Both pointer arrays alias the exact same Monster instance
        overallList[i] = m;
        speedList[i] = m;
    }
 
    // Sort each pointer array independently
    mergeSort(overallList, N, TOTAL);
    quickSort(speedList, N, SPEED);
 
    // Output Phase
    printf("Overall Expedition Ranking\n");
    for (int i = 0; i < N; i++) {
        printf("%d. %-15s %d\n", i + 1, overallList[i]->name, overallList[i]->scores[TOTAL]);
    }
 
    printf("\n");
 
    printf("Speed Challenge Ranking\n");
    for (int i = 0; i < N; i++) {
        printf("%d. %-15s %d\n", i + 1, speedList[i]->name, speedList[i]->scores[SPEED]);
    }
 
    // Freeing Phase 
    // Single-pass deallocation through overallList to prevent double-free
    for (int i = 0; i < N; i++) {
        free(overallList[i]->name);
        free(overallList[i]);
    }
    free(overallList);
    free(speedList);
 
    return 0;
}