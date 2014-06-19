/**
 * Test ESE 116 HW 04, Spring 2008
 *
 * @version 2008 March 26th
 * @author JJ Geewax
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
 */

 // specific to this homework
#include "pointers.h"
 
// general homework tester stuff
#include "cgrader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions that are extern'ed by the library testing type for the xml parser
// Must be filled in
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11604; }

// tester functions' headers
// Pointer to vowel, 20 pts
#include "testPointerToVowel.h"
// Pointer to last word, 20pts
#include "testPointerToLastWord.h"
// Reverse strings = 18 PTS
// Used Pointer notation = 2 PTS
#include "testReverse.h"

void blankTest(){}

// tester main
int main(int argc, char * argv[]) {
	// 12 + 21 = 33 points // after curve, -16 points, 17 points
	PROBLEM * prob1 = add_new_problem("Test Pointer to Vowel", 1);
	add_new_test(prob1, "Test pointer to vowel (x)", 6,
		&testPointerToVowel_x);
	add_new_test(prob1, "Test pointer to vowel (y)", 6,
		&testPointerToVowel_y);
	add_new_test(prob1, "Test pointer to vowel (z)", 7,
		&testPointerToVowel_z);
	add_new_test(prob1, "Test pointer to vowel (w)", 7,
		&testPointerToVowel_w);
	add_new_test(prob1, "Test pointer to vowel (err)", 7,
		&testPointerToVowel_err);

	// 12 + 21 = 33 points // after curve, -14 points, 19 points
	PROBLEM * prob2 = add_new_problem("Test Pointer to Last Word", 2);
	add_new_test(prob2, "testPointerToLastWord_oneWord", 6,
		&testPointerToLastWord_oneWord);
	add_new_test(prob2, "testPointerToLastWord_twoWord", 6,
		&testPointerToLastWord_twoWord);
	add_new_test(prob2, "testPointerToLastWord_threeWord", 7,
		&testPointerToLastWord_threeWord);
	add_new_test(prob2, "testPointerToLastWord_spaceAndEmpty", 7,
		&testPointerToLastWord_spaceAndEmpty);
	add_new_test(prob2, "testPointerToLastWord_null", 7,
		&testPointerToLastWord_null);

	// 11 + 21 = 32 points // after curve, -5 from here, 27 points
	PROBLEM * prob3 = add_new_problem("Test reverse String", 3);
	add_new_test(prob3, "testReverse_smallString", 5,
		&testReverse_smallString);
	add_new_test(prob3, "testReverse_longString", 6,
		&testReverse_longString);
	add_new_test(prob3, "testReverse_oddLetters", 7,
		&testReverse_oddLetters);
	add_new_test(prob3, "testReverse_evenLetters", 7,
		&testReverse_evenLetters);
	add_new_test(prob3, "testReverse_nullAndEmpty", 7,
		&testReverse_nullAndEmpty);

	PROBLEM * prob4 = add_new_problem("Used pointer notation", 4);
	add_new_test(prob4, "used pointer notation", 2, &blankTest);

	run_all_tests(argc, argv);
	clean_up();	
	return 0;
}

/** 
 * ----------------------------------------------------
 * Specific Test Functions
 * ----------------------------------------------------
 */
