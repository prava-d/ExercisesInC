/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/
/*
It seems that the parent and child processes do all have access to the same
global, static, and heap variables. However, it seems that the child process
creates a copy of the parent address space according the results of this code.
When the parent and the child incremented it, they became the same value instead
of incrementing it by 2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

// variable located in the global segment
int gint = 1;


// function to print out all the variables
void printvars(int sint, int* hint) {
    printf("Variable gint %d\n", gint);
    printf("Variable sint %d\n", sint);
    printf("Variable hint %d\n", *hint);
}

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


// modified to change global, static, and heap variables
void child_code(int i, int *sintptr, int *hint)
{
    sleep(i);
    gint = gint + 1;
    *sintptr = *sintptr + 1;
    *hint = *hint + 1;
    printf("Hello from child %d.\n", i);
    printvars(*sintptr, hint);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // variables located in the static and the heap segments
    int sint = 10;
    int* hint = malloc (sizeof(int));
    *hint = 100; 

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i, &sint, hint);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    // check to see what happens with the parent modification
    gint = gint + 1;
    sint = sint + 1;
    *hint = *hint + 1;
    printvars(sint, hint);

    // check to see what happens with the child code variables
    child_code(i, &sint, hint);


    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
