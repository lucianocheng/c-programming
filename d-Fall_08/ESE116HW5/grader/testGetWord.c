#include <stdlib.h>
#include <string.h>

#include "cgrader.h"
#include "testGetWord.h"
#include "tokenizer.h"
#include "testGetChar.h"

void testGetWord_empty() {
	set_test_chars("");
	char test[MAX_STR_LENGTH+1];
	int ret = get_word(test, MAX_STR_LENGTH);
	assert_equals_int("Test empty string return value", EOF_BEFORE_WORD, ret);
}

void testGetWord_whitespace() {
	set_test_chars("    ");
	char test[MAX_STR_LENGTH+1];
	int ret = get_word(test, MAX_STR_LENGTH);
	assert_equals_int("Test just whitespace return value", EOF_BEFORE_WORD, ret);	
}

void testGetWord_leading_whitespace_ret_value() {
	set_test_chars("    leading");
	char test[MAX_STR_LENGTH+1];
	int ret = get_word(test, MAX_STR_LENGTH);
	assert_equals_int("Test leading whitespace return value", EOF_AFTER_WORD, ret);
}

void testGetWord_leading_whitespace_string() {
	set_test_chars("    leading");
	char test[MAX_STR_LENGTH+1];
	get_word(test, MAX_STR_LENGTH);
	assert_equals_string("Test leading whitespace (string content)", "leading", test);
}

void testGetWord_trailing_whitespace_ret_value() {
	set_test_chars("trailing     ");
	char test[MAX_STR_LENGTH+1];
	int ret = get_word(test, MAX_STR_LENGTH);
	assert_equals_int("Test trailing whitespace return value", READ_WORD_SUCCESS, ret);
}

void testGetWord_trailing_whitespace_string() {
	set_test_chars("trailing     ");
	char test[MAX_STR_LENGTH+1];
	get_word(test, MAX_STR_LENGTH);
	assert_equals_string("Test trailing whitespace (string content)", "trailing", test);
}

void testGetWord_single_word_ret_value() {
	set_test_chars("single");
	char test[MAX_STR_LENGTH+1];
	int ret = get_word(test, MAX_STR_LENGTH);
	assert_equals_int("Test single word return value", EOF_AFTER_WORD, ret);
}

void testGetWord_single_word_string() {
	set_test_chars("single");
	char test[MAX_STR_LENGTH+1];
	get_word(test, MAX_STR_LENGTH);
	assert_equals_string("Test single word (string content)", "single", test);
}

void testGetWord_multiple_words_ret_value() {
	set_test_chars("multi words");
	char test[MAX_STR_LENGTH+1];
	int ret = get_word(test, MAX_STR_LENGTH);
	assert_equals_int("Test multiple words return value", READ_WORD_SUCCESS, ret);
	char test2[MAX_STR_LENGTH+1];
	ret = get_word(test2, MAX_STR_LENGTH);
	assert_equals_int("Test multiple words return value (2nd wrd)", EOF_AFTER_WORD, ret);
}

void testGetWord_multiple_words_string() {
	set_test_chars("multi words");
	char test[MAX_STR_LENGTH+1];
	get_word(test, MAX_STR_LENGTH);
	assert_equals_string("Test multiple words (string content)", "multi", test);
	char test2[MAX_STR_LENGTH+1];
	get_word(test2, MAX_STR_LENGTH);
	assert_equals_string("Test multiple words (string content 2nd wrd)", "words", test2);
}

void testGetWord_too_long_ret_value() {
	set_test_chars("single");
	char test[MAX_STR_LENGTH+1];
	int ret = get_word(test, 3);
	assert_equals_int("Test long word return value", READ_WORD_SUCCESS, ret);
}

void testGetWord_too_long_string() {
	set_test_chars("single");
	char test[MAX_STR_LENGTH+1];
	get_word(test, 3);
	assert_equals_string("Test long word (string content)", "si", test);
}

