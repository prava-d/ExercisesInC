/* Example from Head First C.

Downloaded from https://github.com/twcamper/head-first-c

Modified by Allen Downey.
*/

/* Answers to questions:
The exec() call terminates the previous process, so it only looked at the 
first feed and outputed the headlines for that. To fix, we need to fork()
in order to create a copy. That code was copied and modified from fork.c.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }
    const char *PYTHON = "/usr/bin/python2";
    const char *SCRIPT = "rssgossip.py";
    char *feeds[] = {
        "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
    };
    int num_feeds = 5;
    char *search_phrase = argv[1];
    char var[255];

    double start, stop;
    int pid;
    int status;

    start = get_seconds();

    for (int i=0; i<num_feeds; i++) {
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        pid = fork();
        if (pid == 0) {
            int res = execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars);
            if (res == -1) {
                error("Can't run script.");
            }
        }
    }


    for (int i=0; i<num_feeds; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        if(status != 0){
          printf("Child %d exited with error code %d.\n", pid, status);
        }
    }

    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);


    return 0;
}
