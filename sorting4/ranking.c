/* COP 3502C PA4
This program is written by: Jeronimo Leon */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Required constraints
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


int compareTo(Monster *m1, Monster *m2, int key) {
    // Larger score ranks earlier, return negative
    if (m1->scores[key] > m2->scores[key]) {
        return -1; 
    }
    // Smaller score ranks later, positive
    if (m1->scores[key] < m2->scores[key]) {
        return 1;  
    }
    // Alphabetical tie-breaker, ascending by first letter
    return strcmp(m1->name, m2->name);
}
 
 // Recursive sort slice
void insertionSort(Monster **list, int low, int high, int key) {
    // i is first unsorted index
    for (int i = low + 1; i <= high; i++) {
        // 
        Monster *current = list[i];
        int j = i - 1;
        // Runs condition while current ranks before list
        // Use j >= low to establish slice boundary
        while (j >= low && compareTo(current, list[j], key) < 0) {
            // Shift pointer right, copy bytes
            list[j + 1] = list[j];
            j--;
        }
        // Drop current into hole
        list[j + 1] = current;
    }
}
 
void merge(Monster **list, int low, int mid, int high, int key) {
    // Element count
    int size = high - low + 1;
    // Local array pointer 
    // Alocate Monster size 
    Monster **temp = (Monster **)malloc(size * sizeof(Monster *));
    // Ensure allocation
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
     
    int leftIndex = low;
    int rightIndex = mid + 1;
    int tempIndex = 0;
 
    // Run until one of the halves is depleted
    while (leftIndex <= mid && rightIndex <= high) {
        if (compareTo(list[leftIndex], list[rightIndex], key) <= 0) {
            temp[tempIndex++] = list[leftIndex++];
        } else {
            // Rank right index first
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
    // Slice size
    int size = high - low + 1;
    // Base case
    if (size <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
    
    // Last index of left half
    int mid = low + (high - low) / 2;
    // Sort left half
    mergeSortRec(list, low, mid, key);
    // Sorts right half
    mergeSortRec(list, mid + 1, high, key);
    // Combines
    merge(list, low, mid, high, key);
}
 
void mergeSort(Monster **list, int n, int key) {
    if (n <= 0) return;
    // Convert the count to bounds
    mergeSortRec(list, 0, n - 1, key);
}
 
 

void swap(Monster **list, int a, int b) {
    Monster *hold = list[a];
    list[a] = list[b];
    list[b] = hold;
}
 

int partition(Monster **list, int low, int high, int key) {
    int pivotIndex = low + rand() % (high - low + 1);
    // park the pivot at list[low]
    swap(list, low, pivotIndex);
    // where the pivot is parked
    int pivotPos = low;    
 
    // scans forward
    int left = low + 1; 
    // scans backward
    int right = high; 
 
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
 
    // Free individually to prevent double-free
    for (int i = 0; i < N; i++) {
        // free name before struct
        free(overallList[i]->name);
        free(overallList[i]);
    }
    // Free any dangling pointers
    free(overallList);
    // Then array block
    free(speedList);
 
    return 0;
}