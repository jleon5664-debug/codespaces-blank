#include <stdio.h>
#include <string.h>

void double_value(int *n) {
    *n = *n * 2;
}

int count_vowels(char *s) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            count++;
        }
    }
    return count;
}

int main(void) {
    int x = 5;
    double_value(&x);
    printf("Doubled: %d\n", x);
// bytes
    char greeting[] = "Hello World";
    greeting[0] = 'h';

    printf("Vowels in '%s': %d\n", greeting, count_vowels(greeting));
    return 0;
} 