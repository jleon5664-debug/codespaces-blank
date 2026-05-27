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
    int hm; 
    double number, temp;
        // temp menu
    printf("\n--- Temperature ---\n");
    printf("1. Celsius -> Fahrenheit\n");
    printf("2. Fahrenheit -> Celsius\n");
    
        // enter menu choice
        hm = get_validated_int(1, 2, "C or F conversion (1 or 2): ", "Invalid direction. Try again. \n");

            // temp value input
        printf("Enter Temp: ");
        scanf("%lf", &number);
    // Calculate temp conversion
    if (hm == 1) {
            // C -> F 
        temp = (number * C_TO_F_SCALE) + C_TO_F_OFFSET;

        // Temp Format
        printf("%.2f\xc2\xb0" "C = %.2f\xc2\xb0" "F\n", number, temp);
        }
    else {
        // F -> C conversion
        temp = (number - C_TO_F_OFFSET) / (C_TO_F_SCALE);
        // Print val and unit
        printf("%.2f\xc2\xb0" "F = %.2f\xc2\xb0" "C\n", number, temp);
         }
    } 


void convert_distance(void) {
    // Declarations
    int dist_choice;
    double input_val, result_val;
    // Distance menu options
    printf("\n--- distance ---\n");
    printf("1. Miles to Kilometers\n");
    printf("2. kilometers to Miles\n");
    dist_choice = get_validated_int(1,2, "Enter direction (1 or 2): ", "Invalid direction. Try again.\n");

    // Calculate the value
    printf("Enter Distance: ");
    scanf("%lf", &input_val);

            // selection
            if (dist_choice == 1) {
                // M -> K conversion
                result_val = input_val * MI_TO_KM;
                printf("%.2f miles = %.2f km\n", input_val, result_val);
    }
    else {
            // K -> M conversion
            result_val = input_val / MI_TO_KM;
            printf("%.2f km = %.2f miles\n", input_val, result_val);
    }
}

void convert_weight(void) {
    int weight_choice;
    double user_mass, converted_mass;

    // weight menu and options 
    printf("\n--- Weight ---\n");
    printf("1. Pounds to Kilograms\n");
    printf("2. Kilograms to Pounds\n");

    weight_choice = get_validated_int(1, 2, "Enter direction (1 or 2): ", " Invalid direction. Try again.\n");

        printf("Enter weight: ");
        scanf("%lf", &user_mass);

    if (weight_choice == 1) {
        //LB -> Kg conversion
        converted_mass = user_mass * LB_TO_KG;
        printf("%.2f lbs = %.2f kg\n", user_mass, converted_mass);
    }
    else {
        // Kg -> LB conversion
        converted_mass = user_mass / LB_TO_KG;
        printf("%.2f kg = %.2f lbs\n", user_mass, converted_mass);
    }
}

void convert_speed(void) {
    int speed_choice;
    double user_speed, final_speed;

    // speed menus
        printf("\n--- Speed ---\n");
        printf("1. MPH to KPH\n");
        printf("2. KPH to MPH\n");

    // speed function
        speed_choice = get_validated_int(1, 2, "Enter direction (1 or 2): ", "Invalid direction. Try again.\n");
        
        printf("Enter speed: ");
        scanf("%lf", &user_speed);

        if (speed_choice == 1) {
            // MPH -> KPH conversion
            final_speed = user_speed * MI_TO_KM;
            printf( "%.2f mph = %.2f kph\n", user_speed, final_speed);
        }
        else { 
            // KPH -> MPH conversion
            final_speed = user_speed / MI_TO_KM;
            printf("%.2f kph = %.2f mph\n", user_speed, final_speed);
        }    
}


        // filter & exit
int get_validated_int(int min, int max, const char *prompt, const char *err) {
        int user_selection;
        int input_is_good = 0;

        do {
            // prompt parameter
            printf("%s", prompt);

            if (scanf("%d", &user_selection) == 1) {
                // the min & max parameters
                if (user_selection >= min && user_selection <= max) {
                    input_is_good = 1;
                }   else {
                    // error parameter
                    printf("%s", err);
                }
        } else {
            printf("%s", err);
            while(getchar() != '\n');
        }
    } while (input_is_good == 0);
    return user_selection;
}