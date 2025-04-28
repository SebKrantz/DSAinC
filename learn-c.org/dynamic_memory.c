/*
Dynamic allocation of memory is a very important subject in C. It allows building complex data structures such as linked lists. 
Allocating memory dynamically helps us to store data without initially knowing the size of the data in the time we wrote the program.

To allocate a chunk of memory dynamically, we need to have a pointer ready to store the location of the newly allocated memory. 
We can access memory that was allocated to us using that same pointer, and we can use that pointer to free the memory again, once we have finished using it.

Let's assume we want to dynamically allocate a person structure. The person is defined like this:
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char * name;
    int age;
} person;

int main() {

    person * p = malloc(2*sizeof(person));

    p[0].name = "John";
    p[0].age = 27;

    p[1].name = "Jane";
    p[1].age = 25;

    printf("%s is %d years old.\n", p[0].name, p[0].age);
    printf("%s is %d years old.\n", p[1].name, p[1].age);

    free(p);

    return 0;
}
