#ifndef _TEST_H_
#define _TEST_H_

#include <setjmp.h>
#include "stringbuf.h"
#include "bool.h"

#define ERRBUF_LEN 512

typedef struct{
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
	
	int test_pid;
	int wstat;

	jmp_buf curjump;
	void (*test_function)();
	//struct test_t* next;
} TEST;

TEST* test_create(const char* description, void (*test_function)());

#endif

