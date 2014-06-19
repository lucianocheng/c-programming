#include "testReverse.h"
#include <stdlib.h>
#include <string.h>
#include "cgrader.h"
#include "pointers.h"

extern void reverse(char *);

void testReverse_smallString(){
  char test0[30] = "the quick brown";
  char test1[30] = "1234!@#$";

  reverse(test0);
  assert_equals_string("test 'the quick brown'", 
		       "nworb kciuq eht", test0);
  reverse(test1);
  assert_equals_string("test '1234!@#$", "$#@!4321",
		       test1);
}

void testReverse_longString(){
  char test0[80] = "abcdefghijklmnopqrstuvwxyz 1234567890";
  char test1[80] = "!@#$%^&*() aabbccddeeffgghhiijjkkllmm";
  
  reverse(test0);
  assert_equals_string("test 'abcdefghijklmnopqrstuvwxyz 1234567890'",
		       "0987654321 zyxwvutsrqponmlkjihgfedcba", test0);

  reverse(test1);
  assert_equals_string("test '!@#$%^&*() aabbccddeeffgghhiijjkkllmm",
		       "mmllkkjjiihhggffeeddccbbaa )(*&^%$#@!", test1);
}

void testReverse_oddLetters(){
  char test0[20] = "a";
  char test1[20] = "abc";
  char test2[20] = "abcde";
  char test3[20] = "abcdefg";

  reverse(test0);
  assert_equals_string("test 'a'", "a", test0);
  
  reverse(test1);
  assert_equals_string("test 'abc'", "cba", test1);

  reverse(test2);
  assert_equals_string("test 'abcde'", "edcba", test2);

  reverse(test3);
  assert_equals_string("test 'abcdefg'", "gfedcba", test3);
}

void testReverse_evenLetters(){
  char test0[20] = "ab";
  char test1[20] = "abcd";
  char test2[20] = "abcdef";
  char test3[20] = "abcdefgh";

  reverse(test0);
  assert_equals_string("test 'ab'", "ba", test0);

  reverse(test1);
  assert_equals_string("test 'abcd'", "dcba", test1);
  
  reverse(test2);
  assert_equals_string("test 'abcdef'", "fedcba", test2);
  
  reverse(test3);
  assert_equals_string("test 'abcdefgh'", "hgfedcba", test3);
}

void testReverse_nullAndEmpty(){
  char test0[20] = "";
  char *test1 = NULL;
  int result;

  reverse(test0);
  result = !strcmp("", test0);
  assert_equals_int("test empty string result", 1, result);

  reverse(test1);
  assert_equals_pointer("test NULL", NULL, test1);
}

