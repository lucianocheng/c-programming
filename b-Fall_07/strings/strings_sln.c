/*  ESE 116 Fall 2007 HW 3 - strings.c
 *  
 *  For this homework assignment you will be writing two functions, getWord() and sortWords()
 *
 * Your job is to complete the functions according to the specs provided
 * in the comments.  You are heavily encouraged to test this code.
 *
 * You can test using input redirection:
 *    gcc strings.c -Wall -o strings
 *    ./strings < test.txt (where text.txt has 100 or less words in it)
 *
 * You can also test by running the program, inputting your own words into the terminal,
 * and hitting (CTRL + D) to send a EOF to the terminal and stop the parsing:
 *    gcc strings.c -Wall -o strings
 *    ./strings
 *    hello
 *    goodbye
 *    i am sam
 *    (CTRL + D)
 *
 * Functions to be completed:
 *    1. getWord()
 *    2. sortWords()
 *
 * NOTE: Please indent your code correctly.  Proper indentation is the sign of a trained programmer,
 *       and makes your code 100% easier to analyze and debug.
 *
 * NOTE: str_list is a array of strings. It essentially the same as the char** we used for the packets
 *       in HW2, except instead of "packets" (char arrays of size 12) they are now strings (null 
 *       terminated character arrays)
 *
 *       Remember, character index 0 in string index 1 can be accessed as str_list[1][0]
 *
 * NOTE: You are not allowed to use malloc() or any dynamic memory allocation in any of the functions you
 *       write for this homework.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"

#ifndef TEST_1xx

/**
 * The main function of strings.c
 * Calls getWord repeatidly, stores the words, calls sortWords(), exits.
 */
int main(int argc, char* argv[]){
  
  char str_list[MAX_STR_COUNT][MAX_STR_LENGTH + 1];
  int i = 0;
  int word_index = 0;
  int getWordResult = 0;
  
  /*
   * Call getWord repeatidly, retreving every word from stdin
   * If EOF_BEFORE_WORD is returned, don't count the whitespace read in and break
   * If EOF_AFTER_WORD is returned, count the word and break
   */
  for(word_index = 0; word_index < MAX_STR_COUNT; word_index++){
    getWordResult = getWord(str_list[word_index], MAX_STR_LENGTH);
    if(getWordResult == EOF_BEFORE_WORD){
      word_index--;
      break;
    }
    if(getWordResult == EOF_AFTER_WORD){
      break;
    }
  }
   
  // Output the current word array (unsorted)
  printf("Inputted Words (unsorted):\n");
  for(i = 0; i < word_index + 1; i++){
	printWord(str_list[i], strlen(str_list[i]));
  }
  printf("\n");
  
  // Sort the array of parsed words
  sortWords(str_list, word_index + 1);
  
  // Output the array of sorted words
  printf("Inputted Words (sorted):\n");
  for(i = 0; i < word_index + 1; i++){
	printWord(str_list[i], strlen(str_list[i]));
  }
  printf("\n");
  
  return EXIT_SUCCESS;
}
#endif

/**
 * Function getWord()
 *
 * The getWord function is a function to parse arbirary user input into words.
 * 
 * Another name for such a function is a "tokenizer", meaning it breaks the user's input
 * into word "tokens".
 *
 * The getWord function should do the following:
 * 1. Call getchar() until it returns a character that isn't a space or a newline
 *    This will get rid of preceding whitespace and find the beginning of the next word.
 *    Note: The last character you get using getchar() while doing this is the first character of 
 *          the word, so you need to hold on to it.
 * 2. If getchar returns EOF (the End Of File character) while removing preceding whitespace,
 *    return EOF_BEFORE_WORD;
 * 3. Use getchar() to get characters until a space, enter, or EOF is
 *    reached, or until the number of characters reaches size - 1.
 *    Store these characters in newString.  Add a null character ('\0') at the end of newString.
 * 3. If the number of characters reached is size - 1, truncate the word in the array, but 
 *    keep calling getchar() until a space, enter, or EOF is reached.  Add a null character to 
 *	  the end of the string.
 *    (For example, if size is 5, and the word "jello" is read in, only "jell" should be written
 *	  into newString, and the trailing 'o' should be discarded.)
 * 4. If no EOF was reached (at the end of the word), return READ_WORD_SUCCESS.  
 * 5. If a EOF was reached, return EOF_AFTER_WORD.
 *
 * Hint: This function may seem simple, but there are a lot of edge cases, and may take longer
 *       then you expect to write.  
 *       Be prepared to abuse this code in testing until it takes every edge case.
 * NOTE: You can assume that 'size' will always be >= 1.
 *
 * @param newString The string where the word will be written to
 * @param size The size of newString
 * 
 * @returns EOF_BEFORE_WORD, EOF_AFTER_WORD, or READ_WORD_SUCCESS
 */

