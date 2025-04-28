/* 
By default, functions are global in C. If we declare a function with static, 
the scope of that function is reduced to the file containing it.

While static variables have scope over the file containing them making them accessible only inside a given file, 
global variables can be accessed outside the file too.
*/ 

#include <stdio.h>

static void fun(void) {
    printf("I am a static function.");
 }
 