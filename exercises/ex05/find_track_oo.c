/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


typedef regex_t Regex;


/* Returns a new Regex that matches the given pattern.
* Modified Allen's solution code from Homework 2.5
*
* pattern: string regex
* flags: flags passed to regcomp
* returns: new Regex
*/
Regex *make_regex(char *pattern, int flags) {
    // using malloc to free dynamic space
    regex_t *re = malloc(sizeof(regex_t));
    int ret = regcomp(re, pattern, flags);

    if (ret) {
        printf("Regex error");
        exit(1);
    }

    return re;
}

/* Checks whether a regex matches a string.
* Modified Allen's solution code from Homework 2.5
*
* regex: Regex pointer
* s: string
* returns: 1 if there's a match, 0 otherwise
*/
int regex_match(Regex *regex, char *s) {
    // first makes regex
    int ret = regexec(regex, s, 0, NULL, 0);

    // successful match
    if (!ret) {
        return 1;
    }
    // not successful
    else if (ret == REG_NOMATCH) {
        return 0;
    }
    // regex match error
    else {
        char msgbuf[100];
        regerror(ret, regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}

/* Frees a Regex.
*
* regex: Regex pointer
*/
void regex_free(Regex *regex) {
    //the regex library has an inbuilt function for this
    regfree(regex);
}


/* Finds all tracks that match the given pattern.
*
* Prints track number and title.
*/
void find_track_regex(char pattern[])
{
    int i;

    Regex *regex = make_regex(pattern, REG_EXTENDED | REG_NOSUB);

    for (i=0; i<NUM_TRACKS; i++) {
        if (regex_match(regex, tracks[i])) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }

    regex_free(regex);
}


int main (int argc, char *argv[])
{
    char *pattern = "F.*F.*";
    find_track_regex(pattern);

    return 0;
}
