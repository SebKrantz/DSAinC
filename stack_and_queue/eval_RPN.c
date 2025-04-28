#include <string.h>
#include <stdlib.h>

// Solution
int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(tokensSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < tokensSize; ++i) {
        if (tokens[i][1] == '\0' &&
            (tokens[i][0] == '+' || tokens[i][0] == '-' ||
             tokens[i][0] == '*' || tokens[i][0] == '/')) {
            int op2 = stack[top--];
            int op1 = stack[top--];
            switch (tokens[i][0]) {
                case '+':
                    stack[++top] = op1 + op2;
                    break;
                case '-':
                    stack[++top] = op1 - op2;
                    break;
                case '*':
                    stack[++top] = op1 * op2;
                    break;
                case '/':
                    stack[++top] = op1 / op2;
                    break;
            }
        } else {
            stack[++top] = atoi(tokens[i]);
        }
    }

    int result = stack[top];
    free(stack);
    return result;
}

// Solution 2: Evaluate the Stack

struct stack {
    int top;
    int array[10000];
};

int is_empty(struct stack* stack) { return stack->top == 0; }
int peek(struct stack* stack) { return stack->array[stack->top - 1]; }

void push(struct stack* stack, int num) {
    stack->array[stack->top] = num;
    stack->top++;
}

int pop(struct stack* stack) { return stack->array[--stack->top]; }

int evalRPN(char** tokens, int tokensSize) {
    struct stack stack;
    stack.top = 0;

    for (int i = 0; i < tokensSize; i++) {
        if (strcmp(tokens[i], "+") != 0 && strcmp(tokens[i], "-") != 0 &&
            strcmp(tokens[i], "*") != 0 && strcmp(tokens[i], "/") != 0) {
            push(&stack, atoi(tokens[i]));
        } else {
            int number2 = pop(&stack);
            int number1 = pop(&stack);
            int result = 0;
            if (strcmp(tokens[i], "+") == 0) {
                result = number1 + number2;
            } else if (strcmp(tokens[i], "-") == 0) {
                result = number1 - number2;
            } else if (strcmp(tokens[i], "*") == 0) {
                result = number1 * number2;
            } else if (strcmp(tokens[i], "/") == 0) {
                result = number1 / number2;
            }
            push(&stack, result);
        }
    }

    return peek(&stack);
}

// More Elaborate Solution

struct hash_table {
    char key[2];
    int (*value)(int, int);
    UT_hash_handle hh;
};

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mult(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

struct hash_table *create_hash_table() {
    struct hash_table *s, *hash_table = NULL;
    int (*functions[4])(int, int) = {add, sub, mult, divide};
    char *keys[4] = {"+", "-", "*", "/"};

    for (int i = 0; i < 4; i++) {
        s = malloc(sizeof(struct hash_table));
        strncpy(s->key, keys[i], 2);
        s->value = functions[i];
        HASH_ADD_STR(hash_table, key, s);
    }

    return hash_table;
}

int evalRPN(char **tokens, int tokens_size) {
    struct hash_table *hash_table = create_hash_table();
    struct hash_table *s;
    int currentPosition = 0;
    int *stack = calloc(tokens_size, sizeof(int));
    int top = -1;

    while (currentPosition < tokens_size) {
        HASH_FIND_STR(hash_table, tokens[currentPosition], s);
        if (s == NULL) {
            stack[++top] = atoi(tokens[currentPosition++]);
        } else {
            int a = stack[top--];
            int b = stack[top--];
            stack[++top] = s->value(b, a);
            currentPosition++;
        }
    }

    int result = stack[top];
    free(stack);
    HASH_CLEAR(hh, hash_table);
    return result;
}