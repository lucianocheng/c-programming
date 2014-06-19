/**
 * Exercises for int arrays.
 *
 * ESE 116 Spring 2007
 */

#include <stdio.h>
#include <stdlib.h>

// methods to write
void copyArray(int from[], int to[], int len);
void rotateArray(int arr[], int len, int direction);
// ALSO getDiffs

/**
 * Declares new int arrays of some default length,
 * then runs the other functions on them and prints results.
 */
int main() {
	// ADD CODE HERE TO DECLARE ARRAYS & RUN YOUR FUNCTIONS
	return EXIT_FAILURE;
}

/**
 * Copy the elements of one array into another array.
 * @param from the array to copy from
 * @param to the array to copy into
 * @param len the length (same for both arrays)
 */
void copyArray(int from[], int to[], int len) {
	// COMPLETE THIS FUNCTION
}

/**
 * Calculate the differences between an array's elements,
 * last first. That is, the first element in the diffs array
 * will be the the array[last] - array[2nd-to-last].
 *      [0,  10,  -2, 45,  23, -10, 2]
 *      produces
 *        [12, -33, -22, 47, -12, 10]
 *      or, for a shorter example,
 *      [0, 10, -2]
 *      produces
 *       [-12, 10]
 * @param arr the array to generate differences for
 * @param diffs the array to put differences in
 * @param len the length of the original array
 *      (the differences array should be len-1 long)
 */
void getDiffs(int arr[], int diffs[], int len) {
	// COMPLETE THIS FUNCTION
}

/**
 * Rotate an array, either right or left.
 *	RIGHT: [0, 1, 2, 3] becomes [3, 0, 1, 2]
 *	LEFT:  [0, 1, 2, 3] becomes [1, 2, 3, 0]
 * @param arr the array to rotate
 * @param len the length (same for both arrays)
 * @param direction, one of RIGHT or LEFT
 *	if invalid, return without modifying the array
 */
// DECLARE THE FUNCTION, and its header at the top of the file
	// define RIGHT and LEFT as some values
	// COMPLETE THIS FUNCTION
