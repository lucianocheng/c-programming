#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>


#include "cassert.h"
#include "ctester.h"
#include "problem.h"
#include "stringbuf.h"
#include "test.h"
#include "linked_list.h"

extern LINKED_LIST* problems;

/**
 * Get a manual grade from the user
 * 
 * Prompt the user for a manual grade
 */
void _get_manual_grade(TEST* test)
{
	double max=0;
	if(test->is_ec){
		printf(" Extra Credit:");
		max = test->max_ec_score;
	}
	else
		max = test->max_score;
	printf(" Grade for %s (out of %.1lf): ", test->descrip, max);
	double entered = -1;
	while(entered < 0 || entered > max)
	{
		scanf("%lf", &entered);
		if(entered < 0 || entered > max)
			printf("\nPlease re-enter a value in the correct range (0 to %.1lf): ", max);
	}
	printf("\n");

	if(test->is_ec)
		test->ec_score = entered;
	else
		test->score = entered;
}


/**
 * Print the comments on a particular problem
 *
 * @param problem the problem of which comments to print
 */
void _get_comments(PROBLEM* problem)
{
	printf("Comments for question #%d:\n", problem->number);
	printf("---------------------------------\n");
	printf("Comments can be multiline, enter the string $$$ to end (max 512 chars per line).\n");
	char buf[COMMENT_BUF_LEN];
	_STRBUF* comments = _strbuf_init(COMMENT_BUF_LEN);

	do
	{
		scanf("%s", buf);
		if(strcmp(buf,"$$$")==0) break;
		_strbuf_append(comments, buf);
		_strbuf_append(comments, "\n");
	} while(TRUE);

	problem->comments = comments;
}

void run_normal_test(TEST* test, _STRBUF* xml_buffer){
	char testdesc[MAX_TAG_LEN];
	
	sprintf(testdesc, "  <test max_score=\"%.1lf\" max_ec_score=\"%.1lf\">\n",
			test->max_score, test->max_ec_score);
	set_assert_current_test(test);		
	_strbuf_append(xml_buffer, testdesc);
	_strbuf_append(xml_buffer, "   <desc>");
	char* escaped_desc = xml_escape((char*)test->descrip);
	_strbuf_append(xml_buffer, escaped_desc);
	_strbuf_append(xml_buffer, "</desc>\n");

	if(test->is_ec){
		printf(" Extra Credit:");
	}		

	printf(" Test - %s: ", test->descrip);

	if(fork_test_function(test) == FAILED)
	{
		test->has_run = TRUE;
		test->errflag = TRUE;
		test->is_successful = FALSE;
		printf(" did not pass - 0 points\n");

		if(test->is_ec)
			test->ec_score = 0;
		else
			test->score = 0;
	}
	else{
		test->has_run = TRUE;				
		test->is_successful = TRUE;

		if(test->is_ec){
			test->ec_score = test->max_ec_score;
			printf(" Passed - %.1lf points\n", test->ec_score);
		}
		else{
			test->score = test->max_score;
			printf(" Passed - %.1lf points\n", test->score);
		}
	}

	char scoretags[MAX_TAG_LEN];
	sprintf(scoretags, "   <score>%.1lf</score>\n   <ec_score>%.1lf</ec_score>\n",
			test->score, test->ec_score);
	_strbuf_append(xml_buffer, scoretags);

	if(test->errflag)
	{
		_strbuf_append(xml_buffer, "   <error>");
		_strbuf_append(xml_buffer, xml_escape(test->error_buffer));
		_strbuf_append(xml_buffer, "\n</error>\n");
	}
	_strbuf_append(xml_buffer, "  </test>\n");
}

void run_manual_test(TEST* test, _STRBUF* xml_buffer){
	set_assert_current_test(test);		
	char testdesc[MAX_TAG_LEN];
	sprintf(testdesc, "  <test max_score=\"%.1lf\" max_ec_score=\"%.1lf\">\n",
			test->max_score, test->max_ec_score);
	_strbuf_append(xml_buffer, testdesc);
	_strbuf_append(xml_buffer, "   <desc>Grade for ");
	_strbuf_append(xml_buffer, xml_escape((char*)test->descrip));

	char tmpbuf[30];
	if(test->is_ec)
		sprintf(tmpbuf, " (out of %.1lf)", test->max_ec_score);
	else
		sprintf(tmpbuf, " (out of %.1lf)", test->max_score);
	
	_strbuf_append(xml_buffer, tmpbuf);
	_strbuf_append(xml_buffer, "</desc>\n");

	test->has_run = TRUE;
	test->test_function();
	test->is_successful = TRUE;

	char scoretags[MAX_TAG_LEN];
	sprintf(scoretags, "   <score>%.1lf</score>\n   <ec_score>%.1lf</ec_score>\n",
			test->score, test->ec_score);
	_strbuf_append(xml_buffer, scoretags);

	if(test->errflag){
		_strbuf_append(xml_buffer, "   <error>");
		_strbuf_append(xml_buffer, xml_escape(test->error_buffer));
		_strbuf_append(xml_buffer, "\n</error>\n");
	}
	_strbuf_append(xml_buffer, "  </test>\n");
}

/**
 * Run all the tests, passing the first problem in the linked list to the tester; 
 * Not thread safe
 *
 * @param problem the first problem in the PROBLEM linked list
 * @param late_ts The late timestamp, in unix epoch time
 * @param xml_buffer the string buffer to print the xml output
 */
