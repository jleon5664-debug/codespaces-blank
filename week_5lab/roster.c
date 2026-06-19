#include <stdio.h>
#include <string.h>
#include "roster.h"

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

void print_student(const Student *s) {
    if (s == 0) {
        printf("No Student to Print\n");
        return;
    }
    // -> operator to reach within pointer to print
    printf("[%i] %s, %s \t GPA: %.2f \t Standing: %s\n",
            s->student_id, s->last_name, s->first_name, s->gpa, grade_to_string(s->standing));
}

void print_roster(const Roster *r) {
    printf("Student Roster (%i students)\n", r->count);

    // loops through active count 
    for (int i = 0; i < r->count; i++) {
        // pass add of student at i 
        print_student(&(r->students[i]));
    }
}
