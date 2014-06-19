/*
 * This file contains several incomplete functions that use pointers.
 * Your job is to complete the functions according to the spec provided
 * in the comments. You are encouraged but not required to write test
 * functions to test your code. (See pointers_lab.c for examples on how
 * to test your code.)
 *
 * To be completed:
 *    1. pointerToVowel()
 *    2. lastWord()
 *    2. reverse()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointers.h"

/* pointerToVowel()
 * input: four pointers to lowercase characters (ok to assume valid input).
 * output: THE POINTER to the first vowel (aeiou AND y), or NULL if none are vowels.
 * Assumed: no input parameters are NULL.
 *
 * Note: You MUST return one of the address passed to you via this function,
 *       we will be testing for the pointer you return, NOT the value.
 * 
 * IE, DO NOT DO THIS:
 *     char x = 'y';
 *     return &x;
 * Doing the above returns a pointer to a local variable, which is VERY bad.
 * 
 * Note: Feel free to use the string library (see `man string.h`),
 * though it's not required/essential.
 */
char * pointerToVowel(char *x, char *y, char *z, char *w){
  char xvow = *x;
  char yvow = *y;
  char zvow = *z;
  char wvow = *w;

  if(xvow == 'a' ||xvow == 'e' ||xvow == 'i' ||xvow == 'o' ||xvow == 'u' ||xvow == 'y'){
    return x;
  }
  if(yvow == 'a' ||yvow == 'e' ||yvow == 'i' ||yvow == 'o' ||yvow == 'u' ||yvow == 'y'){
    return y;
  }
  if(zvow == 'a' ||zvow == 'e' ||zvow == 'i' ||zvow == 'o' ||zvow == 'u' ||zvow == 'y'){
    return z;
  }
  if(wvow == 'a' ||wvow == 'e' ||wvow == 'i' ||wvow == 'o' ||wvow == 'u' ||wvow == 'y'){
    return w;
  }
  else
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
 * Reminder: All strings are NULL-terminated
 * 
 * HINT: You can use strlen() to find the length of the string 
 * and traverse it starting at the end and going backwards.
 */

char* lastWord(char *line){
	
	if(line == NULL) return NULL;

	int length = strlen(line);
	int i,j, keepGoing;
	keepGoing = 0;
	char *output;
	
	i = length;
	while(keepGoing == 0){
	  i = i-1;
	  if(((line[i]>='a')&&(line[i]<='z')) || ((line[i]>='A') && (line[i]<='Z'))){
		keepGoing = 1;
		}
	}

	if(keepGoing){
     
		for(j = i;j>=0;j--){
		  if(((line[j-1]>='a')&&(line[j-1]<='z')) || ((line[j-1]>='A') && (line[j-1]<='Z'))){
			output = &line[j];
			}
			else{
			  output = &line[j];
			  return output;
			}
		}
	}
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
 * Reminder: All strings are NULL terminated
 * 
 * NOTE: For full credit, use pointer notation (with *'s), not []'s.
 */


void reverse(char *data){
	
	if(data == NULL) return;

	char temp;
	int i,j,length;
	length = strlen(data);
	int halfpoint = (length/2);
	
	for(i=0,j=length-1;i<halfpoint;i++,j--){
	    	temp = *(data+i);
		 *(data+i) = *(data+j);
	    	*(data+j) = temp;
	}
	
}
	











