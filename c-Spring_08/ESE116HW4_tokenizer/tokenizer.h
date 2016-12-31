// The tokenizer.h file

#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

const int MAX_STR_LENGTH = 256;
const int MAX_STR_COUNT = 100;

const int READ_WORD_SUCCESS = 0;
const int EOF_BEFORE_WORD = 1;
const int EOF_AFTER_WORD = 2;

// Function declarations
int get_word(char[], int);
int sort_and_delete_duplicates(char[][MAX_STR_LENGTH + 1], int);
void print_word(char[], int);

#endif