int getWord(char newString[], int size){
  
  char tempChar;
  int index = 0;

  // Eliminate extra spaces before the word
  do{
    tempChar = getchar();
    if(tempChar == EOF) return EOF_BEFORE_WORD;
  } while(tempChar == ' ' || tempChar == '\n');

  // Add the first non-space character to the string
  if(index < size - 1){
    newString[index] = tempChar;
    index++;
  }

  // Get the rest of the word, up to size - 1 spaces
  while(1){
    tempChar = getchar();
    if(tempChar == ' ' || tempChar == '\n' || tempChar == EOF){
      break;
    }

    newString[index] = tempChar;
    index++;

    // If the last character is not a space or enter, finish off the word
    if(index >= size - 1){
      do{
        tempChar = getchar();
      } while(tempChar != ' ' && tempChar != '\n' && tempChar != EOF);
      break;
    }
  }

  // Fill the last filled space (has a space, EOF, or enter) with a NULL
  newString[index] = '\0';

  if(tempChar == EOF) return EOF_AFTER_WORD;
  else return READ_WORD_SUCCESS;
}

/**
 * Function sortWords()
 *
 * The sortWords function of strings should do the following
 * 1. Given an array of strings (null-terminated character arrays), you should sort
 *    the strings alphebetically.
 * 2. The alphebetical list should be written back into str_array[]
 * 3. Once str_array contains it's original strings but sorted, return.
 * 4. We do not care how inefficient your sorting algorithm is, so we recommend you
 *    use bubble sort.  Documentation can be found on the webpage.  If you wish
 *	  to implement another sorting algorithm, you may do so as long as it follows
 *	  the parameters laid out in the webpage and the documentation above.
 *	  You cannot use malloc().
 *
 * HINT: read the slides / online documentation for strcmp().
 *
 * NOTE: *You can assume that the words being inputed are not larger than MAX_STR_LENGTH
 *       *You can assume that the arrays holding the words being inputed are no longer 
 *        then MAX_STR_LENGTH + 1
 *       *The number of strings being passed is string_count, however you can
 *	      assume that string_count will never be larger than MAX_STR_COUNT
 *       *You can use ASCII order, so upper case words / characters would come before 
 *		  lower case ones.
 *       *Remember, str_array is a array of strings.  So, character index 0 of string 1
 *		  can be accessed as str_array[1][0]
 *
 * @param str_array An array of strings.  Put in other words, a two dimensional character
 *                  array, where all the elements in the second dimension are null-terminated.
 * @param string_count A integer that equals the number of strings in str_array
 */
void sortWords(char str_array[][MAX_STR_LENGTH + 1], int string_count){
  
  int switched = 0;
  int index = 0;
  int cmpResult = 0;

  char tempString[MAX_STR_LENGTH + 1];

  // Bubble sort, loop until no switches take place
  do{
    switched = 0;
    for(index = 0; index < string_count - 1; index++){
      cmpResult = strcmp(str_array[index], str_array[index+1]);
      
      // if index > index+1 switch
      if(cmpResult > 0){
        strcpy(tempString, str_array[index]);
        strcpy(str_array[index], str_array[index + 1]);
        strcpy(str_array[index + 1], tempString);
        switched = 1;
      }
    }
  }while(switched);

  return;
}

/**
 * The printWord function printf's (prints to STDOUT) the word and length of the word
 * @param printString the string to be printed
 * @param length the length of printString
 */
void printWord(char printString[], int length){
  printf("'%s'(%d), ", printString, length);
}
