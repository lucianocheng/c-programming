#include <stdlib.h>
#include <string.h>
#include "testPointerToLastWord.h"
#include "cgrader.h"
#include "pointers.h"

extern char * lastWord(char *);

void testPointerToLastWord_oneWord(){
  char test0[20] = "hello";
  char test1[20] = "goodbye";

  assert_equals_pointer("test 'hello'", &test0[0],
			lastWord(test0));
  assert_equals_pointer("test 'goodbye'", &test1[0],
			lastWord(test1));
}

void testPointerToLastWord_twoWord(){
  char test0[40] = "hello my";
  char test1[40] = "name Luke";

  assert_equals_pointer("test 'hello my'", &test0[6],
			lastWord(test0));
  assert_equals_pointer("test 'name Luke'", &test1[5],
			lastWord(test1));
}

void testPointerToLastWord_threeWord(){
  char test0[40] = "hello my name";
  char test1[40] = "abracadabra is name";

  assert_equals_pointer("test 'hello my name'", &test0[9],
			lastWord(test0));
  assert_equals_pointer("test 'abracadabra is name'", &test1[15],
			lastWord(test1));
}

void testPointerToLastWord_spaceAndEmpty(){
  char test0[30] = "     ";
  char test1[10] = " ";
  char test2[10] = "";

  assert_equals_pointer("test '     '", NULL,
			lastWord(test0));
  assert_equals_pointer("test ' '", NULL,
			lastWord(test1));
  assert_equals_pointer("test ''", NULL,
			lastWord(test2));
}

void testPointerToLastWord_null(){
  char *test = NULL;
  
  assert_equals_pointer("test NULL", NULL,
			lastWord(test));
}


