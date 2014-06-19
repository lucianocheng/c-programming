#ifndef _CTESTER_CTESTER_H_
#define _CTESTER_CTESTER_H_

#include "ctester-defs.h"
#include "cassert.h"

PROBLEM* add_new_problem(const char* description, int number);

void add_new_test(PROBLEM* problem, const char* description, double points, void (*test_function)() );

void add_new_ec_test(PROBLEM* problem, const char* description, double points, void (*test_function)() );

void add_manual_grade(PROBLEM* problem, const char* description, int points, BOOL is_extra_credit);

void set_comments(PROBLEM* problem, BOOL set);

void run_tests(PROBLEM* problem, long late_ts, _STRBUF* xml_buffer);

void run_all_tests(int argc, char* argv[]);

void clean_up();

_STRBUF* _strbuf_init(int min);

void _strbuf_append(_STRBUF* buf, char* append_str);

void _strbuf_free(_STRBUF* buf);

#endif
