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
    /* TODO: walk both strings simultaneously, return first difference */
    return 0;
}

void str_reverse(char *s) {
    /* TODO: swap characters from both ends toward the middle */
}

int str_count_char(const char *s, char c) {
    /* TODO */
    return 0;
}

void str_to_upper(char *s) {
    /* TODO: for each char, if 'a' <= c <= 'z', subtract 32 */
}

void array_stats(const int arr[], int len,
                 int *out_min, int *out_max, double *out_avg) {
    /* TODO: handle len <= 0 case; otherwise scan for min/max/sum */
}

int array_find(const int arr[], int len, int target) {
    /* TODO: linear scan; return index or -1 */
    return -1;
}
