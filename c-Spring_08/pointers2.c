/*
 * This file contains several incomplete functions that use pointers.
 * Your job is to complete the functions according to the spec provided
 * in the comments. You are encouraged but not required to write test
 * functions to test your code. (See pointers1.c for examples of test
 * functions.)
 *
 * To be completed:
 *    1. pointerToVowel()
 *    2. lastWord()
 *    2. reverse()
 */

#include <stdio.h>
#include <stdlib.h>

char * pointerToVowel(char *, char *, char *, char *);
char * lastWord(char *);
void   reverse(char *);


#ifndef TEST_1XX
int main(int argc, char* argv[]){
  // You may put your own test code here.
  int numErrors = 0;

  printf("Number of errors: %d\n", numErrors);
  return EXIT_SUCCESS;
}
#endif


/* pointerToVowel()
 * input: four pointers to lowercase characters (ok to assume valid input).
 * output: pointer to the first vowel (aeiouy), or NULL if none are vowels.
 * Assumed: no input parameters are NULL.
 *
 * Note: Feel free to use the string library (see `man string.h`),
 * though it's not required/essential.
 */
char * pointerToVowel(char *x, char *y, char *z, char *w){
  // COMPLETE THIS FUNCTION

  return NULL;
}



/* lastWord()
 * input:  a string
 * output: pointer to the first character of the last word in the string
 * examples:
 *      If line is NULL         out: NULL
 *	in: "hello, world"      out: pointer to the 'w'
 *	in: "welcome to lab"    out: pointer to the second 'l'
 *	in: "ese116"            out: pointer to the first 'e'
 *	in: "ese116  "          out: pointer to the first 'e'
 *	in: "   "               out: NULL
 *	in: ""                  out: NULL
 *
 * HINT: You may want to use strlen() to find the length of the string 
 * and traverse it starting at the end and going backwards.
 */
char* lastWord(char *line){
  // COMPLETE THIS FUNCTION

  return NULL;
}

/* reverse()
 * input: a string
 * output: none, however the original string has been reversed
 * examples:
 *   If data is NULL, no action is taken.
 *   If data is:                it is changed to:
 *           "hello"            "olleh"
 *           "hello, world"     "dlrow ,olleh"
 *           ""                 ""
 *
 * NOTE: For full credit, use pointer notation (with *'s), not []'s.
 */
void   reverse(char *data){

}
