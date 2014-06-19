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

/**
 * Function get_word()
 *
 * The get_word function is a function to parse arbirary user input.  Each call to get_word() should
 * return one word read from the terminal via getchar() as defined below.
 * 
 * Another name for such a function is a "tokenizer", meaning it breaks the user's input
 * into word "tokens".
 *
 * The get_word function should do the following:
 * 1. Call getchar() until it returns a character that isn't a space or a newline
 *    This will get rid of preceding whitespace and find the beginning of the next word.
 *    Note: The last character you get using getchar() while eliminating preceding whitespace
 *          is the first character of the word, so you need to hold on to it.
 * 2. If getchar returns EOF (the End Of File character) while removing preceding whitespace,
 *    return EOF_BEFORE_WORD;
 * 3. Otherwise, use getchar() to get characters until a space, enter, or EOF is
 *    reached, or until the number of characters reaches size - 1.
 *    Store these characters in new_string.  Add a null character ('\0') at the end of new_string.
 * 3. If the number of characters reached is size - 1, truncate the word in the array, but 
 *    keep calling getchar() until a space, enter, or EOF is reached.  Add a null character to 
 *	  the end of the string.
 *    (For example, if size is 5, and the word "jello" is read in, only "jell" should be written
 *	  into newString, and the trailing 'o' should be discarded.)
 * 4. If no EOF was reached (at the end of the word), return READ_WORD_SUCCESS.  
 * 5. If a EOF was reached, return EOF_AFTER_WORD.
 *
 * HINT: This function may seem simple, but there are a lot of edge cases, and may take longer
 *       then you expect to write.  
 *       Be prepared to abuse this code in testing until it takes every edge case.
 * HINT: Use (Ctrl+D) to send a EOF to the terminal while testing this function
 * NOTE: You can assume that 'size' will always be >= 1.
 * NOTE: You must use getchar() and only getchar() to retrieve user input from the terminal
 *
 * @param new_string The string where the word will be written to
 * @param size The size of new_string
 * 
 * @returns EOF_BEFORE_WORD, EOF_AFTER_WORD, or READ_WORD_SUCCESS
 */

int get_word(char new_string[], int size){
  
	// INSERT YOUR CODE HERE
	
	return READ_WORD_SUCCESS;
}

/**
 * Function sort_and_delete_duplicates()
 *
 * The sort_and_delete_duplicates function of strings should do the following:
 * 1. Given an array of strings (null-terminated character arrays), you should sort
 *    the strings alphebetically, and eliminate duplicates.
 * 2. The alphebetical list, with duplicates deleted, should be written back into str_array[]
 * 3. Once str_array contains it's original strings sorted with duplicates removed, you
 *    should return the new number of strings in str_array.
 * 4. We do not care how inefficient your sorting algorithm is, so we recommend you
 *    use bubble sort.  Documentation can be found on the webpage.  If you wish
 *	  to implement another sorting algorithm, you may do so as long as it follows
 *	  the parameters laid out in the webpage and the documentation above.
 * 5. You cannot use malloc(), or use any functions that use any dynamic memory allocation, even
 *    if said functions are in string.h
 *
 * HINT: read the slides / online documentation for strcmp().
 *
 * NOTE: *You can assume that the words being inputed are not larger than MAX_STR_LENGTH
 *       *You can assume that the arrays holding the words being inputed are no longer 
 *        then MAX_STR_LENGTH + 1
 *       *The number of strings being passed is string_count, however you can
 *	      assume that string_count will never be larger than MAX_STR_COUNT
 *       *You must use ASCII order, so upper case words / characters come before 
 *		  lower case ones.  See a link on the webpage for an ASCII chart.
 *       *Remember, str_array is a array of strings.  So, character index 0 of string 1
 *		  can be accessed as str_array[1][0].  See the picture on the webpage for a visual representation
 *
 * @param str_array An array of strings.  Put in other words, a two dimensional character
 *                  array, where all the elements in the second dimension are null-terminated.
 * @param string_count A integer that equals the number of strings in str_array
 * 
 * @return the number of strings in str_array after being sorted and having duplicates removed
 */
int sort_and_delete_duplicates(char str_array[][MAX_STR_LENGTH + 1], int string_count){
  
	// INSERT YOUR CODE HERE
	
	return 0;
	
}