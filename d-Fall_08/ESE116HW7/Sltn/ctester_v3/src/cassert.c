#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>
#include <math.h>

#include "ctester.h"
#include "cassert.h"

TEST* assert_current_test;

void set_assert_current_test(TEST* new_test){
	assert_current_test = new_test;
}

/**
 * Test if the two strings match, only test with null-terminated char arrays; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param str1 the expected string
 * @param str2 the string produced by the student's test code
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_string(const char* msg, char* str1, char* str2)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	if(strcmp(str1, str2)!=0)
	{
		sprintf(assert_current_test->error_buffer, 
				"* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%s>, but was <%s>",
				assert_current_test->descrip, msg, _sanitize_string(str1), _sanitize_string(str2));
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the two strings match up to 'length' characters; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param str1 the expected string
 * @param str2 the string produced by the student's test code
 * @param length the length of the string to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_nstring(const char* msg, char* str1, char* str2, int length)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	if(strncmp(str1, str2, length)!=0)
	{
		char* tmpstr1 = (char*) calloc(strlen(str1), sizeof(char));
		char* tmpstr2 = (char*) calloc(strlen(str2), sizeof(char));
		strncpy(tmpstr1, str1, length);
		strncpy(tmpstr2, str2, length);

		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%s>, but was <%s>",
				assert_current_test->descrip, msg, _sanitize_string(tmpstr1), _sanitize_string(tmpstr2));
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the two integers match; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param int1 the expected integer
 * @param int2 the integer produced by the students test code
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_int(const char* msg, int int1, int int2)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	if(int1!=int2)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%d>, but was <%d>",
				assert_current_test->descrip, msg, int1, int2);
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the two double values match; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param double1 the expected double
 * @param double2 the double produced by the students test code
 * @param accuracy_range the difference between produced and expected must be less than this for the test to pass
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_double(const char* msg, double double1, double double2, double accuracy_range)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	double val = fabs(double1 - double2);

	if(fabs(accuracy_range) < val)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%f>, but was <%f>",
				assert_current_test->descrip, msg, double1, double2);
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the two char values match; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param char1 the expected char
 * @param char2 the char produced by the student's output
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_char(const char* msg, char char1, char char2)
{
	char test_message[100];

	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	if(char1!=char2)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%c>, but was <%s>",
				assert_current_test->descrip, msg, char1, _sanitize_char(char2, test_message));
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the two pointer addresses match (not a string comparison, strictly addresses); 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param ptr1 the pointer that is expected
 * @param ptr2 the output pointer produced by the student's function
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_pointer(const char* msg, void* ptr1, void* ptr2)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	if(ptr1!=ptr2)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected address <%p>, but was <%p>",
				assert_current_test->descrip, msg, ptr1, ptr2);
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the two pointers match based on the compare function pointer passed; 
 * This function is best used to compare specific types of structs; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param ptr1 the pointer that is expected
 * @param ptr2 the output pointer produced by the student's function
 * @param compare the function to call to compare the two pointers
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_callback(const char* msg, void* ptr1, void* ptr2, int (*compare)(void*, void*))
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	if( compare(ptr1, ptr2) != 0)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Data structure at <%p> does not equal structure at <%p>",
				assert_current_test->descrip, msg, ptr1, ptr2);
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the int arrays match for a certain length; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param arr1 the integer array that is expected
 * @param arr2 the output integer array produced by the student's function
 * @param length the length of the arrays to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_int_array(const char* msg, int arr1[], int arr2[], int length)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	int equal=1;
	int ne_index=-1;
	int i;
	for(i=0; i<length; i++)
	{
		if(arr1[i]!=arr2[i])
		{
			equal=0;
			ne_index=i;
			break;
		}
	}

	if(!equal)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Integer arrays not equal at index %d - "
				"Expected <%d>, but was <%d>", assert_current_test->descrip, msg, ne_index,
				arr1[ne_index], arr2[ne_index]);
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the char arrays match up to a certain length; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param arr1 the char array that is expected
 * @param arr2 the char integer array produced by the student's function
 * @param length the length of the arrays to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_char_array(const char* msg, char arr1[], char arr2[], int length)
{
	char test_message[100];

	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	int equal=1;
	int ne_index=-1;
	int i;
	for(i=0; i<length; i++)
	{
		if(arr1[i]!=arr2[i])
		{
			equal=0;
			ne_index=i;
			break;
		}
	}

	if(!equal)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Character arrays not equal at index %d - "
				"Expected <%c>, but was <%s>", assert_current_test->descrip, msg, ne_index,
				arr1[ne_index], _sanitize_char(arr2[ne_index], test_message));
		assert_current_test->errflag=1;
	}
	return 1;
}

/**
 * Test if the double arrays match up to a certain length; 
 * If doesn't match, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param arr1 the double array that is expected
 * @param arr2 the double array produced by the student's function
 * @param length the length of the arrays to test
 * @param accuracy_range the difference between expected and student-produced must be less than this to pass
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_equals_double_array(const char* msg, double arr1[], double arr2[],
		int length, double accuracy_range)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	int equal=1;
	int ne_index=-1;
	int i;
	for(i=0; i<length; i++)
	{
		double val = fabs(arr1[i] - arr2[i]);
		if(val > fabs(accuracy_range) )
		{
			equal=0;
			ne_index=i;
			break;
		}
	}

	if(!equal)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Double arrays not equal at index %d - "
				"Expected <%f>, but was <%f>", assert_current_test->descrip, msg, ne_index,
				arr1[ne_index], arr2[ne_index]);
		assert_current_test->errflag=1;
		assert_fail();
	}
	return 1;
}

/**
 * Test if the given int evaluates to true in a 'if' statement; 
 * If doesn't evaluate to true, fail the test and report the error
 *
 * @param msg the message to print once the test has failed
 * @param boolean_expression the int expression to test
 * @return 0 if the test has an error, 1 if the test completed
 */
int assert_true(const char* msg, int boolean_expression)
{
	//don't do anything if we've marked this test as having an error.
	if(assert_current_test->errflag) return 0;

	memset(assert_current_test->error_buffer, 0, ERRBUF_LEN);

	if(!boolean_expression)
	{
		sprintf(assert_current_test->error_buffer, "* Detailed results for \"%s\":\n\tIncorrect value: %s",
				assert_current_test->descrip, msg);
		assert_current_test->errflag=1;
		assert_fail();
	}

	return 1;
}

/**
 * Aborts execution of the current test and moves on to the next test
 */
void assert_fail()
{
	longjmp(assert_current_test->curjump, TEST_FAIL);
}
