#ifndef __TEST_GET_CHAR_H__
#define __TEST_GET_CHAR_H__

#define TEST_CHARS_MAX_LENGTH 1024
char test_chars[TEST_CHARS_MAX_LENGTH];

int get_test_char();
void set_test_chars(char*);
void reset_test_chars();
int strlen_max(char*, int);

#endif


