/*
    You previously learned what is a pointer and how to manipulate pointers. 
    In this tutorial you will be learning the arithmetic operations on pointers. 
    There are multiple arithmetic operations that can be applied on C pointers: ++, --, -, +
*/

#include <stdio.h>

// Exercise
#include <stdio.h>
	
void exercise() {
    int intarray[5] = {10,20,30,40,50};
    //-----------------------^
    int *pointer = &intarray[2];

    // Array of 3 pointers
    int *parray[3];

    // Copy last three addresses of intarray into parray
    // Use parray and pointer
    int i;
    for (i = 0; i < 3; i++) {
        parray[i] = pointer+i;
        // Insert code here
    }

    // Test code
    for (i = 0; i < 3; i++) {
        if (parray[i] == &pointer[i]) {
            printf("Matched!\n");
        } else {
            printf("Fail\n");
        }
    }
}

int main() {

    int intarray[5] = {10, 20, 30, 40, 50};
    int i;

    printf("Initial array values and addresses:\n");
    for (i = 0; i < 5; i++) {
        printf("intarray[%d] = %d at address %p\n", i, intarray[i], (void*)&intarray[i]);
    }

    // Incrementing a Pointer with ++
    int *ptr = &intarray[3]; // Point to the 4th element (index 3)
    printf("\nPointer initially points to intarray[3]: value = %d at address %p\n", *ptr, (void*)ptr);
    ptr++; // Move to the next element
    printf("After incrementing, pointer points to intarray[4]: value = %d at address %p\n", *ptr, (void*)ptr);

    // Decreasing a Pointer with --
    ptr = &intarray[4]; // Point to the 5th element (index 4)
    printf("\nPointer reset to intarray[4]: value = %d at address %p\n", *ptr, (void*)ptr);
    ptr--; // Move to the previous element
    printf("After decrementing, pointer points to intarray[3]: value = %d at address %p\n", *ptr, (void*)ptr);

    // Adding Pointers with +
    ptr = &intarray[1]; // Point to the 2nd element (index 1)
    printf("\nPointer set to intarray[1]: value = %d at address %p\n", *ptr, (void*)ptr);
    ptr += 2; // Move forward by two elements
    printf("After adding 2, pointer points to intarray[3]: value = %d at address %p\n", *ptr, (void*)ptr);

    // Subtracting Pointers with -
    ptr = &intarray[4]; // Point to the 5th element (index 4)
    printf("\nPointer set to intarray[4]: value = %d at address %p\n", *ptr, (void*)ptr);
    ptr -= 2; // Move backward by two elements
    printf("After subtracting 2, pointer points to intarray[2]: value = %d at address %p\n", *ptr, (void*)ptr);

    exercise();
    return 0;
}
