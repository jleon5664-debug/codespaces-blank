#include <stdio.h>

/* Prototypes — do not modify */
int max_of_three(int a, int b, int c);
int min_of_three(int a, int b, int c);
int sum_of_digits(int n);

int main(void) {
    printf("max(3, 7, 2):      %d\n", max_of_three(3, 7, 2));
    printf("max(-1, -5, -3):   %d\n", max_of_three(-1, -5, -3));
    printf("min(3, 7, 2):      %d\n", min_of_three(3, 7, 2));
    printf("sum_of_digits(123): %d\n", sum_of_digits(123));
    printf("sum_of_digits(0):   %d\n", sum_of_digits(0));
    printf("sum_of_digits(-45): %d\n", sum_of_digits(-45));
    return 0;
}

/* TODO: implement max_of_three
   Returns the largest of three integers. */

    int max_of_three(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
   }
/* TODO: implement min_of_three
   Returns the smallest of three integers. */

   int min_of_three(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
   }
   

/* TODO: implement sum_of_digits
   Returns the sum of the decimal digits of n.
   The sign does not count. sum_of_digits(-45) == 9. */

   int sum_of_digits(int n) {
    int sum = 0;

    if (n < 0) {
        n = -n;
    }
    
    while (n > 0) {
        sum += n % 10;
        n = n / 10;
    }
        return sum;
   }