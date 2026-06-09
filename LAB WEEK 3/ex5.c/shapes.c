#include "shapes.h"
#include <math.h> /* for M_PI — link with -lm */
double circle_area(double radius) { return M_PI * radius * radius; }
double rectangle_area(double w, double h) { return w * h; }