/**
 * Test ESE 116 HW 03, Spring 2007
 *
 * @version 2007 Nov 20
 * @author Luciano Cheng
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
 *  EXTRA NOTES FOR THIS HW:
 *
 *  (-5) for use of malloc
 *
 *  (-10) for minor (< 3 errors) modifications required to compile
 *
 *  (-20) for major (> 3 errors) modifications required to compile
 *
 *  (-10) for minor (< 3 errors) modifications to the code to format output
 *
 *  (-20) for major (>3 errors) modifications to the code to format output
 */

// general homework tester stuff

// These #defines don't seem to take effect in the right scope,
// so moved to the Makefile.hw1 definition of the gcc call
// #define TEST_1xx
// #define TEST_1XX
// #define TESTER_1XX

#include "ctester.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// specific to this homework
extern int MAX_STR_LENGTH;
extern int MAX_STR_COUNT;

extern int READ_WORD_SUCCESS;
extern int EOF_BEFORE_WORD;
extern int EOF_AFTER_WORD;

#define TRUE 1
#define FALSE 0

// tester functions: Getword
// getWord = 50 Points, 10 tests 5 points each
void getWord_shortWord();
void getWord_mediumWord();
void getWord_longWord();
void getWord_spacesInFront();
void getWord_spacesInBack();
void getWord_enterInFront();
void getWord_enterInBack();
void getWord_EOFBeforeWord();
void getWord_EOFAfterWord();
void getWord_wordTooLong();

// SortWords = 50 Points, 5 tests 10 points each
void sortWords_OneWord();
void sortWords_FiveWord();
void sortWords_TenWord();
void sortWords_TwentyFiveWord();
void sortWords_EdgeCaseWord();

// Extra functions / variables required for testing
int getWord(char[], int);
void sortWords(char[][MAX_STR_LENGTH + 1], int);
void printWord(char[], int);
char lukegetchar();
void setLukeGetChar(char[]);

char lukeGetCharVal[100];
int lukeGetCharIndex;

/**
 * Setup tester labels
 */
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11603; }

/** 
 * tester main
 */
int main(int argc, char * argv[]) {
	PROBLEM * prob1 = add_new_problem("GetWord Function", 1);
	PROBLEM * prob2 = add_new_problem("SortWord Function", 2);

  // GetWord = 50 Points
  add_new_test(prob1, "getWord_shortWord", 5, 
    &getWord_shortWord);
  add_new_test(prob1, "getWord_mediumWord", 5, 
    &getWord_mediumWord);
  add_new_test(prob1, "getWord_longWord", 5, 
    &getWord_longWord);
  add_new_test(prob1, "getWord_spacesInFront", 5, 
    &getWord_spacesInFront);
  add_new_test(prob1, "getWord_spacesInBack", 5, 
    &getWord_spacesInBack);
  add_new_test(prob1, "getWord_enterInFront", 5, 
    &getWord_enterInFront);
  add_new_test(prob1, "getWord_enterInBack", 5, 
    &getWord_enterInBack);
  add_new_test(prob1, "getWord_EOFBeforeWord", 5, 
    &getWord_EOFBeforeWord);
  add_new_test(prob1, "getWord_EOFAfterWord", 5, 
    &getWord_EOFAfterWord);
  add_new_test(prob1, "getWord_wordTooLong", 5, 
    &getWord_wordTooLong);

  // SortWords = 50 Points, 5 tests 10 points each
  add_new_test(prob2, "sortWords_OneWord", 10, 
    &sortWords_OneWord);
  add_new_test(prob2, "sortWords_FiveWord", 10, 
    &sortWords_FiveWord);
  add_new_test(prob2, "sortWords_TenWord", 10, 
    &sortWords_TenWord);
  add_new_test(prob2, "sortWords_TwentyFiveWord", 10, 
    &sortWords_TwentyFiveWord);
  add_new_test(prob2, "sortWords_EdgeCaseWord", 10, 
    &sortWords_EdgeCaseWord);




	run_all_tests(argc, argv);
	clean_up();
	return 0;
}

char lukegetchar(){
  return lukeGetCharVal[lukeGetCharIndex++];
}

/**
 * Assumes you are passing it a string
 */
void setLukeGetChar(char newVal[]){
  int i = 0;

  for(i = 0; i < 100; i++){
    lukeGetCharVal[i] = (char)NULL;
  }

  strcpy(lukeGetCharVal, newVal);
}

