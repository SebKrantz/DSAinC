#include <stdio.h>
#include <stdlib.h> // For qsort

// Example 1: Basic function and function pointer
void someFunction(int arg) {
    printf("This is someFunction being called and arg is: %d\n", arg);
    printf("Whoops leaving the function now!\n");
}

// Example 2: Comparison function for qsort (descending order)
int compare(const void* left, const void* right) {
    return (*(int*)right - *(int*)left);
}


void f1(int var) {
    printf("this is f1 and var is: %d\n", var);
}

void f2(int var) {
    printf("this is f2 and var is: %d\n", var);
}

void f3(int var) {
    printf("this is f3 and var is: %d\n", var);
}

void exercise() {
    
    /* define an array full of function pointers 
    to the above functions, that take an `int` as 
    their only argument */
    void (*pf[])(int) = {f1, f2, f3};

    int c = 0;
    while(c < 3) {
        pf[c](c);
        ++c;
    }
}

int main() {
    // Example 1: Using a function pointer to call a function
    void (*pf)(int); // Declare a function pointer
    pf = &someFunction; // Assign the address of someFunction to the pointer
    printf("We're about to call someFunction() using a pointer!\n");
    pf(5); // Call the function using the pointer
    printf("Wow that was cool. Back to main now!\n\n");

    // Example 2: Using function pointer with qsort
    int (*cmp)(const void*, const void*); // Declare a comparison function pointer
    cmp = &compare; // Assign the address of compare to the pointer

    int iarray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t array_size = sizeof(iarray) / sizeof(*iarray);

    // Sort the array in descending order using qsort and the comparison function
    qsort(iarray, array_size, sizeof(*iarray), cmp);

    printf("Sorted array in descending order:\n");
    for (size_t c = 0; c < array_size; c++) {
        printf("%d\t", iarray[c]);
    }
    printf("\n");

    exercise();

    return 0;
}
