#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgrader.h"
#include "testSortAndDeleteDuplicates.h"
#include "tokenizer.h"
#include "testGetChar.h"

void testSortAndDeleteDuplicates_empty() {
	char str_array[1][MAX_STR_LENGTH+1];
	int string_count = 1;
	int n = sort_and_delete_duplicates(str_array, string_count);
	assert_equals_int("empty list", 1, n);
}

void testSortAndDeleteDuplicates_simple_duplicate() {
	char str_array[2][MAX_STR_LENGTH+1];
	str_array[0][0] = 'd';
	str_array[0][1] = 'u';
	str_array[0][2] = 'p';
	str_array[0][3] = '\0';
	str_array[1][0] = 'd';
	str_array[1][1] = 'u';
	str_array[1][2] = 'p';
	str_array[1][3] = '\0';
	int string_count = 2;
	int n = sort_and_delete_duplicates(str_array, string_count);
	assert_equals_int("simple duplicate", 1, n);
}

void testSortAndDeleteDuplicates_single_word() {
	char str_array[1][MAX_STR_LENGTH+1];
	str_array[0][0] = 'h';
	str_array[0][1] = 'e';
	str_array[0][2] = 'l';
	str_array[0][3] = 'l';
	str_array[0][4] = 'o';
	str_array[0][5] = '\0';
	int string_count = 1;
	sort_and_delete_duplicates(str_array, string_count);
	assert_equals_string("Sort and delete, single word", "hello", str_array[0]);
}

void testSortAndDeleteDuplicates_simple_sort() {
	char str_array[2][MAX_STR_LENGTH+1];
	str_array[0][0] = 'b';
	str_array[0][1] = 'b';
	str_array[0][2] = 'b';
	str_array[0][3] = '\0';
	str_array[1][0] = 'a';
	str_array[1][1] = 'a';
	str_array[1][2] = 'a';
	str_array[1][3] = '\0';
	int string_count = 2;
	int n = sort_and_delete_duplicates(str_array, string_count);
	assert_equals_int("simple sort", 2, n);
	assert_equals_string("simple sort (content 1)", "aaa", str_array[0]);
	assert_equals_string("simple sort (content 2)", "bbb", str_array[1]);
}

void testSortAndDeleteDuplicates_complex() {
	char str_array[4][MAX_STR_LENGTH+1];
	str_array[0][0] = 'a';
	str_array[0][1] = 'z';
	str_array[0][2] = '\0';
	str_array[1][0] = 'b';
	str_array[1][1] = 'b';
	str_array[1][2] = 'b';
	str_array[1][3] = '\0';
	str_array[2][0] = 'a';
	str_array[2][1] = 'a';
	str_array[2][2] = '\0';
	str_array[3][0] = 'a';
	str_array[3][1] = 'a';
	str_array[3][2] = '\0';
	
	int string_count = 4;
	int n = sort_and_delete_duplicates(str_array, string_count);
	assert_equals_int("complex sort and delete", 3, n);
	assert_equals_string("simple sort (content 1)", "aa", str_array[0]);
	assert_equals_string("simple sort (content 2)", "az", str_array[1]);
	assert_equals_string("simple sort (content 3)", "bbb", str_array[2]);
}
