#include "mathlib.h"

int clamp(int value, int lo, int hi) {
    /* lo return value */
    if (value < lo) 
        return lo;
    // hi return value
        else if (value > hi)
            return hi; 
    // return orignal value
        else 
            return value;
        
}

double power(double base, int exp) {
    double result = 1.0;
    // force positive number into loop
        int iterations = exp;
        if (exp < 0){
            iterations = -exp;
        }
    // double power loop
        for (int i = 0; i < iterations; i++) {
            result *= base;
        }
    // negative exponent rule 1/ base^n
        if (exp < 0) {
            return 1.0 / result;
        }
    return result;
}

int is_prime(int n) {
    /* TODO */
    return 0;
}

int gcd(int a, int b) {
    /* TODO */
    return 0;
}

double average(int arr[], int len) {
    /* TODO */
    return 0.0;
}

int count_digits(long long n) {
    /* TODO */
    return 0;
}