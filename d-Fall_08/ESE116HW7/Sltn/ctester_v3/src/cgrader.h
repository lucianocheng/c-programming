#ifndef _C_GRADER_
#define _C_GRADER_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include "bool.h"
#include "test.h"
#include "cassert.h"
#include "ctester.h"
#include "ese_malloc.h"
#include "problem.h"
#include "stringbuf.h"
#include "linked_list.h"

/**
 * Gets the string of the problem set type from a PS_TYPE object
 *
 * @param type the PS_TYPE object to decode; returns a string based on this
 * @return "homework" if type is a HOMEWORK, "exam" if type is a EXAM, "lab" if type is a LAB
 */

char* _pstype_to_str(PS_TYPE type);

/**
 * Print the usage message for the given program, printed if the program is missing arguments
 * 
 * @param prog the program name, as a string
 */
void printUsage(char* prog);

/**
 * Run every test as set up in the PROBLEM linked list
 *
 * @param argc the size of argv
 * @param argv the collection of arguments to the program
 */
void run_all_tests(int argc, char* argv[]);

/**
 * Cleans up after all tests have been run, cleans up all global variables
 */
void clean_up();

PROBLEM* add_new_problem(const char* name, int number);


/**
 * Add a new test to the given problem, given the function to test
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_test(PROBLEM* problem, const char* description, double points, void (*test_function)());

/**
 * Supplied for backwards compatibility, all tests are now fork tests
 * 
 * Add a new test to the given problem with a fork test, given the function to test
 * A fork test means that the program will fork off and test and see if the function completes
 *        in 30 seconds.  If it does not, it fails the test.
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_fork_test(PROBLEM* problem, const char* description, double points, void (*test_function)());

/**
 * Add a new extra credit to the given problem, given the function to test
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of extra credit points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_ec_test(PROBLEM* problem, const char* description, double points, void (*test_function)());

/**
 * Add a manual grade to the given problem.  A manual grade is a grade you enter at the keyboard, not tested by the comp
 *
 * @param problem the problem to add the manual grade to
 * @param description a description of the manual grade
 * @param points the points associated with this manual grade
 * @param is_extra_credit is this manual grade extra credit?
 */
void add_manual_grade(PROBLEM* problem, const char* description, int points, BOOL is_extra_credit);

/**
 * Set whether or not this problem has comments, the value of set is set to has_comments
 *
 * @param problem the problem to set if there are comments
 * @param set TRUE if the problem does have comments, FALSE if it does not
 */
void set_comments(PROBLEM* problem, BOOL set);

#endif
