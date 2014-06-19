#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

#include "ctester-defs.h"
#include "cassert.h"
#include "ctester.h"

PROBLEM* all_problems;

TEST* current_test;

extern char* ct_get_file_suffix();
extern PS_TYPE ct_get_problem_set_type();
extern int ct_get_problem_set_num();

/**
 * Calloc the requested memory or exit the program
 *
 * @param num the number of units to index
 * @param size the size of a given unit
 * @param msg the message to print if the calloc fails
 */
void* _calloc_or_die(size_t num, size_t size, const char* msg)
{
	void* ptr = calloc(num, size);
	if(ptr==NULL)
	{
		fprintf(stderr, msg);
		exit(1);
	}
	return ptr;
}

/**
 * Add a new PROBLEM to the problem set to be tested, initialize the PROBLEM; 
 * A PROBLEM is one grade that is eventually loaded into the SQL database for the assignment
 *
 * @param description A description of the problem
 * @param number The problem number
 */
PROBLEM* add_new_problem(const char* description, int number)
{
	PROBLEM* prob = _calloc_or_die(1, sizeof(PROBLEM), "Couldn't calloc problem\n");
	prob->descrip = description;
	prob->number = number;
	prob->has_comments = FALSE;
	prob->comments = NULL;
	prob->tests = NULL;
	prob->manual_tests = NULL;
	prob->next = NULL;

	if(all_problems == NULL)
	{
		all_problems = prob;
	}
	else
	{
		//advance to last problemo
		PROBLEM* ptr;
		for(ptr = all_problems; ptr->next!=NULL; ptr = ptr->next);
		ptr->next = prob;
	}

	return prob;
}

/**
 * Add a new test to a given problem, a problem is a collection of tests; 
 * This is not the function that is called by the test program, this is an internal function
 *
 * @param problem the problem to which to add the test
 * @param description the description of the problem
 * @param test_function the function that the test will call
 * @param list the test list to add the test to
 * @return the test that is created
 */
TEST* _add_new_test(PROBLEM* problem, const char* description, void (*test_function)(), TEST** list )
{
	TEST* test = _calloc_or_die(1, sizeof(TEST), "Couldn't calloc test\n");
	test->descrip = description;
	test->test_function = test_function;
	test->next = NULL;
	test->errflag = FALSE;
	test->has_run = FALSE;
	test->is_successful = FALSE;
        test->is_fork_test = FALSE;
	test->score = 0;
	test->ec_score = 0;

	if(*list == NULL)
	{
		*list = test;
	}
	else
	{
		TEST* ptr;
		for(ptr = *list; ptr->next!=NULL; ptr = ptr->next);
		ptr->next = test;
	}

	return test;
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
	TEST* test = _add_new_test(problem, description, test_function, &(problem->tests));
	test->is_manual = FALSE;
	test->is_ec = FALSE;
        test->is_fork_test = FALSE;
	test->max_score = points;
	test->max_ec_score = 0;
}

/**
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
        TEST* test = _add_new_test(problem, description, test_function, &(problem->tests));
        test->is_manual = FALSE;
        test->is_ec = FALSE;
        test->is_fork_test = TRUE;
        test->max_score = points;
        test->max_ec_score = 0;
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
	TEST* test = _add_new_test(problem, description, test_function, &(problem->tests));
	test->is_manual = FALSE;
	test->is_ec = TRUE;
	test->max_score = 0;
	test->max_ec_score = points;
}

/**
 * Add a new manual grade, this is the system function, not called by the grading program; not thread safe
 */
