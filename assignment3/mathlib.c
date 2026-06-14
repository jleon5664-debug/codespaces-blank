#include "mathlib.h"

// inequality function
int clamp(int value, int lo, int hi) {
    // lo return value 
    if (value < lo) 
        return lo;
    // hi return value
        else if (value > hi)
            return hi; 
    // return orignal value
        else 
            return value;
        
}

// exponent function
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

// is this a prime number function
int is_prime(int n) {
    // guardrail against 0 & negative numbers
        if (n <= 1) {
        return 0;
        } 
    // loop until i^2 is > n
        for(int i = 2; i * i <= n; i++){
        if (n % i == 0) {
            // false
            return 0;
            }
        }
        return 1;
}

// gcd / euclidean algorithm
int gcd(int a, int b) {
    // absolute values
        if (a < 0) a = -a;
        if (b < 0) b = -b;
    // while loop 
        while (b != 0) {
            int var = b;
            b = a % b;
            a = var;
        }
    return a;
}

// average of an array / set of numbers
double average(int arr[], int len) {
    // prevent divsion by 0 error
        if (len <= 0) {
            return 0.0;
        }
        int sum = 0;
    // avg loop from 0 to len-1
        for (int i = 0; i < len; i++) {
            sum += arr[i];
        }
    return (double)sum / len;
}

// count digits 
int count_digits(long long n) {
    int count = 0;
    // turns negative numbers into positive
        if (n < 0) {
            n = -n;
        }
    // do-while loop to count 0 without error
        do {
            count++;
            n /= 10;
        }
        while (n > 0);
    return count;
}