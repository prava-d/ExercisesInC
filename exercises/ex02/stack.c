/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

/* Answers to exercise questions:

   1. The function foo() makes an array of size 5 and assigns each element the
      value 42. The function bar() makes an array of size 5 and assigns the
      elements 0, 1, 2, 3, and 4 to it, consecutively. The main function prints
      the elements of an array after foo() and then bar() are called on it.

   2. stack.c: In function ‘foo’:
      stack.c:30:12: warning: function returns address of local variable [-Wreturn-local-addr]

      This error means that there is a local variable that only exists in the
      foo() stack frame whose address is being returned. So we don't have,
      access to it outside of the function.

   3. I got a segmentation fault, probably because the program was reading fron
      places in memory it wasn't supposed to.

   4. 0x7ffe206778f0
      0x7ffe206778f0

      These outputs were generated, printing out the addresses of the arrays.
      Although foo() returned the array, when bar() ran the memory was
      reallocated. Hence, them being at the same place is memory.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
