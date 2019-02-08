/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

/* Prints address of a local variable
   
   varname: name of the variable
   var: address to print out
*/
void printAddress(char *varname, int *var) {
	printf("Address of %s is %p\n",varname, var);
}

/* Main function to illustrate memory allocation for variables and pointers.
*/
int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);

    /* p points to 0xb14010
	   x points to 0xb144b0

	   The heap grows up as the address for x is larger.
    */
    void *x = malloc(64);
    printf ("x points to %p\n", x);

    /* Address of var2 is 0x7ffe541b9db8
	   Address of y is 0x7ffe541b9dbc

	   The stack grows up as the address for y is larger.
    */
    int y = 10;
    printAddress("y", &y);

    /* Address of chunk1 is 0xb14500
	   Address of chunk2 is 0xb14520

	   There are 32 Bytes between them.
    */
    void *chunk1 = malloc(8);
    void *chunk2 = malloc(8);
    printAddress("chunk1", chunk1);
    printAddress("chunk2", chunk2);

    return 0;
}
