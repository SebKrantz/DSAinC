#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValid(char* s) {
    int length = strlen(s);
    char* stack = malloc(length * sizeof(char));
    int top = -1;
    for(int i = 0; i < length; ++i) {
        char si = s[i];
        // Need to use single quotes for char, double quotes for string
        if(si == '(' || si == '[' || si == '{') 
            stack[++top] = si;
        else if (top < 0 || 
                  (si == ')' && stack[top--] != '(') ||
                  (si == ']' && stack[top--] != '[') || 
                  (si == '}' && stack[top--] != '{')) {
            free(stack);
            return false;
        }
    }
    free(stack);
    return top == -1;
}