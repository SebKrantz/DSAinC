/*

C Unions are essentially the same as C Structures, except that instead of containing multiple variables each with their own memory 
a Union allows for multiple names to the same variable. These names can treat the memory as different types 
(and the size of the union will be the size of the largest type, + any padding the compiler might decide to give it)

So if you wanted to be able to read a variable's memory in different ways, for example read an integer one byte at a time, 
you could have something like this:

*/

#include <stdio.h>
#include <string.h>

// Example 1: Accessing an integer's bytes using a union
void example1() {
    printf("Example 1: Accessing an integer's bytes using a union\n");

    union intParts {
        int theInt;
        char bytes[sizeof(int)];
    };

    union intParts parts;
    parts.theInt = 5968145; // Arbitrary number > 255 (1 byte)

    printf("The int is %d\n", parts.theInt);
    printf("The bytes are [%d, %d, %d, %d]\n",
           parts.bytes[0], parts.bytes[1], parts.bytes[2], parts.bytes[3]);
}

// Example 2: Tagged union to store multiple types
void example2() {
    printf("\nExample 2: Tagged union to store multiple types\n");

    struct operator {
        int type; // 0: int, 1: float, 2: double
        union {
            int intNum;
            float floatNum;
            double doubleNum;
        };
    };

    struct operator op;

    // Store an int
    op.type = 0;
    op.intNum = 352;
    printf("Stored int: %d\n", op.intNum);

    // Store a float
    op.type = 1;
    op.floatNum = 3.14f;
    printf("Stored float: %.2f\n", op.floatNum);

    // Store a double
    op.type = 2;
    op.doubleNum = 2.71828;
    printf("Stored double: %.5f\n", op.doubleNum);
}

// Example 3: Union with anonymous struct and array for dual access
void example3() {
    printf("\nExample 3: Union with anonymous struct and array for dual access\n");

    union Coins {
        struct {
            int quarter;
            int dime;
            int nickel;
            int penny;
        };
        int coins[4];
    };

    union Coins change;

    // Input coin counts
    printf("Enter the number of quarters, dimes, nickels, and pennies:\n");
    change.coins[0] = 2;
    change.coins[1] = 1;
    change.coins[2] = 1;
    change.coins[3] = 1;
    // for (int i = 0; i < 4; ++i) {
    //     scanf("%d", &change.coins[i]);
    // }

    // Display coin counts
    printf("Quarters: %d\n", change.quarter);
    printf("Dimes: %d\n", change.dime);
    printf("Nickels: %d\n", change.nickel);
    printf("Pennies: %d\n", change.penny);
}

/*
Exercise: Create a union that stores an array of 21 characters and 6 ints (6 since 21 / 4 == 5, but 5 * 4 == 20 so you need 1 more for the purpose of this exercise), 
you will set the integers to 6 given values and then print out the character array both as a series of chars and as a string.
*/  

void exercise() {

    typedef union {
        int ints[6];
        char chars[22];
    } hiddenmessage;
    
    // initializer lists like this are assigned to the first member of the union/struct!
    // There are 6 ints here so...
    hiddenmessage intCharacters = {{1853169737, 1936876900, 1684955508, 1768838432, 561213039, 0}};
  
    /* testing code */
    printf("[");
    // only go to 18 because 1 byte is for the terminating 0 and we don't print the last in the loop
    for(int i = 0; i < 19; ++i)
        printf("%c, ", intCharacters.chars[i]);
    printf("%c]\n", intCharacters.chars[19]);

    printf("%s\n", intCharacters.chars);
}

int main() {
    example1();
    example2();
    example3();
    exercise();

    return 0;
}
