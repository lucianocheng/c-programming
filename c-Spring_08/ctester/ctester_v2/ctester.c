#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

#include "ctester-defs.h"
#include "cassert.h"

PROBLEM* all_problems;


TEST* current_test;

extern char* ct_get_file_suffix();
extern PS_TYPE ct_get_problem_set_type();
extern int ct_get_problem_set_num();

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


TEST* _add_new_test(PROBLEM* problem, const char* description, void (*test_function)(), TEST** list )
{
	TEST* test = _calloc_or_die(1, sizeof(TEST), "Couldn't calloc test\n");
	test->descrip = description;
	test->test_function = test_function;
	test->next = NULL;
	test->errflag = FALSE;
	test->has_run = FALSE;
	test->is_successful = FALSE;
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


void add_new_test(PROBLEM* problem, const char* description, double points, void (*test_function)() )
{
	TEST* test = _add_new_test(problem, description, test_function, &(problem->tests));
	test->is_manual = FALSE;
	test->is_ec = FALSE;
	test->max_score = points;
	test->max_ec_score = 0;
}

void add_new_ec_test(PROBLEM* problem, const char* description, double points, void (*test_function)() )
{
	TEST* test = _add_new_test(problem, description, test_function, &(problem->tests));
	test->is_manual = FALSE;
	test->is_ec = TRUE;
	test->max_score = 0;
	test->max_ec_score = points;
}

//not thread safe...
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

void add_manual_grade(PROBLEM* problem, const char* description, int points, BOOL is_extra_credit)
{
	TEST* test = _add_new_test(problem, description, &_get_manual_grade, &(problem->manual_tests));
	test->is_manual = TRUE;
	test->is_ec = is_extra_credit;
	test->max_score = (is_extra_credit ? 0 : points);
	test->max_ec_score = (is_extra_credit ? points : 0);
}

void set_comments(PROBLEM* problem, BOOL set)
{
	problem->has_comments = TRUE;
}


_STRBUF* _strbuf_init(int min)
{
	_STRBUF* buf = _calloc_or_die(1, sizeof(_STRBUF), "Couldn't calloc internal buffer");
	buf->resize_factor = 1;
	buf->len = min;
	buf->buffer = _calloc_or_die(min, sizeof(char), "Couldn't calloc buffer string");

	return buf;
}

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

void _strbuf_free(_STRBUF* buf)
{
	free(buf->buffer);
	free(buf);
}

char * str_replace (char * string,char * search,char *replace);

char * xml_escape(char* string);

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

//not thread safe...
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

		if(test->is_ec)
			printf(" Extra Credit:");
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

void printUsage(char* prog)
{
	printf("%s usage:\n", prog);
	printf("\t%s *STUDENT_ID *latefile=<late_submission_file>\n", prog);
	printf("Arguments marked with a * are optional. If you wish for a .tester ");
	printf("file to be produced you must also provide STUDENT_ID.\n");
	printf("If tested solution is submitted late, you must specify the LATE_SUBMISSION file as well.\n");
}

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

/*
 *   Written By -  Lehner Franz (franz@caos.at) 2002
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

char * xml_escape(char* string)
{
	string = str_replace(string, "<", "&lt;");
	string = str_replace(string, ">", "&gt;");
	return string;
}
