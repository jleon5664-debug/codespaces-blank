#include <stdio.h>
int celsius_to_fahrenheit_int(int c) { return c * 9 / 5 + 32; }
double celsius_to_fahrenheit(double c) { return c * 9.0 / 5.0 + 32.0; }
int fahrenheit_to_celsius_int(int f) { return (f - 32) * 5 / 9; }
double fahrenheit_to_celsius(double f) { return (f - 32.0) * 5.0 / 9.0; }
void print_conversion_table(int start, int end, int step) {
printf("%-8s %-8s\n", "C", "F");
printf("-------- --------\n");
for (int c = start; c <= end; c += step) {
printf("%-8d %-8d\n", c, celsius_to_fahrenheit_int(c));
}
}
int main(void) {
print_conversion_table(0, 100, 10);
printf("\n32F = %.2fC\n", fahrenheit_to_celsius(32.0));
printf("100C = %.2fF\n", celsius_to_fahrenheit(100.0));
return 0;
}