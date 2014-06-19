#ifndef _CTESTER_CTESTER_H_
#define _CTESTER_CTESTER_H_

#include <stdlib.h>
#include "stringbuf.h"
#include "problem.h"
#include "test.h"

#define TEST_FAIL 42
#define MAX_TAG_LEN 128
#define COMMENT_BUF_LEN 512
#define MIN_XMLBUF_LEN 1024

#define PASSED 1
#define FAILED 0

//#define SETERRFLAG() current_test->errflag=1
//#define CUR_ERR_FLAG current_test->errflag

/**
 * Problem Set Type Enumeration
 */
typedef enum { HOMEWORK, LAB, EXAM } PS_TYPE;

/**
 * Calloc the requested memory or exit the program
 *
 * @param num the number of units to index
 * @param size the size of a given unit
 * @param msg the message to print if the calloc fails
 */
void* _calloc_or_die(size_t num, size_t size, const char* msg);

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
 * Aborts execution of the current test and moves on to the next test, write a message
 * @param msg the message to print once the test has failed
 */
void set_fail_msg(TEST* test, char* msg);

/**
 * Test a function via a fork function.  Kill after 30 seconds if function has not completed
 * @param function the function to fork and make sure terminates
 * @returns 0 if unsuccessful, 1 if successful
 */
int fork_test_function(TEST* test);

/**
 * Run all the tests, passing the first problem in the linked list to the tester; 
 * Not thread safe
 *
 * @param problem the first problem in the PROBLEM linked list
 * @param late_ts The late timestamp, in unix epoch time
 * @param xml_buffer the string buffer to print the xml output
 */
void run_problem_tests(PROBLEM* problem, long late_ts, _STRBUF* xml_buffer);

void fill_stack_frame(int value);

/**
 * Add a new manual grade, this is the system function, not called by the grading program; not thread safe
 */
void _get_manual_grade();

PROBLEM* add_new_problem(const char* name, int number);

#endif
