#ifndef _CTESTER_CASSERT_H_
#define _CTESTER_CASSERT_H_

/**
 * Asserts two null-terminated strings are equal.
 */
int assert_equals_string(const char* msg, char* str1, char* str2);

/**
 * Asserts the first n characters of two strings are equal
 */
int assert_equals_nstring(const char* msg, char* str1, char* str2, int length);

int assert_equals_int(const char* msg, int int1, int int2);

int assert_equals_double(const char* msg, double double1, double double2, double accuracy_range);

int assert_equals_char(const char* msg, char char1, char char2);

int assert_equals_pointer(const char* msg, void* ptr1, void* ptr2);

int assert_equals_callback(const char* msg, void* ptr1, void* ptr2, int (*compare)(void*, void*) );

int assert_equals_int_array(const char* msg, int arr1[], int arr2[], int length);

int assert_equals_char_array(const char* msg, char arr1[], char arr2[], int length);

int assert_equals_double_array(const char* msg, double arr1[], double arr2[],
	int length, double accuracy_range);

int assert_true(const char* msg, int boolean_expression);

/**
 * Aborts execution of the current test and moves on to the next test
 */
void fail();

/**
 * Same as fail() except lets you provide a message.
 */
void fail_msg(char* msg);

#endif
