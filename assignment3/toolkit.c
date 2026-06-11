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
            case 1: {
                int val, lo, hi;
                printf("Enter value, lo, hi \n");
                scanf("%i %i %i", &val, &lo, &hi);
            
                int res = clamp(val, lo, hi);
                printf("clamp(%i, %i, %i) = %i\n", val, lo, hi, res);
                break;
            }
            case 7: {
                printf("Goodbye!\n");
                break;
            }
            default: {
                if (choice >= 2 && choice <= 6) {
                    printf("Option %i is not implemented yet\n", choice);
                }       else if (choice != 7)

                        printf("Invalid choice. Please choose 1-7\n");
                    break; }
                return 0;} 
            }
        }