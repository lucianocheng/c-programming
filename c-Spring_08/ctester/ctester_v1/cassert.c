#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>
#include <math.h>

#include "ctester-defs.h"

/*extern char* current_error_buffer[ERRBUF_LEN];
extern int current_test;
extern int* test_error_flags;*/

extern TEST* current_test;

//extern jmp_buf curjump;

void fail()
{
	longjmp(current_test->curjump, TEST_FAIL);
}

void fail_msg(char* msg)
{
	sprintf(CURBUF, "* Detailed results for \"%s\":\n\tTest failed: %s",
		current_test->descrip, msg);
	SETERRFLAG();
	fail();
}

int assert_equals_string(const char* msg, char* str1, char* str2)
{
	//don't do anything if we've marked this test as having an error.
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(strcmp(str1, str2)!=0)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%s>, but was <%s>",
			current_test->descrip, msg, str1, str2);
		SETERRFLAG();
		fail();
	}
	return 1;
}

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
			current_test->descrip, msg, tmpstr1, tmpstr2);
		SETERRFLAG();
		fail();
	}
	return 1;
}


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

int assert_equals_char(const char* msg, char char1, char char2)
{
	//don't do anything if we've marked this test as having an error.
	if(CUR_ERR_FLAG) return 0;

	memset(CURBUF, 0, ERRBUF_LEN);

	if(char1!=char2)
	{
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Expected <%c>, but was <%c>",
			current_test->descrip, msg, char1, char2);
		SETERRFLAG();
		fail();
	}
	return 1;
}

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

int assert_equals_char_array(const char* msg, char arr1[], char arr2[], int length)
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
		sprintf(CURBUF, "* Detailed results for \"%s\":\n\tIncorrect value: %s - Character arrays not equal at index %d - "
			"Expected <%c>, but was <%c>", current_test->descrip, msg, ne_index,
			arr1[ne_index], arr2[ne_index]);
		SETERRFLAG();
	}
	return 1;
}

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


