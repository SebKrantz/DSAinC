/* 

Pointers are also variables and play a very important role in C programming language. 
They are used for several reasons, such as:

    Strings
    Dynamic memory allocation
    Sending function arguments by reference
    Building complicated data structures
    Pointing to functions
    Building special data structures (i.e. Tree, Tries, etc...)

And many more.

A pointer is essentially a simple integer variable which holds a memory address that points to a value, 
instead of holding the actual value itself.

The computer's memory is a sequential store of data, and a pointer points to a specific part of the memory. 
Our program can use pointers in such a way that the pointers point to a large amount of memory - 
depending on how much we decide to read from that point on.

*/

#include <stdio.h>

int main() {

    /* define a local variable a */
    int a = 1;

    /* define a pointer variable, and point it to a using the & operator */
    int * pointer_to_a = &a;

    printf("The value a is %d\n", a);
    printf("The value of a is also %d\n", *pointer_to_a);

    // We then referred to it using the dereferencing operator. We can also change the contents of the dereferenced variable:
    /* let's change the variable a */
    a += 1;

    /* we just changed the variable again! */
    *pointer_to_a += 1;

    /* will print out 3 */
    printf("The value of a is now %d\n", a);

    /* testing code */
    if (pointer_to_a != &a) return 1;
    if (*pointer_to_a != 3) return 1;

    return 0;
}