void _get_manual_grade()
{
	TEST* test = current_test;
	double max=0;
	if(test->is_ec)
	{
		printf(" Extra Credit:");
		max = test->max_ec_score;
	}
	else
		max = test->max_score;
	printf(" Grade for %s (out of %.1lf): ", current_test->descrip, max);
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
 * Add a manual grade to the given problem.  A manual grade is a grade you enter at the keyboard, not tested by the comp
 *
 * @param problem the problem to add the manual grade to
 * @param description a description of the manual grade
 * @param points the points associated with this manual grade
 * @param is_extra_credit is this manual grade extra credit?
 */
void add_manual_grade(PROBLEM* problem, const char* description, int points, BOOL is_extra_credit)
{
	TEST* test = _add_new_test(problem, description, &_get_manual_grade, &(problem->manual_tests));
	test->is_manual = TRUE;
	test->is_ec = is_extra_credit;
	test->max_score = (is_extra_credit ? 0 : points);
	test->max_ec_score = (is_extra_credit ? points : 0);
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

/**
 * Create a new _STRBUF struct, initilize the values
 *
 * @param min the minimum size of the starting string buffer
 */
_STRBUF* _strbuf_init(int min)
{
	_STRBUF* buf = _calloc_or_die(1, sizeof(_STRBUF), "Couldn't calloc internal buffer");
	buf->resize_factor = 1;
	buf->len = min;
	buf->buffer = _calloc_or_die(min, sizeof(char), "Couldn't calloc buffer string");

	return buf;
}

/**
 * Append a string append_str on to the end of the string buffer 'buf'
 *
 * @param buf the buffer to add the string on to
 * @param append_str the string to append
 */
void _strbuf_append(_STRBUF* buf, char* append_str)
{
	int size = strlen(append_str);
	if(buf->size+size > buf->len)
	{
		while(buf->resize_factor * buf->len < buf->size + size)
		{
			buf->resize_factor *= 2;
		}
		char* newbuf = _calloc_or_die(buf->resize_factor * buf->len, sizeof(char), "Couldn't recalloc buffer");
		strcpy(newbuf, buf->buffer);
		strcpy(newbuf+buf->size, append_str);

		char* tmpold = buf->buffer;
		buf->buffer = newbuf;
		free(tmpold);
		buf->len *= buf->resize_factor;
		buf->size += strlen(append_str);
	}
	else
	{
		strcpy(buf->buffer+buf->size, append_str);
		buf->size += strlen(append_str);
	}
}

/**
 * free a stringbuffer cleanly
 *
 * @param buf the string buffer to free
 */
void _strbuf_free(_STRBUF* buf)
{
	free(buf->buffer);
	free(buf);
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

/**
 * Run all the tests, passing the first problem in the linked list to the tester; 
 * Not thread safe
 *
 * @param problem the first problem in the PROBLEM linked list
 * @param late_ts The late timestamp, in unix epoch time
 * @param xml_buffer the string buffer to print the xml output
 */
void run_tests(PROBLEM* problem, long late_ts, _STRBUF* xml_buffer)
{
	double total_max_score=0;
	double total_max_ec_score=0;


	char probdesc[MAX_TAG_LEN];
	TEST* test;

	//add up max points first
	for(test = problem->tests; test!=NULL; test = test->next)
	{
		total_max_score += test->max_score;
		total_max_ec_score += test->max_ec_score;
	}

	sprintf(probdesc, " <problem problem_number=\"%d\" late-timestamp=\"%ld\" max_score=\"%.1lf\" max_ec_score=\"%.1lf\">\n",
		problem->number, late_ts, total_max_score, total_max_ec_score);
	_strbuf_append(xml_buffer, probdesc);
	_strbuf_append(xml_buffer, "  <desc>");
	char* escape_probdesc=xml_escape((char*)problem->descrip);
	_strbuf_append(xml_buffer, escape_probdesc);
	_strbuf_append(xml_buffer, "</desc>\n");


	printf("Question #%d: %s\n", problem->number, problem->descrip);
	printf("---------------------------\n");

	//normal tests
	for(test = problem->tests; test!=NULL; test = test->next)
	{
		current_test = test;
		char testdesc[MAX_TAG_LEN];
		sprintf(testdesc, "  <test max_score=\"%.1lf\" max_ec_score=\"%.1lf\">\n",
			test->max_score, test->max_ec_score);
		_strbuf_append(xml_buffer, testdesc);
		_strbuf_append(xml_buffer, "   <desc>");
		char* escaped_desc = xml_escape((char*)test->descrip);
		_strbuf_append(xml_buffer, escaped_desc);
		_strbuf_append(xml_buffer, "</desc>\n");

		if(test->is_ec){
			printf(" Extra Credit:");
                }		

                printf(" Test - %s: ", test->descrip);

		int jmpres = setjmp(test->curjump);
		if(jmpres == TEST_FAIL)
		{
			test->is_successful = FALSE;
			printf(" did not pass - 0 points\n");

			if(test->is_ec)
				test->ec_score = 0;
			else
				test->score = 0;
		}
		else
		{
			test->has_run = TRUE;
                        if(test->is_fork_test == FALSE || fork_test_function(test->test_function) == 1){

			       (test->test_function)();
			       //if you get here, longjmp has not been called.
			       test->is_successful = TRUE;
  
			       if(test->is_ec)
			       {
				    test->ec_score = test->max_ec_score;
				    printf(" Passed - %.1lf points\n", test->ec_score);
			       }
			       else
			       {
			            test->score = test->max_score;
				    printf(" Passed - %.1lf points\n", test->score);
			       }
                        }
                        else{
                               fail_msg("Function crashed, looped infinitely or improperly prompted for user input");
                        }
		}

		char scoretags[MAX_TAG_LEN];
		sprintf(scoretags, "   <score>%.1lf</score>\n   <ec_score>%.1lf</ec_score>\n",
			test->score, test->ec_score);
		_strbuf_append(xml_buffer, scoretags);

		if(test->errflag)
		{
			_strbuf_append(xml_buffer, "   <error>");
			char* esc_errbuf = xml_escape(test->error_buffer);
			_strbuf_append(xml_buffer, esc_errbuf);
			_strbuf_append(xml_buffer, "\n</error>\n");
		}
		_strbuf_append(xml_buffer, "  </test>\n");

	}

	//manual grades
	for(test = problem->manual_tests; test!=NULL; test = test->next)
	{
		current_test = test;
		char testdesc[MAX_TAG_LEN];
		sprintf(testdesc, "  <test max_score=\"%.1lf\" max_ec_score=\"%.1lf\">\n",
			test->max_score, test->max_ec_score);
		_strbuf_append(xml_buffer, testdesc);
		_strbuf_append(xml_buffer, "   <desc>Grade for ");
		char* escaped_desc = xml_escape((char*)test->descrip);
		_strbuf_append(xml_buffer, escaped_desc);
		char tmpbuf[30];
		if(test->is_ec)
			sprintf(tmpbuf, " (out of %.1lf)", test->max_ec_score);
		else
			sprintf(tmpbuf, " (out of %.1lf)", test->max_score);
		_strbuf_append(xml_buffer, tmpbuf);
		_strbuf_append(xml_buffer, "</desc>\n");

		//no need for longjmp for manual grades
		test->has_run = TRUE;
		test->test_function();
		//if you get here, longjmp has not been called.
		test->is_successful = TRUE;

		char scoretags[MAX_TAG_LEN];
		sprintf(scoretags, "   <score>%.1lf</score>\n   <ec_score>%.1lf</ec_score>\n",
			test->score, test->ec_score);
		_strbuf_append(xml_buffer, scoretags);

		if(test->errflag)
		{
			_strbuf_append(xml_buffer, "   <error>");
			char* esc_errbuf = xml_escape(test->error_buffer);
			_strbuf_append(xml_buffer, esc_errbuf);
			_strbuf_append(xml_buffer, "\n</error>\n");
		}
		_strbuf_append(xml_buffer, "  </test>\n");

	}

	printf("---------------------------\n");

	//print out tests w/ errors
	BOOL has_errors=FALSE;
	for(test = problem->tests; test!=NULL; test = test->next)
	{
		if(test->errflag)
		{
			printf("%s\n", test->error_buffer);
			has_errors=TRUE;
		}
	}
	if(has_errors)
		printf("---------------------------\n");



	if(problem->has_comments)
	{
		_get_comments(problem);
		if(problem->comments!=NULL && problem->comments->buffer!=NULL)
		{
			_strbuf_append(xml_buffer, "  <comment>");
			char* esc_comments = xml_escape(problem->comments->buffer);
			_strbuf_append(xml_buffer, esc_comments);
			_strbuf_append(xml_buffer, "\n</comment>\n");
		}
	}
	_strbuf_append(xml_buffer, " </problem>\n");
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
 * Run every test as set up in the PROBLEM linked list
 *
 * @param argc the size of argv
 * @param argv the collection of arguments to the program
 */
void run_all_tests(int argc, char* argv[])
{
	char* student="";
	char* latefile=NULL;
	if(argc > 3)
	{
		printUsage(argv[0]);
		exit(0);
	}
	else if(argc >= 2)
	{
		student = argv[1];
		if(argc == 3 && strncmp(argv[2], "*latefile=", 10) == 0)
		{
			latefile = argv[2] + 10;
		}
	}

	if(all_problems == NULL)
	{
		printf("No tests to run...\n");
		exit(1);
	}

	//for now, we won't bother opening the latefile
	//EXPAND: when it's time to add multiple late deadlines, open the LATE_SUBMISSION file

	long late_ts = (latefile==NULL ? 0 : 1);

	_STRBUF* xml_buffer = _strbuf_init(MIN_XMLBUF_LEN);

	_strbuf_append(xml_buffer, "<?xml version=\"1.0\"?>\n");
	_strbuf_append(xml_buffer, "<!DOCTYPE tester SYSTEM \"/home2/c/cse1xx/misc/tester.dtd\">\n");

	char* suffix = ct_get_file_suffix();

	char testlist_tag[MAX_TAG_LEN*2];
	sprintf(testlist_tag, "<testlist problem_set_type=\"%s\" problem_set_number=\"%d\"",
		_pstype_to_str(ct_get_problem_set_type()), ct_get_problem_set_num());
	if(suffix==NULL || strcmp(suffix, "")==0)
	{
		strcat(testlist_tag, " file_suffix=\"");
		strcat(testlist_tag, suffix);
		strcat(testlist_tag, "\"");
	}
	strcat(testlist_tag, ">\n");

	_strbuf_append(xml_buffer, testlist_tag);

	char student_tag[MAX_TAG_LEN];
	sprintf(student_tag, "<student username=\"%s\">\n", student);
	_strbuf_append(xml_buffer, student_tag);

	PROBLEM* prob;
	for(prob = all_problems; prob != NULL; prob = prob->next)
	{
		run_tests(prob, late_ts, xml_buffer);
	}

	//tack on closing stuffs
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
void clean_up()
{
	PROBLEM* probptr;
	for(probptr = all_problems; probptr!=NULL; )
	{
		PROBLEM* tmp = probptr->next;
		if(probptr->comments!=NULL)
			_strbuf_free(probptr->comments);

		TEST* testptr;
		for(testptr = probptr->tests; testptr!=NULL; )
		{
			TEST* tmptest = testptr->next;
			free(testptr);
			testptr=tmptest;
		}

		for(testptr = probptr->manual_tests; testptr!=NULL; )
		{
			TEST* tmptest = testptr->next;
			free(testptr);
			testptr=tmptest;
		}

		free(probptr);

		probptr = tmp;
	}
}

/**
 * Replaces instances of the search string with the replace string in 'string'; 
 * Written By -  Lehner Franz (franz@caos.at) 2002
 *
 * @param string the string to do the operation on
 * @param search the string to search for
 * @param replace the string to replace the first string with
 * @return return the edited string
 */
char * str_replace (char * string,char * search,char *replace)
{
	char * cp = string;
	char * s1;
	char * s2;
	register int z1=0;
	char *tmp = malloc (strlen(string) - strlen(search) + strlen(replace)+1);

	if (!*search) return string;

	while (*cp)
	{
		s1 = cp;
		s2 = search;

		while ( *s1 && *s2 && !(*s1-*s2) )
			s1++, s2++;

		// substring found
		if (!*s2) {
			// Replace String attached

			tmp=strcat(tmp,replace);
   			cp+=strlen(search);
   			tmp=strcat(tmp,cp);
   			strcpy(string,tmp);
   			free(tmp);
   			// call recursive to replace multiple entries
			string=str_replace(string,search,replace);
   			return string;
   		}

		tmp[z1]=string[z1];
		tmp[z1+1]=0;

		cp++;
		z1++;
	}

	free(tmp);
	return string;
}

/**
 * Replaces '<' and '>' in the xml docs so the xml does not crash
 *
 * @param string the string to do the replacement on
 * @return return the edited string
 */
char * xml_escape(char* string)
{
	string = str_replace(string, "<", "&lt;");
	string = str_replace(string, ">", "&gt;");
	return string;
}
