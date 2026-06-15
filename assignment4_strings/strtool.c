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
            case 3: {
                //clear \n
                while (getchar() != '\n');
                //a b buckets
                char user_str1[256];
                char user_str2[256];
                printf("Enter first string: \n");
                fgets(user_str1, sizeof(user_str1), stdin);
                printf("Enter second string: \n");
                fgets(user_str2, sizeof(user_str2), stdin);
                // clean
                char *ptr1 = user_str1;
                while (*ptr1 != '\0') {
                    if (*ptr1 == '\n') {
                        *ptr1 = '\0';
                        break;
                    }
                    ptr1++;
                }
                char *ptr2 = user_str2;
                while (*ptr2 != '\0') {
                    if (*ptr2 == '\n') {
                        *ptr2 = '\0';
                        break;
                    }
                    ptr2++;
                }
                int diff = str_compare(user_str1, user_str2);
                if (diff < 0) {
                    printf("%s comes before %s\n", user_str1, user_str2);
                } else if (diff >0) {
                    printf("%s comes after %s\n", user_str1, user_str2);
                } else {
                    printf("%s equals %s\n", user_str1, user_str2);
                }
                break;
            }
            // reverse string menu
            case 4: {
                // clear \n
                while (getchar() != '\n');
                char user_str[256];
                printf("Enter string: \n");
                fgets(user_str, sizeof(user_str), stdin);
                // filter & swap \n with \0
                char *next_line = user_str;
                while (*next_line != '\0') {
                    if (*next_line == '\n') {
                        *next_line = '\0';
                        break;
                    }
                    next_line++;
                }
                // process reversal
                str_reverse(user_str);
                printf("Reversed: %s\n", user_str);
                break;
            }
            // string count char menu
            case 5: {
                // clear \n
                while (getchar() != '\n');
                // read input
                char user_str[256];
                printf("Enter string: \n");
                fgets(user_str, sizeof(user_str), stdin);
                // filter \n 
                char *next_line = user_str;
                while (*next_line != '\0') {
                    if (*next_line == '\n') {
                        *next_line = '\0';
                        break;
                    }
                    next_line++;
                }
                char type_char;
                printf("Enter character: \n");
                scanf(" %c", &type_char);
                //funct process
                int count = str_count_char(user_str, type_char);
                printf("Count: %i\n", count);
                break;
            }
            case 6: {
                // clear \n
                while (getchar() != '\n');
                //input
                int count;
                char user_str[256];
                printf("Enter string: \n");
                fgets(user_str, sizeof(user_str), stdin);
                //filter \n
                char *next_line = user_str;
                while (*next_line != '\0') {
                    if (*next_line == '\n') {
                        *next_line = '\0';
                        break;
                    }
                    next_line++;
                }
                str_to_upper(user_str);
                printf("Upper: %s\n", user_str);
                break;
            }
            case 7: {
                // clear \n
                while (getchar() != '\n');
                //input
                int count;
                printf("Enter count then values: \n");
                if (scanf("%i", count) != 1 || count <= 0) {
                    break;
                }
                // decllare size
                int val[count];
                for (int i = 0; i < count; i++) {
                    scanf("%i", val + i);
                }
                int min_out = 0;
                int max_out = 0;
                double avg_out = 0.0;
                array_stats(val, count, &min_out, &max_out, &avg_out);
                printf("min=%i max=%i avg=%.2f\n", min_out, max_out, avg_out);
                break;
            }
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