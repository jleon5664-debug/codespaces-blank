  #include "strlib.h"

int str_length(const char *s) {
    // local track
        const char *t = s;

    //loop until null \0
        while (*t != '\0') {
            t++;
        }
    // subtract beginning address from ending address
    return t - s;
}

void str_copy(char *dst, const char *src, int dst_size) {
    // prevent memory crash
        if (dst_size <= 0){
            return;
    }
        int copied = 0;
    // loops copy until dst_size - 1 memory capacity
        while (*src != '\0' && copied < (dst_size - 1)) {
            *dst = *src;
            dst++;
            src++;
            copied++;
        }
    // close with null or \0
        *dst = '\0';
}

int str_compare(const char *a, const char *b) {
    // loops until *a ends and both equal
    while (*a != '\0' && *a == *b) {
        a++;
        b++;
    }
    // difference between at end of loop 
    return *a - *b;
}

void str_reverse(char *s) {
   // skips if empty or \0
        if (s == 0 || *s == '\0') {
            return;
        }
   // calc string length
        int len = str_length(s);
   // begin point at left & end at right
        char *left = s;
        char *right = s + len - 1;
   // reverses and ovewrites values
        while (left < right) {
            char move = *left;
            *left = *right;
            *right = move; 
    // increments left to center & decrement right towards center
        left++;
        right--;
        }
}

int str_count_char(const char *s, char c) {
    // end if nothing or zero
        if (s == 0) {
        return 0;
    }
        int count = 0;
    // walks until \0 
        while (*s != '\0') {
            if (*s == c) {
                count++;
            }
            // increment address
            s++;
        }
        return count;
}

void str_to_upper(char *s) {
    // exits if nothing or 0
    if (s == 0) {
        return;
    }
    // runs until reaching null/0
    while (*s != '\0') {
        // checks if lowercase range
        if (*s >= 'a' && *s <= 'z') {
        // change to uppercase
            *s = *s - 32;
        }
        s++;
    }
}

void array_stats(const int arr[], int len,
                 int *out_min, int *out_max, double *out_avg) {
    // terminates if 0 and negative length 
        if (len <= 0) {
            *out_min = 0;
            *out_max = 0;
            *out_avg = 0.0;
            return;
        }
    // start by derefrencing 
        int c_min = *arr;
        int c_max = *arr;
        double sum = 0.0;
        // int only track
        const int *ptr = arr;
    // loop by pointer increment
        for (int i = 0; i < len; i++) {
            if (*ptr < c_min) {
                c_min = *ptr;
            }
            if (*ptr > c_max) {
                c_max = *ptr;
            }
            sum += *ptr;
    // increment to next int
        ptr++;
        }
        *out_min = c_min;
        *out_max = c_max;
        *out_avg = sum / len;
}

int array_find(const int arr[], int len, int target) {
    //terminate if empty
    if (len <= 0 || arr == 0) {
        return -1;
    }
    const int *ptr = arr; 
    // scan loop
    for (int i = 0; i < len; i++) {
        if (*ptr == target) {
            return i;
        }
        ptr++;
    }
    return -1;
}
