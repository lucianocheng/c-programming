/*  ESE 116 Spring 2008 HW 5 - tokenizer.c
 *  
 *  For this homework assignment you will be writing two functions, get_word() and sort_and_delete_duplicates()
 *
 * Your job is to complete the functions according to the specs provided
 * in the comments.  You are heavily encouraged to test this code.
 *
 * You can test using input redirection:
 *    gcc tokenizer.c -Wall -o tokenizer
 *    ./tokenizer < test.txt (where text.txt is a text file with 100 or less words in it)
 *
 * You can also test by running the program, inputting your own words into the terminal,
 * and hitting (CTRL + D) to send a EOF to the terminal and stop the parsing:
 *    gcc tokenizer.c -Wall -o tokenizer
 *    ./tokenizer
 *    hello
 *    goodbye
 *    i am sam
 *    (CTRL + D)
 *
 * Functions to be completed:
 *    1. get_word()
 *    2. sort_and_delete_duplicates()
 *
 * NOTE: Please indent your code correctly.  Proper indentation is the sign of a trained programmer,
 *       and makes your code a lot easier to analyze and debug.
 *
 * NOTE: str_array is a array of strings. It can be accessed the same way the packets array was accessed
 *       in the last homework
 *       Remember, character index 0 in string index 1 can be accessed as str_array[1][0]
 *
 * NOTE: You are not allowed to use malloc() or any dynamic memory allocation in any of the functions you
 *       write for this homework.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

#ifndef TEST_1xx // ARRRRRRRRGGGGGGGGGGGGGGG - Below this line be grading code, do not alter or remove

/**
 * The main function of strings.c
 * Calls get_word() repeatidly, stores the words, calls sort_and_delete_duplicates(), exits.
 */
int main(int argc, char* argv[]){
  
  char str_list[MAX_STR_COUNT][MAX_STR_LENGTH + 1];
  int i = 0;
  int word_index = 0;
  int get_word_result = 0;
  
  printf("Executing Tokenizer Program (%s)...\n", argv[0]);
  printf("Input data to be tokenized (Ctrl+D to send EOF and stop): ");
  
  /*
   * Call get_word repeatidly, retreving every word from stdin
   * If EOF_BEFORE_WORD is returned, don't count the whitespace read in and break
   * If EOF_AFTER_WORD is returned, count the word and break
   */
  for(word_index = 0; word_index < MAX_STR_COUNT; word_index++){
	get_word_result = get_word(str_list[word_index], MAX_STR_LENGTH);
    if(get_word_result == EOF_BEFORE_WORD){
      word_index--;
      break;
    }
    if(get_word_result == EOF_AFTER_WORD){
      break;
    }
  }
   
  // Output the current word array (unsorted)
  printf("\nInputted Words (unsorted):\n");
  printf("Count: %d\n", word_index + 1);
  for(i = 0; i < word_index + 1; i++){
	print_word(str_list[i], strlen(str_list[i]));
  }
  printf("\n");
  
  // Sort the array of parsed words
  int new_word_count = sort_and_delete_duplicates(str_list, word_index + 1);
  
  // Output the array of sorted words
  printf("Inputted Words (sorted with duplicates deleted):\n");
  printf("Count: %d\n", new_word_count);
  for(i = 0; i < new_word_count; i++){
	print_word(str_list[i], strlen(str_list[i]));
  }
  printf("\n");
  
  return EXIT_SUCCESS;
}

/**
 * The print_word function printf's (prints to STDOUT) the word and length of the word
 * @param print_string the string to be printed
 * @param length the length of printString
 */
void print_word(char print_string[], int length){
  printf("'%s'(%d), ", print_string, length);
}

#endif // ARRRRRRRRGGGGGGGGGGGGGGG - Above this line be grading code, do not alter or remove