/**
 * Test ESE 116 HW 01, Spring 2007
 *
 * @version 2007 Oct 20
 * @author Luciano Cheng
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
 */

// general homework tester stuff

// These #defines don't seem to take effect in the right scope,
// so moved to the Makefile.hw1 definition of the gcc call
// #define TEST_1xx
// #define TEST_1XX
// #define TESTER_1XX

#include "ctester.h"
#include <stdio.h>
#include <stdlib.h>

// specific to this homework
#include "calc.h"

// tester functions' headers
void testlookupOperator_ADD();
void testlookupOperator_SUB();
void testlookupOperator_MUL();
void testlookupOperator_DIV();
void testlookupOperator_ERR();

void testevaluateExpression_ADD();
void testevaluateExpression_SUB();
void testevaluateExpression_MUL();
void testevaluateExpression_DIV();

// tester main
int main(int argc, char * argv[]) {
	PROBLEM * prob1 = add_new_problem("lookupOperator", 1);
	PROBLEM * prob2 = add_new_problem("evaluateExpression", 2);
	PROBLEM * prob3 = add_new_problem("use switch statements", 3);

	add_new_test(prob1, "testlookupOperator_ADD", 10,
		&testlookupOperator_ADD);
	add_new_test(prob1, "testlookupOperator_SUB", 10,
		&testlookupOperator_SUB);
	add_new_test(prob1, "testlookupOperator_MUL", 10,
		&testlookupOperator_MUL);
	add_new_test(prob1, "testlookupOperator_DIV", 10,
		&testlookupOperator_DIV);
	add_new_test(prob1, "testlookupOperator_ERR", 10,
		&testlookupOperator_ERR);

	add_new_test(prob2, "testevaluateExpression_ADD", 10,
		&testevaluateExpression_ADD);
	add_new_test(prob2, "testevaluateExpression_SUB", 10,
		&testevaluateExpression_SUB);
	add_new_test(prob2, "testevaluateExpression_MUL", 10,
		&testevaluateExpression_MUL);
	add_new_test(prob2, "testevaluateExpression_DIV", 10,
		&testevaluateExpression_DIV);

	add_manual_grade(prob3, "used switch statements", 10, FALSE);

	run_all_tests(argc, argv);

	clean_up();
	
	return 0;
}

char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11601; }

// specific tests

/**
 * Test the lookupOperator function:
 *	input		output
 *	'a' or 'A'	ADD
 *	's' or 'S'	SUB
 *	'm' or 'M'	MUL
 *	'd' or 'D'	DIV
 *	anything else	ERR
 */

// add
void testlookupOperator_ADD() {
	assert_equals_char("lookup a", '+', lookupOperator('a'));
	assert_equals_char("lookup A", '+', lookupOperator('A'));
}
// subtract
void testlookupOperator_SUB() {
	assert_equals_char("lookup s", '-', lookupOperator('s'));
	assert_equals_char("lookup S", '-', lookupOperator('S'));
}
// multiply
void testlookupOperator_MUL() {
	assert_equals_char("lookup m", '*', lookupOperator('m'));
	assert_equals_char("lookup M", '*', lookupOperator('M'));
}
// divide
void testlookupOperator_DIV() {
	assert_equals_char("lookup d", '/', lookupOperator('d'));
	assert_equals_char("lookup D", '/', lookupOperator('D'));
}
// error
void testlookupOperator_ERR() {
	assert_equals_char("lookup error 'Z'", '?', lookupOperator('Z'));
	assert_equals_char("lookup error '\0'", '?', lookupOperator('\0'));
	assert_equals_char("lookup error '\n'", '?', lookupOperator('\n'));
}

/**
 * Test evaluateExpression(int {ADD, SUB, MUL, DIV}, int int)
 */
// add
void testevaluateExpression_ADD() {
	assert_equals_int("a 3 5 = 8", 8,
		evaluateExpression('+', 3, 5));
	assert_equals_int("a -1024 24 = -1000", -1000,
		evaluateExpression('+', -1024, 24));
}
// subtract
void testevaluateExpression_SUB() {
	assert_equals_int("s 102 12 = 90", 90,
		evaluateExpression('-', 102, 12));
	assert_equals_int("s 5 5 = 0", 0,
		evaluateExpression('-', 5, 5));
}
// multiply
void testevaluateExpression_MUL() {
	assert_equals_int("m 2 217 = 434", 434,
		evaluateExpression('*', 2, 217));
	assert_equals_int("m -512 -2 = 1024", 1024,
		evaluateExpression('*', -512, -2));
}
// divide
void testevaluateExpression_DIV() {
	assert_equals_int("d 9 10 = 0", 0,
		evaluateExpression('/', 9, 10));
	assert_equals_int("d 90 45 = 2", 2,
		evaluateExpression('/', 90, 45));
}
