#include <stdio.h>

/* Conversion constants */
const double C_TO_F_SCALE  = 9.0 / 5.0;
const double C_TO_F_OFFSET = 32.0;
const double MI_TO_KM      = 1.60934;
const double LB_TO_KG      = 0.453592;

void convert_temperature(void);
void convert_distance(void);
void convert_weight(void);
void convert_speed(void);

int get_validated_int(int min, int max, const char *prompt, const char *err);

int main(void) {
    int choice;

    do {
        printf("\n= Unit Conversion Station =\n");
        printf("1. Temperature  (Celsius <-> Fahrenheit)\n");
        printf("2. Distance     (Miles <-> Kilometers)\n");
        printf("3. Weight       (Pounds <-> Kilograms)\n");
        printf("4. Speed        (MPH <-> KPH)\n");
        printf("5. Quit\n");

        choice = get_validated_int(1, 5,
            "Enter choice (1-5): ",
            "Invalid choice. Try again.");

        switch (choice) {
            case 1: convert_temperature(); break;
            case 2: convert_distance();    break;
            case 3: convert_weight();      break;
            case 4: convert_speed();       break;
            case 5: printf("Goodbye!\n");  break;
        }

    } while (choice != 5);

    return 0;
}

/* TODO: implement the functions below */

void convert_temperature(void) {
    // Prompt whether to convert degrees Fahrenheit to Celsius or vice-versa
    // Calculate the value
    // Print the value and its unit 
};

void convert_distance(void) {
    // Prompt whether to convert Miles to Kilometers or vice-versa
    // Calculate the value
    // Print the value and its unit 
};

void convert_weight(void) {
    // Prompt whether to convert Pounds to Kilograms or vice-versa
    // Calculate the value
    // Print the value and its unit 
};

void convert_speed(void) {
    // Prompt whether to convert MPH to KPH or vice-versa
    // Calculate the value
    // Print the value and its unit 
};