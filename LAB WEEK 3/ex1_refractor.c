//Excercise 1

#include <stdio.h>
int main(void) {
/* --- compute area and perimeter of a rectangle --- */
double width, height;
printf("Enter width: ");
fscanf(stdin, "%lf", &width);
printf("Enter height: ");
fscanf(stdin, "%lf", &height);
double area = width * height;
double perimeter = 2.0 * (width + height);
printf("Area: %.2f\n", area);
printf("Perimeter: %.2f\n", perimeter);
/* --- classify the rectangle --- */
if (width == height) {
printf("Shape: Square\n");
} else if (width > height * 2.0 || height > width * 2.0) {
printf("Shape: Elongated rectangle\n");
} else {
printf("Shape: Rectangle\n");
}
return 0;
}