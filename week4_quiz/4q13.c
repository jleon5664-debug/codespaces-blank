#include <stdio.h>

/* Fills *out_min, *out_max, and *out_avg with the minimum, maximum,
   and arithmetic mean of the len elements in arr.
   If len <= 0, set all outputs to 0 / 0.0. */
void array_stats(const int arr[], int len,
                 int *out_min, int *out_max, double *out_avg);

int main(void) {
    int a[] = {34, 12, 78, 56, 23, 91, 5};
    int b[] = {42};
    int c[] = {-10, -3, -7};

    int mn, mx; double avg;

    array_stats(a, 7, &mn, &mx, &avg);
    printf("a: min=%d  max=%d  avg=%.2f\n", mn, mx, avg);

    array_stats(b, 1, &mn, &mx, &avg);
    printf("b: min=%d  max=%d  avg=%.2f\n", mn, mx, avg);

    array_stats(c, 3, &mn, &mx, &avg);
    printf("c: min=%d  max=%d  avg=%.2f\n", mn, mx, avg);

    array_stats(NULL, 0, &mn, &mx, &avg);
    printf("empty: min=%d  max=%d  avg=%.2f\n", mn, mx, avg);

    return 0;
}

/* TODO: implement array_stats */
void array_stats(const int arr[], int len, int *out_min, int *out_max, double *out_avg) {
    // guard & terminate if values empty or invalid
    if (len <= 0 || arr == 0) {
        *out_min = 0;
        *out_max = 0;
        *out_avg = 0.0;
        return;
    }
    // track and count array from 0, total average double
    int c_min = arr[0];
    int c_max = arr[0];
    double t_avg = 0.0;

    //loop array & calc values
    for (int i = 0; i < len; i++) {
        if(arr[i] < c_min) {
            c_min = arr[i];
        }
        if (arr[i] > c_max) {
            c_max = arr[i];
        }
        t_avg += arr[i];
    }
    // return final calc to address
    *out_min = c_min;
    *out_max = c_max;
    *out_avg = t_avg / len;
}