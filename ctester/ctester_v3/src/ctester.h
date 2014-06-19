#ifndef _CTESTER_CTESTER_H_
#define _CTESTER_CTESTER_H_

#include <stdlib.h>
#include "ctester-defs.h"
#include "cassert.h"

/**
 * Calloc the requested memory or exit the program
 *
 * @param num the number of units to index
 * @param size the size of a given unit
 * @param msg the message to print if the calloc fails
 */
void* _calloc_or_die(size_t num, size_t size, const char* msg);


/**
 * Add a new test to the given problem, given the function to test
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
PROBLEM* add_new_problem(const char* description, int number);

/**
 * Add a new test to the given problem, given the function to test
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_test(PROBLEM* problem, const char* description, double points, void (*test_function)() );

/**
 * Add a new test to the given problem with a fork test, given the function to test
 * A fork test means that the program will fork off and test and see if the function completes
 *        in 30 seconds.  If it does not, it fails the test.
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_fork_test(PROBLEM* problem, const char* description, double points, void (*test_function)() );

/**
 * Add a new extra credit to the given problem, given the function to test
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of extra credit points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_ec_test(PROBLEM* problem, const char* description, double points, void (*test_function)() );

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

/**
 * Run all the tests, passing the first problem in the linked list to the tester; 
 * Not thread safe
 *
 * @param problem the first problem in the PROBLEM linked list
 * @param late_ts The late timestamp, in unix epoch time
 * @param xml_buffer the string buffer to print the xml output
 */
void run_tests(PROBLEM* problem, long late_ts, _STRBUF* xml_buffer);

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

/**
 * Create a new _STRBUF struct, initilize the values
 *
 * @param min the minimum size of the starting string buffer
 */
_STRBUF* _strbuf_init(int min);

/**
 * Append a string append_str on to the end of the string buffer 'buf'
 *
 * @param buf the buffer to add the string on to
 * @param append_str the string to append
 */
void _strbuf_append(_STRBUF* buf, char* append_str);

/**
 * free a stringbuffer cleanly
 *
 * @param buf the string buffer to free
 */
void _strbuf_free(_STRBUF* buf);

/**
 * Replaces instances of the search string with the replace string in 'string'; 
 * Written By -  Lehner Franz (franz@caos.at) 2002
 *
 * @param string the string to do the operation on
 * @param search the string to search for
 * @param replace the string to replace the first string with
 * @return return the edited string
 */
char * str_replace (char * string,char * search,char *replace);

/**
 * Replaces '<' and '>' in the xml docs so the xml does not crash
 *
 * @param string the string to do the replacement on
 * @return return the edited string
 */
char * xml_escape(char* string);

#endif
