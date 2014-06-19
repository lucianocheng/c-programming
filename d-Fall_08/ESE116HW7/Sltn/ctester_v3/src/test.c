#include "test.h"
#include "stringbuf.h"
#include "bool.h"

/**
 * Add a new test to a given problem, a problem is a collection of tests; 
 * This is not the function that is called by the test program, this is an internal function
 *
 * @param problem the problem to which to add the test
 * @param description the description of the problem
 * @param test_function the function that the test will call
 * @param list the test list to add the test to
 * @return the test that is created
 */
TEST* test_create(const char* description, void (*test_function)()){
	TEST* test = _calloc_or_die(1, sizeof(TEST), "Couldn't calloc test\n");
	test->descrip = description;
	test->test_function = test_function;
	test->errflag = FALSE;
	test->has_run = FALSE;
	test->is_successful = FALSE;
	test->score = 0;
	test->ec_score = 0;

	return test;
}
