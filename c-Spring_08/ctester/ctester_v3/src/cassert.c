#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ctester-defs.h"
#include "cassert.h"

extern TEST* current_test;

/**
 * Aborts execution of the current test and moves on to the next test
 */
void fail()
{
	longjmp(current_test->curjump, TEST_FAIL);
}

/**
 * Aborts execution of the current test and moves on to the next test, write a message
 *
 * @param msg the message to print once the test has failed
 */
void fail_msg(char* msg)
{
	sprintf(CURBUF, "* Detailed results for \"%s\":\n\tTest failed: %s",
		current_test->descrip, msg);
	SETERRFLAG();
	fail();
}

/**
 * Sanitize a char result so as not to be a crazy character that crashes the XML parser
 *
 * @param output the char to be sanitized
 * @param message_array the array to write the message to
 * @return the message formatted, either with the char or with a message saying the char is invalid
 */
char* _sanitize_char(char output, char* message_array){
  int char_num = (int)output;

  if(char_num >= 32 && char_num <= 126){
    message_array[0] = output;
    message_array[1] = '\0';
    return message_array;
  }

  strcpy(message_array, "INVALID_CHAR");
  return message_array;
}

/**
 * Sanitize a string result so as not to be a crazy character that crashes the XML parser
 *
 * @param output_string the string to be sanitized, which will have invalid characters replaced with '~'
 * @return the output_string array formatted, invalid characters replaced with '~'
 */
char* _sanitize_string(char* output_string){
  int i = 0;
  int test_char = 0;

  for(i = 0; i < strlen(output_string); i++){
    test_char = (int)output_string[i];
    if(test_char <= 31 || test_char >= 127 || test_char == '&'){
      output_string[i] = (char)126;
    }
  }
  
  return output_string;
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(strcmp(str1, str2)!=0)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%s>, but was <%s>",
			current_test->descrip, msg, str1, _sanitize_string(str2));
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(strncmp(str1, str2, length)!=0)
	{
		char* tmpstr1 = (char*) calloc(strlen(str1), sizeof(char));
		char* tmpstr2 = (char*) calloc(strlen(str2), sizeof(char));
		strncpy(tmpstr1, str1, length);
		strncpy(tmpstr2, str2, length);

		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%s>, but was <%s>",
			current_test->descrip, msg, tmpstr1, _sanitize_string(tmpstr2));
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(int1!=int2)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%d>, but was <%d>",
			current_test->descrip, msg, int1, int2);
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	double val = fabs(double1 - double2);

	if(fabs(accuracy_range) < val)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%f>, but was <%f>",
			current_test->descrip, msg, double1, double2);
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(char1!=char2)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%c>, but was <%s>",
			current_test->descrip, msg, char1, _sanitize_char(char2, test_message));
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(ptr1!=ptr2)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected address <%p>, but was <%p>",
			current_test->descrip, msg, ptr1, ptr2);
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if( compare(ptr1, ptr2) != 0)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Data structure at <%p> does not equal structure at <%p>",
			current_test->descrip, msg, ptr1, ptr2);
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

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
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Integer arrays not equal at index %d - "
			"Expected <%d>, but was <%d>", current_test->descrip, msg, ne_index,
			arr1[ne_index], arr2[ne_index]);
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

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
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Character arrays not equal at index %d - "
			"Expected <%c>, but was <%s>", current_test->descrip, msg, ne_index,
			arr1[ne_index], _sanitize_char(arr2[ne_index], test_message));
		SETERRFLAG();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

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
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Double arrays not equal at index %d - "
			"Expected <%f>, but was <%f>", current_test->descrip, msg, ne_index,
			arr1[ne_index], arr2[ne_index]);
		SETERRFLAG();
		fail();
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
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(!boolean_expression)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s",
			current_test->descrip, msg);
		SETERRFLAG();
		fail();
	}

	return 1;
}

/**
 * Test a function via a fork function.  Tries 5 forks. Kills after ~30 seconds if function has not completed
 * @param function The function to pass to the test to see if it crashes
 * @return 1 if successful, 0 if failed
 */
int fork_test_function(void (*function)())
{
  const int child_count = 1;
  int i = 0, j = 0;
  int jmpres = 0;
  int result_pid[child_count];
  int wstat[child_count];
  int fork_test_pid[child_count];
  int child_exited_count = 0;

  // Create the 10 children
  for(j = 0; j < child_count; j++){
    fork_test_pid[j] = fork();
    switch(fork_test_pid[j]){
      case -1:
        perror("ERROR AT FORK TESTER\n");
        exit(EXIT_FAILURE);
        break;
      case 0:
        for(i = 0; i < 5; i++){
          fill_stack_frame(i);
          jmpres = setjmp(current_test->curjump);
          if(jmpres != TEST_FAIL){
            (function)();
          }
        }
        exit(EXIT_SUCCESS);
        break;
      default:
        break;
    }
  }

  // Poll the 5 children for 30 seconds, exit the loop if all the children exit
  for(i = 0; i < 300 && child_exited_count < child_count; i++){
    usleep(100);
    for(j = 0; j < child_count; j++){
      result_pid[j] = wait4(fork_test_pid[j], &wstat[j], WNOHANG, (struct rusage *)NULL);
      if(result_pid[j] != 0) child_exited_count++;
    }
  }

  // Kill off all children unconditionally
  for(i = 0; i < child_count; i++){
    kill(fork_test_pid[i], SIGKILL);
  }

  // Check children exit status'.  If any one is out of line, return failure (0)
  for(i = 0; i < child_count; i++){
    if(!(result_pid[i] != 0 && WIFEXITED(wstat[i]) > 0 && WEXITSTATUS(wstat[i]) == EXIT_SUCCESS)){
      return 0;
    }
  }
  
  // Return success (1)
  return 1;
}

void fill_stack_frame(int value){
  int filler[1000];
  int i = 0;
  for(i = 0; i < 1000; i++){
    filler[i] = value;
  }
}
