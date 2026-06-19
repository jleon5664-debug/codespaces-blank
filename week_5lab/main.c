#include <stdio.h>
  #include "roster.h"

int main() {
    int choice = 0; 
        // math menu functions  
        while (choice != 8) {
            printf("= Student Roster System =\n");
            printf("1. Add student\n");
            printf("2. Remove student (by ID)\n");
            printf("3. Find student (by ID)\n");
            printf("4. Find student (by last name)\n");
            printf("5. Sort by name\n");
            printf("6. Sort by GPA\n");
            printf("7. Print roster\n");
            printf("8. Quit\n");   
        
        scanf ("%i", &choice);

    switch (choice) {
            case 1: {
                char first[32], last[32];
                int id;
                double gpa;

                printf("First name: \n");
                // limit scanf to 31 characters
                scanf("%31s", first);
                printf("Last name: \n");
                scanf("%31s", last);
                printf("Student ID: \n");
                scanf("%i", &id);
                printf("GPA: \n");
                scanf("%lf", &gpa);

            }
            case 8: {
                printf("Goodbye!\n");
                break;
            }
    default: {
            printf("Invalid choice. Please choose 1-8\n");
            break;
    }
    }
        return 0;
        }