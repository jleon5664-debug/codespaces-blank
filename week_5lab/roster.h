#ifndef ROSTER_H
#define ROSTER_H

#define MAX_STUDENTS 50

typedef enum {
    GRADE_A, GRADE_B, GRADE_C, GRADE_D, GRADE_F, GRADE_INVALID
} Grade;

typedef struct {
    char   first_name[32];
    char   last_name[32];
    int    student_id;
    double gpa;
    Grade  standing;
} Student;

typedef struct {
    Student students[MAX_STUDENTS];
    int     count;
} Roster;

/* Prototypes */
Student  create_student(const char *first, const char *last,
                        int id, double gpa);
int      roster_add(Roster *r, Student s);
int      roster_remove(Roster *r, int student_id);
Student *roster_find_by_id(Roster *r, int student_id);
Student *roster_find_by_name(Roster *r, const char *last_name);
void     roster_sort_by_name(Roster *r);
void     roster_sort_by_gpa(Roster *r);
void     print_student(const Student *s);
void     print_roster(const Roster *r);
const char *grade_to_string(Grade g);
double   roster_average_gpa(const Roster *r);

#endif /* ROSTER_H */