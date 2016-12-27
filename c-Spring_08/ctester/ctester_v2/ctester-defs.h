#ifndef _CTESTER_CTESTER_DEFS_H_
#define _CTESTER_CTESTER_DEFS_H_

#include <setjmp.h>

#define TRUE 1
#define FALSE 0
#define TEST_FAIL 42 /* any nonzero value will do, but so i dont confuse stuff i pick 42 */
/* For our purposes, we can assume we will never be testing insanely long strings */
#define ERRBUF_LEN 512
#define MAX_TAG_LEN 128
#define COMMENT_BUF_LEN 512
#define MIN_XMLBUF_LEN 1024

#define CURBUF current_test->error_buffer
#define SETERRFLAG() current_test->errflag=1
#define CUR_ERR_FLAG current_test->errflag

typedef int BOOL;

typedef enum { HOMEWORK, LAB, EXAM } PS_TYPE;

typedef struct _ct_str_buffer
{
	int len;
	int size;
	int resize_factor;
	char* buffer;
} _STRBUF;

typedef struct test_t
{
	const char* descrip;
	double max_score;
	double max_ec_score;
	double score;
	double ec_score;
	BOOL is_manual;
	BOOL is_ec;

	BOOL has_run;
	BOOL is_successful;

	BOOL errflag;
	char error_buffer[ERRBUF_LEN];

	jmp_buf curjump;
	void (*test_function)();
	struct test_t* next;
} TEST;


typedef struct problem_t
{
	const char* descrip;
	_STRBUF* comments;
	BOOL has_comments;
	int number;

	TEST* tests;
	TEST* manual_tests;
	struct problem_t* next;
} PROBLEM;



#endif
