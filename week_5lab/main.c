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
        // add roster menu 
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
        // remove student menu function
        case 2: {
                printf("Enter student ID: \n");
                scanf("%i", &input_id);
        
        // call to capture success || failure 
        int remove_result = roster_remove(&my_roster, input_id);

        // route 
            if (remove_result == 1) {
                printf("Student removed.\n");
                } else {
                printf("Student Not Found.\n");
                } 
                break;
            }
        case 3: {
                printf("Enter student ID: \n");
                scanf("%i", &input_id);

        // capture memory add
            Student *found = roster_find_by_id(&my_roster, input_id);

        // evaluate coordinate
            if (found == 0) {
                printf("Student not found.\n");
            } else {
                print_student(found);
            }
            break;
        }
        case 4: {
            printf("Enter last name: \n");
            scanf("%31s", input_last);

        // call string match
            Student *found_name = roster_find_by_name(&my_roster, input_last);

                if (found_name == 0) {
                    printf("Student not found.\n");
                } else {
                    print_student(found_name);
                }
                break;
        }
        case 5: {
            // call sorting function
                roster_sort_by_name(&my_roster);

                printf("Roster sorted by name\n");
                break;
        }
        case 6: {
            // call sort gpa 
                roster_sort_by_gpa(&my_roster);

            // notify modfication
                printf("Roster sorted by GPA.\n");
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