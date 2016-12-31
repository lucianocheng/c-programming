#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "testGetChar.h"

char test_chars[TEST_CHARS_MAX_LENGTH];
int test_char_index = 0;

int get_test_char() {
	return test_chars[test_char_index++];
}

void set_test_chars(char* chars) {
	reset_test_chars();
	if (chars == NULL) return;
	int length = strlen_max(chars, TEST_CHARS_MAX_LENGTH-1);
	int i = 0;
	for(i = 0; i < length; i++) test_chars[i] = chars[i];
	test_chars[length] = EOF;
}

void reset_test_chars() {
	int i = 0;
	for(i = 0; i < TEST_CHARS_MAX_LENGTH; i++) test_chars[i] = '\0';
	test_char_index = 0;
}

int strlen_max(char* chars, int max){
	int i = 0;
	for(i = 0; i < max && chars[i] != '\0'; i++){}
	
	return i;
}
