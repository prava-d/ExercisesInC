/* Program that implements a simple version of the tee command commonly used in a she;;.
	Reads from the stdin and write to the stdout and files
	Author: Prava
*/

/* Answers to questions

3. I first looked at the HFC C chapter to help be figure out how to work with files and arguments
and such, since I personally am not super comfortable with file-writing, looking and parsing arguments
from user inputs, etc. I also looked online to either get some clarification of what HRF did or if
something was erroring 'needlessly. I also think that I didn't have a great understanding of what I
was actually supposed to do and as such coding this probably took way longer then expected. Also I don't
feel like my implementation feels complete and I'm not sure if it does what the tee command should do 
- something I felt while coding too, so I think this lack of initial deep understanding provided a
hindrance to completeing this faster too.

4. I noticed that I didn't print out any errors and really only had one error-handling mechanism,
which doesn't seem very good. It also obviously doesn't have all the additions that the command
would normally have. I think if I had a second crack at it now, I would definitely check for invalid
inputs / failure points in writing to the files and generate appropriate error messages, since the
adding functionality to tee.c seems more trivial (in terms of good code).

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	int i;
	char c;
	char in[256];
	FILE *out;

	// checking arguments and updating variables as necessary
	while((c = getopt(argc, argv, "ai")) != EOF) {
		switch(c) {
			case 'a':
				i = 1;
				break;
			default:
				exit(1);
		}
	}

	// from HFC
	argc -= optind;
	argv += optind;

	// actually writes to stdout and file
	while(fgets(in, 256, stdin)) {
		for (int j = 0; j < argc; j++) {
			if (i) {
				out = fopen(argv[i], "a");
			}
			else {
				out = fopen(argv[i], "w");
			}
			
			// from HFC
			// make sure to close the file
			fprintf(stdout, "%s", in);
			fputs(in, out);
			fclose(out);
		}
}


	return 0;
}