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
#include <string.h>

char * pointerToVowel(char *, char *, char *, char *);
char * lastWord(char *);
void   reverse(char *);


#ifndef TEST_1XX
int main(int argc, char* argv[]){
  // You may put your own test code here.
  //int numErrors = 0;
  //char c1 = 'b';
  //char c2 = 'a';
  //char c3 = 'd';
  //char c4 = 'y';
  //printf("%c is the first vowel in [%c, %c, %c, %c]\n", *pointerToVowel(&c1, &c2, &c3, &c4), c1, c2, c3, c4);
  //char *tests[] = {
  //  NULL,
  //  "hello, world",
  //  "welcome to lab",
  //  "ese116",
  //  "ese116 ",
  //  "   ",
  //  ""
  //};
  //int i;
  //char * result;
  //for (i = 0; i < 7; ++i) {
  //  result = lastWord(tests[i]);
  //  printf("The last word of \n\t\"%s\"\nis\n\t\"%s\"\n", (tests[i] == NULL ? "NULL" : tests[i]), (result  == NULL ? "NULL" : result));
  //}
  char test1[] = "hello";
  printf("%s | ", test1);
  reverse(test1);
  printf("%s\n", test1);
  char test2[] = "hello, world";
  printf("%s | ", test2);
  reverse(test2);
  printf("%s\n", test2);
  char test3[] = "";
  printf("%s | ", test3);
  reverse(test3);
  printf("%s\n", test3);
  
  //printf("Number of errors: %d\n", numErrors);
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
  char *chars[] = {x,y,z,w};
  int i;
  for (i = 0; i < 4; ++i) {
    switch (*(*(chars+i))) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'y':
      return *(chars+i);
      break;
    default :
      break;
    }
  }
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
  if (line == NULL)
    return NULL;
  int i = strlen(line);
  char *last = NULL;
  while (--i >= 0) {
    if (line[i] == ' ') {
      if (last != NULL)
	return last;
    } else {
      last = line + i;
    }
  }
  return last;
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
void reverse(char *data){
  if (data == NULL)
    return;
  char tmp;
  int i = 0;
  int len = strlen(data);
  int mid = len / 2;
  while (i < mid) {
    tmp = *(data + i);
    *(data + i) = *(data + len - 1 - i);
    *(data + len - 1 - i) = tmp;
    ++i;
  }
}
