#include <stdio.h>
  #include "roster.h"

int main(void) {

    Roster my_roster;
    my_roster.count = 0;

    char input_first[32];
    char input_last[32];
    int input_id;
    double input_gpa; 

    int choice = 0; 
        // roster menu options 
        do {
            printf("= Student Roster System =\n");
            printf("1. Add student\n");
            printf("2. Remove student (by ID)\n");
            printf("3. Find student (by ID)\n");
            printf("4. Find student (by last name)\n");
            printf("5. Sort by name\n");
            printf("6. Sort by GPA\n");
            printf("7. Print roster\n");
            printf("8. Quit\n");   
            printf("Enter choice (1-8): \n");
        
        if (scanf("%i", &choice) != 1) {
            // clears letter input from memory
            while (getchar() != '\n');
            printf("Invalid selection. Please enter 1-8.\n");
            continue;
        }

    switch (choice) {
        case 1: {
                printf("First name: \n");
                // limit scanf to 31 characters
                scanf("%31s", input_first);

                printf("Last name: \n");
                scanf("%31s", input_last);

                printf("Student ID: \n");
                scanf("%i", &input_id);

                printf("GPA: \n");
                scanf("%lf", &input_gpa);
            
            Student new_student = create_student(input_first, input_last, input_id, input_gpa);

            int result = roster_add(&my_roster, new_student);

            if (result == 1) {
                printf("Student added.\n");
            } else if (result == 0) {
                printf("Roster Full, Student Not Added\n");
            } else if (result == -1) {
                printf("ID Already Exists, Student Not Added\n");
            }
            break;
        }
        case 7:{ 
            printf("\n");
            print_roster(&my_roster);
            break;
        } 
        case 8: {
            printf("Goodbye!\n");
            break;
        }
    }
} while (choice !=8);

    return 0;
}