void conductGetWordTest(char* name, char* testString, int givenArraySize, int expectedResponse, char* expectedString){
  char* sendString;
  int response;

  sendString = malloc(sizeof(char) * givenArraySize);
  setLukeGetChar(testString);
  
  response = getWord(sendString, givenArraySize);
  assert_equals_int(name, expectedResponse, response);

  if(expectedResponse != EOF_BEFORE_WORD){
    assert_equals_string(name, expectedString, sendString);
  }
}

void getWord_shortWord(){
  conductGetWordTest("Short String", "hello ", 50, READ_WORD_SUCCESS, "hello");
}

void getWord_mediumWord(){
  conductGetWordTest("Medium String", "gahaz my name is", 50, READ_WORD_SUCCESS, "gahaz");
}

void getWord_longWord(){
  conductGetWordTest("Long String", "abcdefghijk , asdf dk", 50, READ_WORD_SUCCESS, "abcdefghijk");
}

void getWord_spacesInFront(){
  conductGetWordTest("Spaces In Front", "    hello my name", 50, READ_WORD_SUCCESS, "hello");
}

void getWord_spacesInBack(){
  conductGetWordTest("Spaces In Back", "spaces!   asdf", 50, READ_WORD_SUCCESS, "spaces!");
}

void getWord_enterInFront(){
  conductGetWordTest("Enter In Front", "\n\ngoodbye hello", 50, READ_WORD_SUCCESS, "goodbye");
}

void getWord_enterInBack(){
  conductGetWordTest("Enter In Back", "hello\n\n\nasdfasdf", 50, READ_WORD_SUCCESS, "hello");
}

void getWord_EOFBeforeWord(){
  char test[] = " testing me";
  test[0] = EOF;

  conductGetWordTest("EOF Before Word", test, 50, EOF_BEFORE_WORD, "");
}

void getWord_EOFAfterWord(){
  char test[] = "testing me";
  test[7] = EOF;

  conductGetWordTest("EOF After Word", test, 50, EOF_AFTER_WORD, "testing");
}

// Word size expected must include NULL
void getWord_wordTooLong(){
  conductGetWordTest("Short String", "hellomynameis", 10, READ_WORD_SUCCESS, "hellomyna");
}

// SortWords = 50 Points, 5 tests 10 points each
void sortWords_OneWord(){
  int wordCount = 1;
  char sentArray[50][MAX_STR_LENGTH + 1];
  char expectedArray[50][MAX_STR_LENGTH + 1];

  strcpy(sentArray[0], "hello");
  strcpy(expectedArray[0], "hello");

  sortWords(sentArray, wordCount);

  int i = 0;
  for(i = 0; i < wordCount; i++){
    assert_equals_string("Sort Test 1 Word", expectedArray[i], sentArray[i]);
  }
}
void sortWords_FiveWord(){
  int wordCount = 5;
  char sentArray[50][MAX_STR_LENGTH + 1];
  char expectedArray[50][MAX_STR_LENGTH + 1];

  strcpy(sentArray[0], "hello");
  strcpy(sentArray[1], "my");
  strcpy(sentArray[2], "name");
  strcpy(sentArray[3], "is");
  strcpy(sentArray[4], "gabriele");

  strcpy(expectedArray[0], "gabriele");
  strcpy(expectedArray[1], "hello");
  strcpy(expectedArray[2], "is");
  strcpy(expectedArray[3], "my");
  strcpy(expectedArray[4], "name");

  sortWords(sentArray, wordCount);

  int i = 0;
  for(i = 0; i < wordCount; i++){
    assert_equals_string("Sort Test 5 Words", expectedArray[i], sentArray[i]);
  }
}

void sortWords_TenWord(){
  int wordCount = 10;
  char sentArray[50][MAX_STR_LENGTH + 1];
  char expectedArray[50][MAX_STR_LENGTH + 1];

  strcpy(sentArray[0], "games");
  strcpy(sentArray[1], "over");
  strcpy(sentArray[2], "losers");
  strcpy(sentArray[3], "i");
  strcpy(sentArray[4], "have");
  strcpy(sentArray[5], "all");
  strcpy(sentArray[6], "the");
  strcpy(sentArray[7], "money");
  strcpy(sentArray[8], "compare");
  strcpy(sentArray[9], "your");

  strcpy(expectedArray[0], "all");
  strcpy(expectedArray[1], "compare");
  strcpy(expectedArray[2], "games");
  strcpy(expectedArray[3], "have");
  strcpy(expectedArray[4], "i");
  strcpy(expectedArray[5], "losers");
  strcpy(expectedArray[6], "money");
  strcpy(expectedArray[7], "over");
  strcpy(expectedArray[8], "the");
  strcpy(expectedArray[9], "your");

  sortWords(sentArray, wordCount);

  int i = 0;
  for(i = 0; i < wordCount; i++){
    assert_equals_string("Sort Test 10 Words", expectedArray[i], sentArray[i]);
  }
}

