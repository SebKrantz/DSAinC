/* 
 Static is a keyword in the C programming language. It can be used with variables and functions.

 By default, variables are local to the scope in which they are defined. Variables can be declared as 
 static to increase their scope up to file containing them. As a result, these variables can be accessed 
 anywhere inside a file.
 */

 #include<stdio.h>
 
int runner() {
    static int count = 0; // Static variable inside function is only initialized once, when the program starts
    count++;
    return count;
}

int main() {
    printf("%d ", runner());
    printf("%d ", runner());
    return 0;
}
