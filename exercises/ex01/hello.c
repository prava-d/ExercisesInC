/*
Simple program to add together two numbers.
Name: Prava
Source: Exercise 1 in ExercisesInC
*/

/* Answers to Optimization questions.
1. The following two lines corresponds to the line of C code:
    subq	$16, %rsp
    movl	$5, -4(%rbp)
2. A lot of things change about the assembly code, but the most noteable
  change was that the optimization seemed to have removed the reference
  to x (movl	$5, -4(%rbp)).
3. When printing x, both with and without optimization, a reference to x
  appears in the assembly code. However, the stack frame seems to be
  smaller with optimization - subl sets it to 16 without the flags
  and 8 with it.
4. Without the optimization, a reference to x exists. With the optimization,
  the value is y is precomputed and used rather then needing to store x.
5. Optimization seems to help in terms of dropping references to variables
  that don't actually need to be stored to run the program. It also will
  precompute values that always stay the same at execution. This allows for
  less use of space and faster program execution.
*/

#include <stdio.h>

int main() {
    int x = 5;
    int y = x + 1;
    //printf("Hello, World!\n");
    //printf("The value of x is %d\n", x);
    printf("The value of y is %d\n", y);
    return 0;
}
