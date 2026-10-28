#include <stdio.h>

//q1
int sumDigits(int n) {
    // establish base case
    if (n == 0) {
        return 0;
    }
    // return last digit
    // recursive call remaining digits
    return (n % 10) + sumDigits(n / 10);
}

//q2
int countOccurences(const char *str, char target) {
    // base case
    if (*str == '\0') {
        return 0;
    }
    // check for match 
    int match = 0;
    if (*str == target)
        match = 1;
    // recursive call 
    return match + countOccurences(str + 1, target);
}

//q3
int countWays(int n) {
    // base case: 0 steps - stop, 1 step - hop
    if (n <= 1) {
        return 1;
    }
    // recursive call
    // sum of taking step 1 or 2 
    return countways(n - 1) + countWays(n - 2);
}

//q4
int sumDiv3digits(int n) {
    // base case
    if (n <= 0) {
        return 0;
    }
    int digit = n % 10;
    int add = (digit % 3 == 0) ? digit : 0;

    // recursive call
    return add + sumDiv3digits(n / 10);
}

//q5
int maxInRange(int vals[], int low, int high) {
    if (low == high) {
        return vals[low];
    }
    int maxRest = maxInRange(vals, low + 1, high);
    return (vals[low] > maxRest) ? vals[low] : maxRest;
}

//q6
//option 1
int minimumStepsToOne(int n) {
    // base case
    if (n <= 1) {
        return 0;
    }
    // option 1: subtract 1
    int steps = 1 + minimumStepsToOne(n - 1);

//option 2
    // base case
    if (n % 2 == 0) {
        int option2 = 1 + minimumStepsToOne(n / 2);
        if (option2 < steps) {
            steps = option2;
        }
    }
// option 3
    // base case
    if (n % 3 == 0) {
        int option3 = 1 + minimumStepsToOne(n / 3);
        if (option3 < steps) {
            steps = option3;
        }
    }
    return steps;
}

// q7
// binary search w array 
int search (int numbers[], int low, int high, int value) {
    // base case 
    if (low > high) {
        return -1;
    }
    int mid = low + (high - low) / 2;

    if (numbers[mid] == value) {
        return mid;
    } else if (numbers[mid] > value) {
        return search(numbers, low, mid - 1, value);
    } else {
        return search(numbers, mid + 1, high, value);
    }
}