void run_problem_tests(PROBLEM* problem, long late_ts, _STRBUF* xml_buffer){
	double total_max_score=0;
	double total_max_ec_score=0;

	char probdesc[MAX_TAG_LEN];
	int i = 0;
	TEST* temp_test;

	// Add up maximum points
	for(i = 0; i != problem->tests->size; i++){
		ll_get(problem->tests, i, (void**)&temp_test);
		
		total_max_score += temp_test->max_score;
		total_max_ec_score += temp_test->max_ec_score;
	}

	// TODO: FIX THIS
	
	sprintf(probdesc, 
			" <problem problem_number=\"%d\" late-timestamp=\"%ld\" max_score=\"%.1lf\" max_ec_score=\"%.1lf\">\n",
			problem->number, late_ts, total_max_score, total_max_ec_score);
	_strbuf_append(xml_buffer, probdesc);
	_strbuf_append(xml_buffer, "  <desc>");
	_strbuf_append(xml_buffer, xml_escape((char*)problem->descrip));
	_strbuf_append(xml_buffer, "</desc>\n");

	printf("Question #%d: %s\n", problem->number, problem->descrip);
	printf("---------------------------\n");

	// Run tests
	for(i = 0; i != problem->tests->size; i++){
		ll_get(problem->tests, i, (void**)&temp_test);
		if(temp_test->is_manual){
			run_manual_test(temp_test, xml_buffer);
		}
		else{
			run_normal_test(temp_test, xml_buffer);
		}
	}

	printf("---------------------------\n");

	// Print out errors
	BOOL has_errors=FALSE;
	for(i = 0; i != problem->tests->size; i++){
		ll_get(problem->tests, i, (void**)&temp_test);
		if(temp_test->errflag && temp_test->error_buffer != NULL){
			printf("%s\n", temp_test->error_buffer);
			has_errors=TRUE;
		}
	}
	
	if(has_errors){
		printf("---------------------------\n");
	}
	
	if(problem->has_comments){
		_get_comments(problem);
		if(problem->comments!=NULL && problem->comments->buffer!=NULL)
		{
			_strbuf_append(xml_buffer, "  <comment>");
			_strbuf_append(xml_buffer, xml_escape(problem->comments->buffer));
			_strbuf_append(xml_buffer, "\n</comment>\n");
		}
	}
	_strbuf_append(xml_buffer, " </problem>\n");
}

/**
 * Test a function via a fork function.  Tries 5 forks. Kills after ~30 seconds if function has not completed
 * @param function The function to pass to the test to see if it crashes
 * @return 1 if successful, 0 if failed
 */
int fork_test_function(TEST* test){
	int i = 0;
	int jmpres = 0;
	int xml_pipe[2];
	
	// Set the test equal to the current test
	set_assert_current_test(test);		
	
	// create the pipe child->parent
  pipe(xml_pipe);
  
  test->test_pid = fork();
	switch(test->test_pid){
	
	// Error Stuff
	case -1:
		perror("ERROR AT FORK TESTER\n");
		exit(EXIT_FAILURE);
		break;
		
	// Child Stuff
	case 0:		
		close(xml_pipe[0]);
		
		strcpy(test->error_buffer, "");
				
		for(i = 0; i < 5; i++){
			fill_stack_frame(i*1000);
			
			jmpres = setjmp(test->curjump);
			if(jmpres == TEST_FAIL){
				write(xml_pipe[1], test->error_buffer, 
						strlen(test->error_buffer) + 1);
				exit(EXIT_FAILURE);
			}
			else{
				(test->test_function)();
			}
		}
		exit(EXIT_SUCCESS);
		break;
		
	// Parent Stuff
	default:
		break;
	}

	close(xml_pipe[1]);
	
	
	/*
	int flags;
  if (-1 == (flags = fcntl(xml_pipe[0], F_GETFL, 0))) flags = 0;
  fcntl(xml_pipe[0], F_SETFL, flags | O_NONBLOCK);
	*/
	
	int error_char_count = 0;
  char read_buffer;
  int read_amount = -1;
	int result_pid = 0;
	
	// Poll the child for 30 seconds, exit the loop if all the children exit
	for(i = 0; i < 10 * 30 * 100 && result_pid == 0; i++){
		usleep(10000);
		result_pid = wait4(test->test_pid, 
				&(test->wstat), WNOHANG, (struct rusage *)NULL);
	}
	
	// Kill off the child unconditionally
	kill(test->test_pid, SIGKILL);
	
	while(read_amount != 0){
		read_amount = read(xml_pipe[0], &read_buffer, 1);
		(test->error_buffer)[error_char_count++] = read_buffer;
	}
	
	// Test timed out
	if(!(result_pid != 0 && WIFEXITED(test->wstat) > 0)){
		set_fail_msg(test, "Function crashed, looped infinitely or improperly prompted for user input");
		return FAILED;
	}
	
	// Test failed normally
	if(WEXITSTATUS(test->wstat) != EXIT_SUCCESS){
		return FAILED;
	}

	// Test succeeded
	return PASSED;
}

void fill_stack_frame(int value){
	int filler[10000];
	int i = 0;
	for(i = 0; i < 10000; i++){
		filler[i] = value;
	}
}

/**
 * Aborts execution of the current test and moves on to the next test, write a message
 *
 * @param msg the message to print once the test has failed
 */
void set_fail_msg(TEST* test, char* msg){
	sprintf(test->error_buffer, "* Detailed results for \"%s\":\n\tTest failed: %s",
			test->descrip, msg);
}
