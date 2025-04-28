#include <stdio.h>
#include <stdlib.h>

void example(void) {
    char vowels[] = {'A', 'E', 'I', 'O', 'U'};
    char *pvowels = vowels;
    int i;

    // Print the addresses
    for (i = 0; i < 5; i++) {
        printf("&vowels[%d]: %p, pvowels + %d: %p, vowels + %d: %p\n", i, &vowels[i], i, pvowels + i, i, vowels + i);
    }

    // Print the values
    for (i = 0; i < 5; i++) {
        printf("vowels[%d]: %c, *(pvowels + %d): %c, *(vowels + %d): %c\n", i, vowels[i], i, *(pvowels + i), i, *(vowels + i));
    }
}

/*
 By now we know that we can traverse an array using pointers. 
 Moreover, we also know that we can dynamically allocate (contiguous) memory using blocks pointers. 
 These two aspects can be combined to dynamically allocate memory for an array. 
 This is illustrated in the following code.
*/
void example2(void) {
    // Allocate memory to store five characters
    int n = 5;
    char *pvowels = (char *) malloc(n * sizeof(char));
    int i;

    pvowels[0] = 'A';
    pvowels[1] = 'E';
    *(pvowels + 2) = 'I';
    pvowels[3] = 'O';
    *(pvowels + 4) = 'U';

    for (i = 0; i < n; i++) {
        printf("%c ", pvowels[i]);
    }

    printf("\n");

    free(pvowels);
}

/*
 We conclude this tutorial by looking at dynamic memory allocation for a two-dimensional array. 
 This can be generalized to n-dimensions in a similar way. Unlike one-dimensional arrays, where we used a pointer, 
 in this case we require a pointer to a pointer, as shown below.
*/
void example3(void) {
    int nrows = 2;
    int ncols = 5;
    int i, j;

    // Allocate memory for nrows pointers
    char **pvowels = (char **) malloc(nrows * sizeof(char *));

    // For each row, allocate memory for ncols elements
    pvowels[0] = (char *) malloc(ncols * sizeof(char));
    pvowels[1] = (char *) malloc(ncols * sizeof(char));

    pvowels[0][0] = 'A';
    pvowels[0][1] = 'E';
    pvowels[0][2] = 'I';
    pvowels[0][3] = 'O';
    pvowels[0][4] = 'U';

    pvowels[1][0] = 'a';
    pvowels[1][1] = 'e';
    pvowels[1][2] = 'i';
    pvowels[1][3] = 'o';
    pvowels[1][4] = 'u';

    for (i = 0; i < nrows; i++) {
        for(j = 0; j < ncols; j++) {
            printf("%c ", pvowels[i][j]);
        }

        printf("\n");
    }

    // Free individual rows
    free(pvowels[0]);
    free(pvowels[1]);

    // Free the top-level pointer
    free(pvowels);
}

int main(void) {
    
    printf("Arrays and Pointers\n");

    printf("\nExample 1:\n\n");
    example();
    printf("\nExample 2:\n\n");
    example2();
    printf("\nExample 3:\n\n");
    example3();

    return 0;
}
