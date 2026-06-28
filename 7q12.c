#include <stdlib.h>

double **make_grid(
    int rows, int cols)
{
    double **g = malloc(
        rows * sizeof(double*));   
    // terminates early if memory is full
    if (g == NULL)
        return NULL;

    int r;
    for (r = 0; r < rows; r++) {
    // clear col elements to 0.0
        g[r] = calloc(cols, sizeof(double));
        
        // decrements r before checking val 
        if (g[r] == NULL) {
            while (--r >= 0)
                free(g[r]);
            free(g);
            return NULL;
        }
    }
    return g;
}