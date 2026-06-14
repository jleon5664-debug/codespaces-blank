#include "mathlib.h"
#include <stdio.h>

int main() {
    int choice = 0; 
        // math menu functions  
        while (choice != 7) {
            printf("=Math Toolkit=\n");
            printf("1. Clamp a value\n");
            printf("2. Compute a power\n");
            printf("3. Prime check\n");
            printf("4. GCD\n");
            printf("5. Array average\n");
            printf("6. Count digits\n");
            printf("7. Quit\n");    
        
        scanf ("%i", &choice);
    
        // user choices functions 
        switch (choice) {
            //clamp menu
            case 1: {
                int val, lo, hi;
                    printf("Enter value, lo, hi \n");
                    scanf("%i %i %i", &val, &lo, &hi);
            
                    int res = clamp(val, lo, hi);
                    printf("clamp(%i, %i, %i) = %i\n", val, lo, hi, res);

                break;
            }
            // double power menu
            case 2: {
                // double power input menu
                double user_base;
                int user_exp;
                    printf("Enter a base and exponent: \n");
                    scanf("%lf %i", &user_base, &user_exp);
                    
                    // mathlib import function & 2 decimal format
                    double power_res = power(user_base, user_exp);
                    printf("power(%.2f, %i) = %.2f\n", user_base, user_exp, power_res);

                break;
            }
            // is_prime menu
            case 3: {
                // input menu
                int user_n;
                    printf("Enter n : \n");
                    scanf("%i", &user_n);

                    // prime or not prime output
                    if (is_prime(user_n) == 1) {
                    printf("%i is prime.\n", user_n);
                    } else {
                    printf("%i is not prime.\n", user_n);
                    }

                break;
            }
            //gcd menu
            case 4: {
                int user_a, user_b;
                    printf("Enter a and b: \n");
                    scanf("%i %i", &user_a, &user_b);
                    // gcd value from input a & b
                    int val = gcd(user_a, user_b);
                    printf("gcd(%i, %i) = %i\n", user_a, user_b, val);
                    break;
            }
            // average menu
            case 5: {
                int count;
                int numbers[100]; 
                    //len / array size
                    printf("Enter count then values: \n");
                    scanf("%i", &count);
                    //list of numbers input
                    for (int i = 0; i < count; i++) {
                    scanf("%i", &numbers[i]);
                    }
                    double avg_val = average(numbers, count);
                    printf("average = %.2f\n", avg_val);
                    break;
            }
            // count digits menu
            case 6: {
                long long user_integer;
                    // integer input
                    printf("Enter integer: \n");
                    scanf("%lli", &user_integer);
                    int digits = count_digits(user_integer);
                    // integer count return 
                    printf("%lli has %i digits.\n", user_integer, digits);
                    break;
            }
            case 7: {
                printf("Goodbye!\n");
                break;
            }
            default: {
                        printf("Invalid choice. Please choose 1-7\n");
                        break; }
            
                        return 0;} 
            }
        }