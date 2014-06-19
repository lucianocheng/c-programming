#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include "stringbuf.h"
#include "test.h"
#include "linked_list.h"

/**
 * PROBLEM - A struct that holds a series of tests connected to a given problem; 
 * The PROBLEMS link together like a linked list
 */
typedef struct
{
	const char* descrip;
	_STRBUF* comments;
	BOOL has_comments;
	int number;

	LINKED_LIST* tests;
} PROBLEM;

PROBLEM* problem_initialize(const char* description, int number);

void problem_free(void* problem);

#endif
