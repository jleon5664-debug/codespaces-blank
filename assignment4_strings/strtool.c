  #include <stdio.h>
  #include "strlib.h"

int main() {
    int choice = 0; 
        // math menu functions  
        while (choice != 9) {
            printf("= String & Array Toolkit =\n");
            printf("1. String length\n");
            printf("2. String copy(with truncation demo)\n");
            printf("3. String compare\n");
            printf("4. Reverse a string\n");
            printf("5. Count a character\n");
            printf("6. Convert to uppercase\n");
            printf("7. Array stats (min/max/avg)\n");
            printf("8. Find value in array\n");
            printf("9. Quit\n");    
        
        scanf ("%i", &choice);
    
        // user choices functions 
        switch (choice) {
            //string length menu
            case 1: {
                    // clear \n
                    while (getchar() != '\n');
                    // retreive input
                    char user_str[256];
                    printf("Enter string: \n");

                    // reads through line and blank spaces
                    fgets(user_str, sizeof(user_str), stdin);
                    // switch \n from fgets with \0 to count accurately
                    char *next_line = user_str;
                    while (*next_line != '\0') {
                    if (*next_line == '\n') {
                        *next_line = '\0';
                        break;
                    } 
                    next_line++; 
                    }    
                int len = str_length(user_str);
                    printf("Length: %i\n",len);
                break;
            // str_copy menu
            case 2: {
                    // clear \n 
                    while (getchar() != '\n');
                    // retrieve input
                    char user_str[256];
                    printf("Enter String: \n");
                    fgets(user_str, sizeof(user_str), stdin);
                    // clean
                    char *next_line = user_str;
                    while (*next_line != '\0') {
                    if (*next_line == '\n') {
                        *next_line = '\0';
                        break;
                    }
                    next_line++;
                    }
                    // reserve 8 bytes
                    char mem_size[8];
                    str_copy(mem_size, user_str, sizeof(mem_size));
                    printf("Copied: %s\n", mem_size);
                    break;
            }
                break;
            case 9: {
                printf("Goodbye!\n");
                break;
            }
            default: {
                        printf("Invalid choice. Please choose 1-9\n");
                        break; }
            
                        return 0;} 
            }
        }
    }