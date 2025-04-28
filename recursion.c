/*

There are two important things that one needs to figure out before implementing a recursive function:

    recurrence relation: the relationship between the result of a problem and the result of its subproblems.
    base case: the case where one can compute the answer directly without any further recursion calls.
     Sometimes, the base cases are also called bottom cases, since they are often the cases where the problem has 
     been reduced to the minimal scale, i.e. the bottom, if we consider that dividing the problem into subproblems 
     is in a top-down manner.

    Once we figure out the above two elements, to implement a recursive function we simply call the function itself 
    according to the recurrence relation until we reach the base case.




*/

/*

It is not easy to understand recursion and find a recursive solution for the problem. It needs practice.

When you meet a tree problem, ask yourself two questions: Can you determine some parameters 
to help the node know its answer? Can you use these parameters and the value of the node itself to 
determine what should be the parameters passed to its children? If the answers are both yes, try to 
solve this problem using a "top-down" recursive solution.

Or, you can think of the problem in this way: for a node in a tree, if you know the answer of its children, 
can you calculate the answer of that node? If the answer is yes, solving the problem recursively using a bottom-up 
approach might be a good idea.

In the following sections, we provide several classic problems for you to help you understand tree structure and 
recursion better.

*/

// Fibonacci Numbers

int fib(int n){
    if(n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

// Factorial Numbers
int fact(int n){
    if(n <= 1) return 1;
    return n * fact(n-1);
}

// Power
double myPow(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1 / myPow(x, -n);
    return x * myPow(x, n - 1);
}