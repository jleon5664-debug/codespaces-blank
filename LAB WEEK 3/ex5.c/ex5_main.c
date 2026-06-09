#include <stdio.h>
#include "shapes.h"
#include "shapes.h" /* intentional duplicate — simulates transitive
include */
int main(void) {
printf("Circle area (r=5): %.2f\n", circle_area(5.0));
printf("Rectangle area (3x4): %.2f\n", rectangle_area(3.0, 4.0));
return 0;
}