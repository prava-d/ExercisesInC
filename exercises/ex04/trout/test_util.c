/* Program to test out the functionality of the icmpcode_v4(int code) function
	in the util.c file.

	Adapted from Allen Downey's test_endswith.c file.

	Author: Prava
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "util.h"
#include "minunit.h"

int tests_run = 0;

static char *test1() {
	char *res = icmpcode_v4(0);
	char *message = "Test 1 (code 0) failed: Did not return 'network unreachable'";
	mu_assert(message, !(strcmp(res, "network unreachable")));
	return NULL;
}

static char *test2() {
	char *res = icmpcode_v4(1);
	char *message = "Test 2 (code 1) failed: Did not return 'host unreachable'";
	mu_assert(message, !(strcmp(res, "host unreachable")));
	return NULL;
}

static char *test3() {
	char *res = icmpcode_v4(2);
	char *message = "Test 3 (code 2) failed: Did not return 'protocol unreachable'";
	mu_assert(message, !(strcmp(res, "protocol unreachable")));
	return NULL;
}

static char *test4() {
	char *res = icmpcode_v4(3);
	char *message = "Test 4 (code 3) failed: Did not return 'port unreachable'";
	mu_assert(message, !(strcmp(res, "port unreachable")));
	return NULL;
}

static char *test5() {
	char *res = icmpcode_v4(4);
	char *message = "Test 4 (code 3) failed: Did not return 'fragmentation required but DF bit set'";
	mu_assert(message, !(strcmp(res, "fragmentation required but DF bit set")));
	return NULL;
}

static char * all_tests() {
	mu_run_test(test1);
    mu_run_test(test2);
    mu_run_test(test3);
    mu_run_test(test4);
    mu_run_test(test5);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

