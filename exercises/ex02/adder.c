/* Program that adds together integers passed in by a user.
   Name: Prava Dhulipalla
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size = 0;

/* Function that returns the size allocation of the array.

   Returns user input (if between 1 or 100) or else, 10
*/
int get_size() {
	char input[4];
	printf("What is the max amount of integers you want to add together (1 to 100)?\nPress enter to keep default, 10.\n");
	fgets(input, sizeof(input), stdin);

	int val = atoi(input);

	if (val > 0 && val <= 100) {
		return val;
	}
	else {
		return 10;
	}
}

/* Gets input of integers seperated by an Enter and exitable by Ctrl+D

   Errors if too many numbers are entered, the number is too large, or if the
   entered character is 0 or a noninteger

   nums: reference to array to store nums

*/
void get_input(int *nums) {
	char input[5];
	printf("Enter your numbers on seperate lines:\n");

	int count = 0;

	while (fgets(input, sizeof(input), stdin) != NULL) {
		if (count == size) {
			printf("Error: You entered too many numebrs.\n");
			break;
		}

		if (input[strlen(input) - 1] != '\n') {
			printf("Error: Your input length is too large.\n");
			break;
		}

		if (atoi(input) == 0) {
			printf("Error: You entered a 0 or a nonnumber.\n");
			break;
		}

		nums[count] = atoi(input);
		count++;

	}

}

/* Adds together elements of an array and returns sum

   nums: array with user input values

*/
int add_nums(int *nums) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += nums[i];
	} 
	return sum;
}

/* Main function that gets user input to sum together nums

   Prints out sum
*/
int main() {
	size = get_size();

	int nums[size];
	memset(nums, 0, size * sizeof(int));

	get_input(nums);
	int sum = add_nums(nums);

	printf("The sum is %i\n", sum);
	return 0;
} 