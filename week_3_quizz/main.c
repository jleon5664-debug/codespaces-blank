#include <stdio.h>
#include "circle.h"

int main(void) {
    double r = 5.0;
    printf("Radius:        %.2f\n", r);
    printf("Area:          %.4f\n", circle_area(r));
    printf("Circumference: %.4f\n", circle_circumference(r));
    return 0;
}