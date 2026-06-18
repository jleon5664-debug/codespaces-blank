#include <math.h>

#ifndef M_PI
#define M_PI 3.14159
#endif

#include "circle.h"

// area of a circle
double circle_area(double radius) {
    return M_PI * radius * radius;
}

// circle circumference 
double circle_circumference(double radius) {
    return 2 * M_PI * radius;
}