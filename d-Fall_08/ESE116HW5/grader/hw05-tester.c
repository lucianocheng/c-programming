/**
 * Test ESE 116 HW 05, Spring 2008
 *
 * @version 2008 April 8th
 * @author JJ Geewax
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
 */

 // specific to this homework
#include "tokenizer.h"
 
// general homework tester stuff
#include "cgrader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions that are extern'ed by the library testing type for the xml parser
// Must be filled in
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11605; }

// tester functions' headers
#include "testGetWord.h"
#include "testSortAndDeleteDuplicates.h"
#include "testGetChar.h"
#include "curveProblem.h"

// tester main
int main(int argc, char * argv[]) {
	int prob1_points = 60;
	int prob1_tests = 12;
	
	void testGetWord_empty();
	void testGetWord_whitespace();
	void testGetWord_leading_whitespace_ret_value();
	void testGetWord_leading_whitespace_string();
	void testGetWord_trailing_whitespace_ret_value();
	void testGetWord_trailing_whitespace_string();
	void testGetWord_single_word_ret_value();
	void testGetWord_single_word_string();
	void testGetWord_multiple_words_ret_value();
	void testGetWord_multiple_words_string();
	void testGetWord_too_long_ret_value();
	void testGetWord_too_long_string();
	
	
	PROBLEM * prob1 = add_new_problem("Test get_word", 1);
	add_new_test(prob1, "Test get_word (empty)", prob1_points/prob1_tests,
		&testGetWord_empty);
	add_new_test(prob1, "Test get_word (whitespace)", prob1_points/prob1_tests,
		&testGetWord_whitespace);
	add_new_test(prob1, "Test get_word (leading whitespace) ret value", prob1_points/prob1_tests,
		&testGetWord_leading_whitespace_ret_value);
	add_new_test(prob1, "Test get_word (leading whitespace) string", prob1_points/prob1_tests,
		&testGetWord_leading_whitespace_string);
	add_new_test(prob1, "Test get_word (trailing whitespace) ret value", prob1_points/prob1_tests,
		&testGetWord_trailing_whitespace_ret_value);
	add_new_test(prob1, "Test get_word (trailing whitespace) string", prob1_points/prob1_tests,
		&testGetWord_trailing_whitespace_string);
	add_new_test(prob1, "Test get_word (single word) ret value", prob1_points/prob1_tests,
		&testGetWord_single_word_ret_value);
	add_new_test(prob1, "Test get_word (single word) string", prob1_points/prob1_tests,
		&testGetWord_single_word_string);
	add_new_test(prob1, "Test get_word (multiple words) ret value", prob1_points/prob1_tests,
		&testGetWord_multiple_words_ret_value);
	add_new_test(prob1, "Test get_word (multiple words) string", prob1_points/prob1_tests,
		&testGetWord_multiple_words_string);
	add_new_test(prob1, "Test get_word (too long) ret value", prob1_points/prob1_tests,
		&testGetWord_too_long_ret_value);
	add_new_test(prob1, "Test get_word (too long) string", prob1_points/prob1_tests,
		&testGetWord_too_long_string);
		
	
	int prob2_points = 40;
	int prob2_tests = 5;
	PROBLEM * prob2 = add_new_problem("Test sort_and_delete_duplicates", 2);
	add_new_test(prob2, "test sort_and_delete_duplicates (empty)", prob2_points/prob2_tests,
		&testSortAndDeleteDuplicates_empty);
	add_new_test(prob2, "test sort_and_delete_duplicates (simple duplicate)", prob2_points/prob2_tests,
		&testSortAndDeleteDuplicates_simple_duplicate);
	add_new_test(prob2, "test sort_and_delete_duplicates (single word)", prob2_points/prob2_tests,
		&testSortAndDeleteDuplicates_single_word);
	add_new_test(prob2, "test sort_and_delete_duplicates (simple sort)", prob2_points/prob2_tests,
		&testSortAndDeleteDuplicates_simple_sort);
	add_new_test(prob2, "test sort_and_delete_duplicates (complex)", prob2_points/prob2_tests,
		&testSortAndDeleteDuplicates_complex);

	run_all_tests(argc, argv);
	clean_up();	
	return 0;
}
