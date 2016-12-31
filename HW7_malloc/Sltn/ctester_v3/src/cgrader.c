#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include "test.h"
#include "cgrader.h"
#include "cassert.h"
#include "ctester.h"
#include "problem.h"
#include "stringbuf.h"
#include "linked_list.h"

LINKED_LIST* problems;

extern char* ct_get_file_suffix();
extern PS_TYPE ct_get_problem_set_type();
extern int ct_get_problem_set_num();

/**
 * Gets the string of the problem set type from a PS_TYPE object
 *
 * @param type the PS_TYPE object to decode; returns a string based on this
 * @return "homework" if type is a HOMEWORK, "exam" if type is a EXAM, "lab" if type is a LAB
 */

char* _pstype_to_str(PS_TYPE type)
{
	switch(type)
	{
	case HOMEWORK:
		return "homework";

	case LAB:
		return "lab";

	case EXAM:
		return "exam";

	default:
		return "";
	}
}

/**
 * Print the usage message for the given program, printed if the program is missing arguments
 * 
 * @param prog the program name, as a string
 */
void printUsage(char* prog)
{
	printf("%s usage:\n", prog);
	printf("\t%s *STUDENT_ID *latefile=<late_submission_file>\n", prog);
	printf("Arguments marked with a * are optional. If you wish for a .tester ");
	printf("file to be produced you must also provide STUDENT_ID.\n");
	printf("If tested solution is submitted late, you must specify the LATE_SUBMISSION file as well.\n");
}

/**
 * Run every test as set up in the PROBLEM linked list
 *
 * @param argc the size of argv
 * @param argv the collection of arguments to the program
 */
void run_all_tests(int argc, char* argv[])
{
	char* student="";
	char* latefile=NULL;
	long late_ts;
	int i;
	
	if(argc > 3){
		printUsage(argv[0]);
		exit(0);
	}
	else if(argc >= 2){
		student = argv[1];
		if(argc == 3 && strncmp(argv[2], "*latefile=", 10) == 0)
		{
			latefile = argv[2] + 10;
		}
	}

	if(problems->size == 0){
		printf("No tests to run...\n");
		exit(1);
	}

	//TODO: when it's time to add multiple late deadlines, open the LATE_SUBMISSION file

  late_ts = (latefile==NULL ? 0 : 1);

	_STRBUF* xml_buffer = _strbuf_init(MIN_XMLBUF_LEN);

	_strbuf_append(xml_buffer, "<?xml version=\"1.0\"?>\n");
	_strbuf_append(xml_buffer, "<!DOCTYPE tester SYSTEM \"/home2/c/cse1xx/misc/tester.dtd\">\n");

	char* suffix = ct_get_file_suffix();

	char testlist_tag[MAX_TAG_LEN*2];
	
	sprintf(testlist_tag, "<testlist problem_set_type=\"%s\" problem_set_number=\"%d\"",
			_pstype_to_str(ct_get_problem_set_type()), ct_get_problem_set_num());
	
	if(suffix==NULL || strcmp(suffix, "")==0){
		strcat(testlist_tag, " file_suffix=\"");
		strcat(testlist_tag, suffix);
		strcat(testlist_tag, "\"");
	}
	strcat(testlist_tag, ">\n");

	_strbuf_append(xml_buffer, testlist_tag);

	char student_tag[MAX_TAG_LEN];
	sprintf(student_tag, "<student username=\"%s\">\n", student);
	_strbuf_append(xml_buffer, student_tag);

	PROBLEM* temp_prob;
	for(i = 0; i < problems->size; i++){
		ll_get(problems, i, (void**)&temp_prob);
		run_problem_tests(temp_prob, late_ts, xml_buffer);
	}

	// Finish off the XML grading file
	_strbuf_append(xml_buffer, "</student></testlist>\n");

	if(strcmp(student, "") != 0)
	{
		char* filename = _calloc_or_die(strlen(student)+strlen(suffix)+10, sizeof(char),
				"Couldn't calloc name of XML file");
		strcat(filename, student);
		strcat(filename, suffix);
		strcat(filename, ".tester");
		
		FILE* file = fopen((const char*)filename, "w");
		fwrite(xml_buffer->buffer, sizeof(char), strlen(xml_buffer->buffer), file);
		
		fclose(file);
		free(filename);
	}

	_strbuf_free(xml_buffer);
}

/**
 * Cleans up after all tests have been run, cleans up all global variables
 */
void clean_up(){
	ll_free(problems);
}

PROBLEM* add_new_problem(const char* name, int number){
	static BOOL problems_initialized = FALSE;
	PROBLEM* prob;
	
	if(problems_initialized == FALSE){
		problems = ll_create(&problem_free);
		problems_initialized = TRUE;
	}
	
	prob = problem_initialize(name, number);
	ll_push_back(problems, prob);
	
	return prob;
}


/**
 * Add a new test to the given problem, given the function to test
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_test(PROBLEM* problem, const char* description, double points, void (*test_function)() )
{
	TEST* test = test_create(description, test_function);
	test->is_manual = FALSE;
	test->is_ec = FALSE;
	test->max_score = points;
	test->max_ec_score = 0;
	
	ll_push_back(problem->tests, test);
}

/**
 * Supplied for backwards compatibility, all tests are now fork tests
 * 
 * Add a new test to the given problem with a fork test, given the function to test
 * A fork test means that the program will fork off and test and see if the function completes
 *        in 30 seconds.  If it does not, it fails the test.
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_fork_test(PROBLEM* problem, const char* description, double points, void (*test_function)() )
{
	add_new_test(problem, description, points, test_function);
}


/**
 * Add a new extra credit to the given problem, given the function to test
 *
 * @param problem the problem to which to add the test
 * @param description a description of the test to add to the problem
 * @param points the number of extra credit points to attribute to the test
 * @param test_function the function that is called and associated with this test
 */
void add_new_ec_test(PROBLEM* problem, const char* description, double points, void (*test_function)() )
{
	TEST* test = test_create(description, test_function);
	test->is_manual = FALSE;
	test->is_ec = TRUE;
	test->max_score = 0;
	test->max_ec_score = points;
	
	ll_push_back(problem->tests, test);
}

/**
 * Add a manual grade to the given problem.  A manual grade is a grade you enter at the keyboard, not tested by the comp
 *
 * @param problem the problem to add the manual grade to
 * @param description a description of the manual grade
 * @param points the points associated with this manual grade
 * @param is_extra_credit is this manual grade extra credit?
 */
void add_manual_grade(PROBLEM* problem, const char* description, int points, BOOL is_extra_credit)
{
	TEST* test = test_create(description, &_get_manual_grade);
	test->is_manual = TRUE;	
	test->is_ec = is_extra_credit;
	test->max_score = (is_extra_credit ? 0 : points);
	test->max_ec_score = (is_extra_credit ? points : 0);
	
	ll_push_back(problem->tests, test);
}

/**
 * Set whether or not this problem has comments, the value of set is set to has_comments
 *
 * @param problem the problem to set if there are comments
 * @param set TRUE if the problem does have comments, FALSE if it does not
 */
void set_comments(PROBLEM* problem, BOOL set)
{
	problem->has_comments = set;
}