void sortWords_TwentyFiveWord(){
  int wordCount = 25;
  char sentArray[50][MAX_STR_LENGTH + 1];
  char expectedArray[50][MAX_STR_LENGTH + 1];

  strcpy(sentArray[0], "the");
  strcpy(sentArray[1], "ultimate");
  strcpy(sentArray[2], "deployment");
  strcpy(sentArray[3], "of");
  strcpy(sentArray[4], "ones");
  strcpy(sentArray[5], "troops");
  strcpy(sentArray[6], "is");
  strcpy(sentArray[7], "to");
  strcpy(sentArray[8], "be");
  strcpy(sentArray[9], "formless");
  strcpy(sentArray[10], "then");
  strcpy(sentArray[11], "the");
  strcpy(sentArray[12], "most");
  strcpy(sentArray[13], "penetrating");
  strcpy(sentArray[14], "spies");
  strcpy(sentArray[15], "cannot");
  strcpy(sentArray[16], "pry");
  strcpy(sentArray[17], "in");
  strcpy(sentArray[18], "nor");
  strcpy(sentArray[19], "the");
  strcpy(sentArray[20], "wise");
  strcpy(sentArray[21], "lay");
  strcpy(sentArray[22], "plans");
  strcpy(sentArray[23], "against");
  strcpy(sentArray[24], "you");

  strcpy(expectedArray[0], "against");
  strcpy(expectedArray[1], "be");
  strcpy(expectedArray[2], "cannot");
  strcpy(expectedArray[3], "deployment");
  strcpy(expectedArray[4], "formless");
  strcpy(expectedArray[5], "in");
  strcpy(expectedArray[6], "is");
  strcpy(expectedArray[7], "lay");
  strcpy(expectedArray[8], "most");
  strcpy(expectedArray[9], "nor");
  strcpy(expectedArray[10], "of");
  strcpy(expectedArray[11], "ones");
  strcpy(expectedArray[12], "penetrating");
  strcpy(expectedArray[13], "plans");
  strcpy(expectedArray[14], "pry");
  strcpy(expectedArray[15], "spies");
  strcpy(expectedArray[16], "the");
  strcpy(expectedArray[17], "the");
  strcpy(expectedArray[18], "the");
  strcpy(expectedArray[19], "then");
  strcpy(expectedArray[20], "to");
  strcpy(expectedArray[21], "troops");
  strcpy(expectedArray[22], "ultimate");
  strcpy(expectedArray[23], "wise");
  strcpy(expectedArray[24], "you");

  sortWords(sentArray, wordCount);

  int i = 0;
  for(i = 0; i < wordCount; i++){
    assert_equals_string("Sort Test 25 Word", expectedArray[i], sentArray[i]);
  }
}

void sortWords_EdgeCaseWord(){
  int wordCount = 10;
  char sentArray[50][MAX_STR_LENGTH + 1];
  char expectedArray[50][MAX_STR_LENGTH + 1];

  strcpy(sentArray[0], "2");
  strcpy(sentArray[1], "11");
  strcpy(sentArray[2], "Uppercase2");
  strcpy(sentArray[3], "Uppercase");
  strcpy(sentArray[4], "lowercase");
  strcpy(sentArray[5], "aaaaaa");
  strcpy(sentArray[6], "abcd");
  strcpy(sentArray[7], "abce");
  strcpy(sentArray[8], "aaa");
  strcpy(sentArray[9], "lowercaselonger");

  strcpy(expectedArray[0], "11");
  strcpy(expectedArray[1], "2");
  strcpy(expectedArray[2], "Uppercase");
  strcpy(expectedArray[3], "Uppercase2");
  strcpy(expectedArray[4], "aaa");
  strcpy(expectedArray[5], "aaaaaa");
  strcpy(expectedArray[6], "abcd");
  strcpy(expectedArray[7], "abce");
  strcpy(expectedArray[8], "lowercase");
  strcpy(expectedArray[9], "lowercaselonger");

  sortWords(sentArray, wordCount);

  int i = 0;
  for(i = 0; i < wordCount; i++){
    assert_equals_string("Sort Test Edge Cases", expectedArray[i], sentArray[i]);
  }
}
