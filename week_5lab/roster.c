#include <stdio.h>
#include <string.h>
#include "roster.h"

// create student
Student create_student(const char *first, const char *last, int id, double gpa) {
    Student temp;

    // copy strings into the structs
    strcpy(temp.first_name, first);
    strcpy(temp.last_name, last);

    temp.student_id = id;
    temp.gpa = gpa;

    if( gpa < 0.0 || gpa > 4.0) {
        temp.standing = GRADE_INVALID;
    } else if (gpa >= 3.5) {
        temp.standing = GRADE_A;
    } else if (gpa >= 3.0) {
        temp.standing = GRADE_B;
    } else if (gpa >= 2.0) {
        temp.standing = GRADE_C;
    } else if ( gpa >= 1.0) {
        temp.standing = GRADE_D;
    } else {
        temp.standing = GRADE_F;
    }
    return temp;
}

const char *grade_to_string(Grade g) {
    switch(g) {
        case GRADE_A: return "A";
        case GRADE_B: return "B";
        case GRADE_C: return "C";
        case GRADE_D: return "D";
        case GRADE_F: return "F";
        default:   return "Incomplete";
    }
}

// print student logic
void print_student(const Student *s) {
    if (s == 0) {
        printf("No Student to Print\n");
        return;
    }
    // combine first & last into single string full_name
    char full_name[66];
    snprintf(full_name, sizeof(full_name), "%s, %s", s->last_name, s->first_name);

    // -> operator reach within pointer & print w no gaps
    printf("[%i] %-24s GPA: %.2f Standing: %s\n",
            s->student_id, full_name, s->gpa, grade_to_string(s->standing));
}

// print roster logic 
void print_roster(const Roster *r) {

        printf("==========================================================\n");
        printf("Student Roster (%i students)\n", r->count);
        printf("==========================================================\n");

    // loops through active count 
    for (int i = 0; i < r->count; i++) {
        // pass add of student at i 
        print_student(&(r->students[i]));
    }
        printf("==========================================================\n");
        printf("Class average GPA: %.2f\n", roster_average_gpa(r));
        printf("==========================================================\n");
    
}

int roster_add(Roster *r, Student s) {
    // check if array is maxed
    if (r->count >= MAX_STUDENTS) {
        return 0;
    }
    
    // check for duplicate ID
    for (int i = 0; i < r->count; i++) {
        if (r->students[i].student_id == s.student_id) {
            return -1;
        }
    }
    
    // add student struct block to active pool
    r->students[r->count] = s;

    // increment to move student data to next block
    r->count++;

    return 1;
}

double roster_average_gpa(const Roster *r) {
    // prevent div by zero
    if (r == 0 || r->count == 0) {
        return 0.0;
    }
    
        double total_gpa = 0.0;

    // acummulate gpa
        for (int i = 0; i < r->count; i++) {
            total_gpa += r->students[i].gpa;
        }
        
    // return average
        return total_gpa / r->count;
}

int roster_remove(Roster *r, int student_id) {
    int target_index = -1;

    // search array
    for (int i = 0; i < r->count; i++) {
        if (r->students[i].student_id = student_id) {
            target_index = i;
            break;
        }
    }
    // if student doesn't exist
    if (target_index == -1) {
        return 0;
    }
    // compaction
    for (int d = target_index; d < r->count - 1; d++) {
        // shifts left 
        r->students[d] = r->students[d + 1];
    }
    // update status
        r->count--;

    return 1;
}