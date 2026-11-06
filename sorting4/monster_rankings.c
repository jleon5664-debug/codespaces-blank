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
 
void insertionSort(Monster **list, int low, int high, int key) {
    // i is first unsorted index
    for (int i = low + 1; i <= high; i++) {
        // Copy slot i address into local pointer
        Monster *current = list[i];
        int j = i - 1;
        // Runs condition while current ranks before list
        // Use j >= low to establish slice boundary, 0 corrupts
        while (j >= low && compareTo(current, list[j], key) < 0) {
            // Copy slot j to one slot right
            list[j + 1] = list[j];
            j--;
        }
        // Drop current into hole left by last shift
        list[j + 1] = current;
    }
}
 
void merge(Monster **list, int low, int mid, int high, int key) {
    // Element count
    int size = high - low + 1;
    // Local array pointer 
    // Alocate Monster size using address
    Monster **temp = (Monster **)malloc(size * sizeof(Monster *));
    // Ensure allocation
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
     
    int leftIndex = low;
    int rightIndex = mid + 1;
    int tempIndex = 0;
 
    // Run until one of the slices is depleted
    while (leftIndex <= mid && rightIndex <= high) {
        if (compareTo(list[leftIndex], list[rightIndex], key) <= 0) {
            // Copies left address if ranks first or ties
            temp[tempIndex++] = list[leftIndex++];
        } else {
            // Rank right index first
            temp[tempIndex++] = list[rightIndex++];
        }
    }
 
    // Copy what is leftover 
    // if right slice depleted first
    while (leftIndex <= mid) {
        temp[tempIndex++] = list[leftIndex++];
    }
    // If left slice depleted first
    while (rightIndex <= high) {
        temp[tempIndex++] = list[rightIndex++];
    }
 
    // Copy mergered order back from temp into slice
    for (int k = 0; k < tempIndex; k++) {
        // Add low to k to avoid overwriting 
        list[low + k] = temp[k];
    }
 
    free(temp);
}
 
void mergeSortRec(Monster **list, int low, int high, int key) {
    // Slice size
    int size = high - low + 1;
    // Base case
    // Sort with insertion sort if slice is 30 or less
    if (size <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
    
    // Index the last element of left half
    int mid = low + (high - low) / 2;
    // Sort left half
    mergeSortRec(list, low, mid, key);
    // Sorts right half
    mergeSortRec(list, mid + 1, high, key);
    // Combines, both slices sorted
    merge(list, low, mid, high, key);
}
 
// Wrapper, conversion b/w array and slots
void mergeSort(Monster **list, int n, int key) {
    if (n <= 0) return;

    mergeSortRec(list, 0, n - 1, key);
}

// Swap pointers within the array
void swap(Monster **list, int a, int b) {
    // Overwrites slot a
    Monster *hold = list[a];
    list[a] = list[b];
    // Saves a address
    list[b] = hold;
}
 

int partition(Monster **list, int low, int high, int key) {
    int pivotIndex = low + rand() % (high - low + 1);
    // Move selected picot into first slot of slice
    swap(list, low, pivotIndex);
    // Save pivot
    int pivotPos = low;    
 
    // Scans forward
    int left = low + 1; 
    // Scans backward from end
    int right = high; 
 
    while (left <= right) {
        // Advance left, past elements that belong on the left
        while (left <= right && compareTo(list[left], list[pivotPos], key) <= 0) {
            left++;
        }
        // Retreat right past elements that belong on the right
        // Stops on first left element or when right passes left 
        while (right >= left && compareTo(list[right], list[pivotPos], key) > 0) {
            right--;
        }
        // Both counters stopped on a misplaced element and have not crossed
        if (left < right) {
            swap(list, left, right);
        }
    }
 
    // Move saved pivot slot into right
    // Element in right into low slot
    swap(list, pivotPos, right);

    return right;
}
 
void quickSortRec(Monster **list, int low, int high, int key) {
    int size = high - low + 1;
    // Switch to insertionSort when base base <= 30
    if (size <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
    
    // Parts slice
    int pivotFinal = partition(list, low, high, key);

    quickSortRec(list, low, pivotFinal - 1, key);
    quickSortRec(list, pivotFinal + 1, high, key);
}
 
 
 // Wrapper, conversion
void quickSort(Monster **list, int n, int key) {
    if (n <= 0) return;
    quickSortRec(list, 0, n - 1, key);
}
 
// Main body, stack
int main(void) {
    // Start seed point for rand
    // Unsigned int to cast
    srand((unsigned int)time(NULL));
 
    // Read monster count into N
    int N = 0;
    if (scanf("%d", &N) != 1 || N <= 0) {
        return 0;
    }
 
    // Allocates two local pointer arrays
    Monster **overallList = (Monster **)malloc(N * sizeof(Monster *));
    Monster **speedList = (Monster **)malloc(N * sizeof(Monster *));
    // Allocation check 
    // if either null return EXIT_FAILURE
    if (overallList == NULL || speedList == NULL) {
        exit(EXIT_FAILURE);
    }
 
    // Allocate each Monster struct once 
    // Use exact-size name string + 1 for '\0'
    char buffer[MAXSIZE + 1];
    for (int i = 0; i < N; i++) {
        Monster *m = (Monster *)malloc(sizeof(Monster));
        if (m == NULL) {
            exit(EXIT_FAILURE);
        }
 
        scanf("%30s", buffer);
        // Store block address into name field 
        m->name = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (m->name == NULL) {
            exit(EXIT_FAILURE);
        }
        // Copy name into new heap block 
        strcpy(m->name, buffer);
 
        scanf("%30s", m->element);
        // Read into scores
        scanf("%d %d %d", &m->scores[POWER], &m->scores[SPEED], &m->scores[STAMINA]);
        m->scores[TOTAL] = m->scores[POWER] + m->scores[SPEED] + m->scores[STAMINA];
 
        // Store address into slot i, one Monster per input 
        overallList[i] = m;
        speedList[i] = m;
    }
 
    // Sort each pointer array independently
    mergeSort(overallList, N, TOTAL);
    quickSort(speedList, N, SPEED);
 
    // Print header, one line per slot 
    printf("Overall Expedition Ranking\n");

    for (int i = 0; i < N; i++) {
        printf("%d. %-15s %d\n", i + 1, overallList[i]->name, overallList[i]->scores[TOTAL]);
    }
 
    printf("\n");
 
    // Second header
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