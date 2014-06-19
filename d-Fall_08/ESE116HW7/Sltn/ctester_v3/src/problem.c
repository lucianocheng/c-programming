#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include "cassert.h"
#include "ctester.h"
#include "problem.h"
#include "stringbuf.h"
#include "test.h"

/**
 * Add a new PROBLEM to the problem set to be tested, initialize the PROBLEM; 
 * A PROBLEM is one grade that is eventually loaded into the SQL database for the assignment
 *
 * @param description A description of the problem
 * @param number The problem number
 */
PROBLEM* problem_initialize(const char* description, int number)
{
	PROBLEM* prob = _calloc_or_die(1, sizeof(PROBLEM), "Couldn't calloc problem\n");
	prob->descrip = description;
	prob->number = number;
	prob->has_comments = FALSE;
	prob->comments = NULL;
	prob->tests = ll_create(&free);
	
	return prob;
}

void problem_free(void* problem){
	PROBLEM* prbptr = (PROBLEM*)problem;
	
	if(prbptr->comments != NULL){
		_strbuf_free(prbptr->comments);
	}
	
	if(prbptr->tests != NULL){
		ll_free(prbptr->tests);
	}
	
	if(prbptr != NULL){
		free(prbptr);
	}
}
