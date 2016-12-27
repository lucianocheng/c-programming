#ifndef _CTESTER_CASSERT_H_
#define _CTESTER_CASSERT_H_

#include <stdlib.h>

/**
 * Test if the two strings match, only test with null-terminated char arrays; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param str1 the expected string
 * @param str2 the string produced by the student's test code
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_string(const char* msg, char* str1, char* str2);

/**
 * Test if the two strings match up to 'length' characters; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param str1 the expected string
 * @param str2 the string produced by the student's test code
 * @param length the length of the string to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_nstring(const char* msg, char* str1, char* str2, int length);

/**
 * Test if the two integers match; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param int1 the expected integer
 * @param int2 the integer produced by the students test code
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_int(const char* msg, int int1, int int2);

/**
 * Test if the two double values match; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param double1 the expected double
 * @param double2 the double produced by the students test code
 * @param accuracy_range the difference between produced and expected must be less than this for the test to pass
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_double(const char* msg, double double1, double double2, double accuracy_range);

/**
 * Test if the two char values match; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param char1 the expected char
 * @param char2 the char produced by the student's output
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_char(const char* msg, char char1, char char2);

/**
 * Test if the two pointer addresses match (not a string comparison, strictly addresses); 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param ptr1 the pointer that is expected
 * @param ptr2 the output pointer produced by the student's function
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_pointer(const char* msg, void* ptr1, void* ptr2);

/**
 * Test if the two pointers match based on the compare function pointer passed; 
 * This function is best used to compare specific types of structs; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param ptr1 the pointer that is expected
 * @param ptr2 the output pointer produced by the student's function
 * @param compare the function to call to compare the two pointers
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_callback(const char* msg, void* ptr1, void* ptr2, int (*compare)(void*, void*) );

/**
 * Test if the int arrays match for a certain length; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param arr1 the integer array that is expected
 * @param arr2 the output integer array produced by the student's function
 * @param length the length of the arrays to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_int_array(const char* msg, int arr1[], int arr2[], int length);

/**
 * Test if the char arrays match up to a certain length; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param arr1 the char array that is expected
 * @param arr2 the char integer array produced by the student's function
 * @param length the length of the arrays to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_char_array(const char* msg, char arr1[], char arr2[], int length);

/**
 * Test if the double arrays match up to a certain length; 
 * If doesn't match, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param arr1 the double array that is expected
 * @param arr2 the double array produced by the student's function
 * @param length the length of the arrays to test
 * @param accuracy_range the difference between expected and student-produced must be less than this to pass
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_double_array(const char* msg, double arr1[], double arr2[],
	int length, double accuracy_range);

/**
 * Test if the given int evaluates to true in a 'if' statement; 
 * If doesn't evaluate to true, fail the test and report the error
 * @param msg the message to print once the test has failed
 * @param boolean_expression the int expression to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_true(const char* msg, int boolean_expression);

/**
 * Aborts execution of the current test and moves on to the next test
 */
void fail();

/**
 * Aborts execution of the current test and moves on to the next test, write a message
 * @param msg the message to print once the test has failed
 */
void fail_msg(char* msg);

/**
 * Sanitize a char result so as not to be a crazy character that crashes the XML parser
 * @param output the char to be sanitized
 * @param message_array the array to write the message to
 * @return the message formatted, either with the char or with a message saying the char is invalid
 */
char* _sanitize_char(char output, char* message_array);

/**
 * Sanitize a string result so as not to be a crazy character that crashes the XML parser
 * @param output_string the string to be sanitized, which will have invalid characters replaced with '~'
 * @return the output_string array formatted, invalid characters replaced with '~'
 */
char* _sanitize_string(char* output_string);

/**
 * Test a function via a fork function.  Kill after 30 seconds if function has not completed
 * @param function the function to fork and make sure terminates
 * @returns 0 if unsuccessful, 1 if successful
 */
int fork_test_function(void (*function)());

void fill_stack_frame(int value);

#endif
