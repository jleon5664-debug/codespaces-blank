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


