/**
 * Test ESE 116 HW 05, Spring 2007
 *
 * @version 2007 Nov 20
 * @author Luciano Cheng
 *
 * Tests of the tester:
 *	- stubbed implementation provide d fails all tests
 *	- (presumably) correct solution passes all tests
 *  EXTRA NOTES FOR THIS HW:
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
//#define TEST_1xx
//#define TEST_1XX
//#define TESTER_1XX

#include "ctester.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// specific to this homework
#include "malloc.c"
#define TRUE 1
#define FALSE 0


// Extra functions / variables required for testing
void luke_assert_equals_char_array(char*, char, int, char*);
void grow_test_size(int);

// Test functions

// nCharsTest() = 25 Points
// Manual Grade

// nChars() = 25 Points
void nChars_1to100();
void nChars_100to1000();
void nChars_1000to5000();
void nChars_5000to10000(); 
void nChars_error();

// growTest() = 25 Points
// Manual Grade

// grow() = 25 Points
void grow_1();
void grow_25();
void grow_100();
void grow_1000();
void grow_error();

/**
 * Setup tester labels
 */
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11605; }

/**
 * tester main
 */
int main(int argc, char * argv[]) {
  PROBLEM * prob1 = add_new_problem("NCharsTest Function", 1);
  PROBLEM * prob2 = add_new_problem("NChars Function", 2);
  PROBLEM * prob3 = add_new_problem("GrowTest Function", 3);
  PROBLEM * prob4 = add_new_problem("Grow Function", 4);

  // nCharsTest = 25 Points
  add_manual_grade(prob1, "nCharsTest_runs", 25, 0);

  // nChars = 25 Points
  add_new_test(prob2, "nChars_1to100", 5, 
    &nChars_1to100);
  add_new_test(prob2, "nChars_100to1000", 5, 
    &nChars_100to1000);
  add_new_test(prob2, "nChars_1000to5000", 5, 
    &nChars_1000to5000);
  add_new_test(prob2, "nChars_5000to10000", 5, 
    &nChars_5000to10000);
  add_new_test(prob2, "nChars_error", 5, 
    &nChars_error);

  // growTest = 25 Points
  add_manual_grade(prob3, "growTest_runs", 25, 0);

  // GetStats = 25 Points
  add_new_test(prob4, "grow_1", 5, 
    &grow_1);
  add_new_test(prob4, "grow_25", 5, 
    &grow_25);
  add_new_test(prob4, "grow_100", 5, 
    &grow_100);
  add_new_test(prob4, "grow_1000", 5, 
    &grow_1000);
  add_new_test(prob4, "grow_error", 5, 
    &grow_error);

  run_all_tests(argc, argv);
  clean_up();
  return 0;
}

void luke_assert_equals_char_array(char* message, char expected, int size, char* received){
  int i = 0;
  for(i = 0; i < size; i++){
    assert_equals_char(message, expected, received[i]);
  }
}

void grow_test_size(int size){
  char* result;
  void* data;
  char message[100];
  int i;
  data = malloc(sizeof(char) * size);
  result = (char*)grow(data, size);
  for(i = 0; i < size * 2; i++){
    result[i] = 'a';
    sprintf(message, "Testing size %d index %d", size, i);
    assert_equals_char(message, 'a', result[i]);
  }
}

// Test functions
void nChars_1to100(){
  int i;
  char message[100];
  char* result;
  
  for(i = 1; i <= 100; i++){
    result = nChars(i, 'a');
    sprintf(message, "Testing nChars size = %d, of 'a'", i);
    luke_assert_equals_char_array(message, 'a', i, result);
    free(result);
  }
}

void nChars_100to1000(){
  int i;
  char message[100];
  char* result;
  
  for(i = 100; i <= 1000; i++){
    result = nChars(i, 'a');
    sprintf(message, "Testing nChars size = %d, of 'a'", i);
    luke_assert_equals_char_array(message, 'a', i, result);
    free(result);
  }
}

void nChars_1000to5000(){
  int i;
  char message[100];
  char* result;
  
  for(i = 1000; i <= 5000; i++){
    result = nChars(i, 'a');
    sprintf(message, "Testing nChars size = %d, of 'a'", i);
    luke_assert_equals_char_array(message, 'a', i, result);
    free(result);
  }
}

void nChars_5000to10000(){
  int i;
  char message[100];
  char* result;
  
  for(i = 5000; i <= 10000; i++){
    result = nChars(i, 'a');
    sprintf(message, "Testing nChars size = %d, of 'a'", i);
    luke_assert_equals_char_array(message, 'a', i, result);
    free(result);
  }
}

void nChars_error(){
  char* result;

  result = nChars(0, 'a');
  assert_equals_pointer("nChars size = 0", NULL, result);
}

// Grow = 25 Points
void grow_1(){
  grow_test_size(1);
}

void grow_25(){
  grow_test_size(25);
}

void grow_100(){
  grow_test_size(100);
}

void grow_1000(){
  grow_test_size(1000);
}

void grow_error(){
  void* result;
  result = grow(NULL, 5);
  assert_equals_pointer("Grow Error (NULL Input)", NULL, result);
}
