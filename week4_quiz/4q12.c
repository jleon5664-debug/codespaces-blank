#include <stdio.h>
#include <string.h>

/* Returns 1 if s is a palindrome (reads the same forward and backward),
   0 otherwise. Case-sensitive. */
int is_palindrome(const char *s);

/* Copies src into dst (up to dst_size-1 chars), converts to uppercase
   in the same pass. Always null-terminates dst. */
void copy_upper(char *dst, const char *src, int dst_size);

int main(void) {
    char words[][16] = {"racecar", "hello", "Level", "madam", "world"};
    int n = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < n; i++) {
        char upper[16];
        copy_upper(upper, words[i], sizeof(upper));
        printf("%-10s → %-10s  palindrome: %s\n",
               words[i], upper,
               is_palindrome(words[i]) ? "yes" : "no");
    }
    return 0;
}

/* TODO: implement is_palindrome */
 int is_palindrome (const char *s) {
    // sets up tracking in begin and end before \n of string
    int left = 0;
    int right = strlen(s) - 1;
    // scans both starting points moving inward 
    while (left < right) {
        if (s[left] != s[right]) {
            return 0;
        }
        right--;
        left++;
    }
    return 1;
 }

/* TODO: implement copy_upper */
void copy_upper(char *dst, const char *src, int dst_size) {
    // checks for invalid values
    if (dst_size <= 0) {
        return;
    }
    int i = 0;
    // loop copies before last value \0
    while (i < dst_size - 1 && src[i] != '\0') {
    // checks for lowercase char & converts to uppercase
    if (src[i] >= 'a' && src[i] <= 'z') {
        dst[i] = src[i] - ('a' - 'A');
    } else {
        dst[i] = src[i];
    }
    i++;
    }
    // stop before \0
    dst[i] = '\0';
}