#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int n;
    char items[256];

    printf("Enter Number: \n");
    // scan
    scanf("%s", items);

    // take length
    int len = strlen(items);

    char ** inventory = malloc(sizeof(char *) *n);

    for(int i = 0; i < n; i++){

    //dynamically make space
    inventory[i] = malloc(sizeof(char) * (len +1));
    strcpy(inventory[i], items);
    }
    for(int i = 0; i < n; i++){
        printf("Item %i %s (Weight: %i)\n", i + 1, inventory[i], strlen(inventory[i]));
    }
    for(int i = 0; i < n; i++) {
        free(inventory[i]);
    }
    
    free(inventory);
    return 0;
}