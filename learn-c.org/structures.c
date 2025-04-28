/*
C structures are special, large variables which contain several named variables inside. 
Structures are the basic foundation for objects and classes in C. Structures are used for:

    Serialization of data
    Passing multiple arguments in and out of functions through a single argument
    Data structures such as linked lists, binary trees, and more

The most basic example of structures are points, which are a single entity that contains two variables - x and y. 
Let's define a point:


struct point {
    int x;
    int y;
};

struct point p;
p.x = 10;
p.y = 5;


Typedefs allow us to define types with a different name - which can come in handy when dealing with structs and pointers. 
In this case, we'd want to get rid of the long definition of a point structure. 
We can use the following syntax to remove the struct keyword from each time we want to define a new point:


typedef struct {
    int x;
    int y;
} point;

// point p;


Structures can also hold pointers - which allows them to hold strings, or pointers to other structures as well - which is their real power. 
For example, we can define a vehicle structure in the following manner:

typedef struct {
    char * brand;
    int model;
} vehicle;

vehicle mycar;
mycar.brand = "Ford";
mycar.model = 2007;

*/

#include <stdio.h>

/* define the person struct here using the typedef syntax */

typedef struct {
    char * name;
    int age;
} person;

// Pointer to structure (declaration)
void increment_age(person * p);

int main() {

    person john;

    /* testing code */
    john.name = "John";
    john.age = 27;

    printf("%s is %d years old.\n", john.name, john.age);
    increment_age(&john);
    printf("%s is %d years old.\n", john.name, john.age);
    return 0;
}

// Modify structure by reference
void increment_age(person * p) {
    p->age++; // Or : (*p).age++;
}