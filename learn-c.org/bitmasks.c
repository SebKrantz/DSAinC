/*

Bit masking is simply the process of storing data truly as bits, as opposed to storing it as chars/ints/floats. 
It is incredibly useful for storing certain types of data compactly and efficiently.

The idea for bit masking is based on boolean logic. For those not familiar, boolean logic is the manipulation of 'true' (1) and 'false' (0) 
through logical operations (that take 0s and 1s as their argument). We are concerned with the following operations:

    NOT a - the final value is the opposite of the input value (1 -> 0, 0 -> 1)
    a AND b - if both values are 1, the final value is 1, otherwise the final value is 0
    a OR b - if either value is 1, the final value is 1, otherwise the final value is 0
    a XOR b - if one value is 1 and the other value is 0, the final value is 1, otherwise the final value is 0

In computing, one of these true/false values is a bit. Primitives in C (int, float, etc) are made up of some number of bits, 
where that number is a multiple of 8. For example, an int may be at least 16 bits in size, where a char may be 8 bits. 
8 bits is typically referred to as a byte. C guarantees that certain primitives are at least some number of bytes in size. 
The introduction of stdint.h in C11 allows the programmer to specify integer types that are exactly some number of bytes, 
which is extremely useful when using masks.

Bit masks are often used when setting flags. Flags are values that can be in two states, such as 'on/off' and 'moving/stationary'.

See also C operators: https://www.tutorialspoint.com/cprogramming/c_operators.htm

*/

#include <stdio.h>
#include <assert.h>

int main() {
    unsigned char storage = 0b01000010; // Initial value: 0x42 (binary: 01000010)

    printf("Initial storage value: 0x%02X\n", storage);

    // Set bit 3 (counting from 0)
    storage |= 1 << 3; // OR operation to set bit 3
    printf("After setting bit 3: 0x%02X\n", storage);

    // Clear bit 3
    storage &= ~(1 << 3); // AND with NOT to clear bit 3
    printf("After clearing bit 3: 0x%02X\n", storage);

    // Flip bit 3
    storage ^= 1 << 3; // XOR to flip bit 3
    printf("After flipping bit 3: 0x%02X\n", storage);

    // Check bit 3
    unsigned char bit = storage & (1 << 3); // AND to check bit 3
    printf("Bit 3 is %s\n", bit ? "set" : "not set");

    // Exercise: Create a bit mask for the following flags: ON, MOVEMENT, TRANSPARENT, ALIVE, BROKEN, and EDIBLE
    const short FLAG_ON          = 1 << 0; // 1  (0x01)
    const short FLAG_MOVEMENT    = 1 << 1; // 2  (0x02)
    const short FLAG_TRANSPARENT = 1 << 2; // 4  (0x04)
    const short FLAG_ALIVE       = 1 << 3; // 8  (0x08)
    const short FLAG_BROKEN      = 1 << 4; // 16 (0x10)
    const short FLAG_EDIBLE      = 1 << 5; // 32 (0x20)

    short attributes = 0;

    /* Set the attributes ON, TRANSPARENT, and BROKEN */
    attributes |= FLAG_ON;
    attributes |= FLAG_TRANSPARENT;
    attributes |= FLAG_BROKEN;
    // possible solution(s):
    // attributes |= FLAG_ON | FLAG_TRANSPARENT | FLAG_BROKEN;
    // attributes = FLAG_ON | FLAG_TRANSPARENT | FLAG_BROKEN;
  
    assert(attributes == (FLAG_ON | FLAG_TRANSPARENT | FLAG_BROKEN));
  
    /* Modify (set/clear/toggle) so the only attributes are ON and ALIVE */
    attributes &= ~FLAG_TRANSPARENT;
    // possible: attributes ^= FLAG_TRANSPARENT;
    attributes ^= FLAG_BROKEN;
    // possible: attributes &= ~FLAG_BROKEN;
    attributes |= FLAG_ALIVE;
  
    assert(attributes == (FLAG_ON | FLAG_ALIVE));
  
    /* Check if the ALIVE flag is set */
    assert(attributes & FLAG_ALIVE);
  
    /* Check if the BROKEN flag is not set */
    assert(!(attributes & FLAG_BROKEN));
  
    /* Modify so only the EDIBLE attribute is set */
    attributes = FLAG_EDIBLE;
  
    assert(attributes == FLAG_EDIBLE);
  
    printf("Done!");
    
    return 0;
}
