// The tokenizer.h file

#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#define MAX_STR_LENGTH 256
#define MAX_STR_COUNT 100

#define READ_WORD_SUCCESS 0
#define EOF_BEFORE_WORD 1
#define EOF_AFTER_WORD 2

extern int get_test_char();

#define getchar get_test_char

// Function declarations
int get_word(char[], int);
int sort_and_delete_duplicates(char[][MAX_STR_LENGTH + 1], int);
void print_word(char[], int);

#endif
