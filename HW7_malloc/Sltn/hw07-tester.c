/**
 * Test ESE 116 HW 07, Spring 2007
 *
 * @version 2007 Nov 20
 * @author Luciano Cheng, JJ Geewax
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

#include "cgrader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define malloc ese_malloc
#define calloc ese_calloc
#define free ese_free

// specific to this homework
#include "malloc.c"

// Extra functions / variables required for testing
void luke_assert_equals_char_array(char*, char, int, char*);
void grow_test_size(int);

// nChars() = 50 Points
void nChars_1to100();
void nChars_100to500();
void nChars_500to750();
void nChars_750to1000();
void nChars_mem_leak_test();
void nChars_error();

// grow() = 50 Points
void grow_1();
void grow_25();
void grow_100();
void grow_1000();
void grow_mem_leak_test();
void grow_error();

/**
 * Setup tester labels
 */
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11607; }

/**
 * tester main
 */
int main(int argc, char * argv[]) {
  PROBLEM * prob1 = add_new_problem("NChars Function", 1);
  PROBLEM * prob2 = add_new_problem("Grow Function", 2);

  // nChars = 25 Points
  add_new_test(prob1, "nChars_1to100", 9, 
    &nChars_1to100);
  add_new_test(prob1, "nChars_100to500", 9, 
    &nChars_100to500);
  add_new_test(prob1, "nChars_500to750", 9, 
    &nChars_500to750);
  add_new_test(prob1, "nChars_750to1000", 9, 
    &nChars_750to1000);
  add_new_test(prob1, "nChars_mem_leak_test", 7, 
    &nChars_mem_leak_test);
  add_new_test(prob1, "nChars_error", 7,
    &nChars_error);

  // GetStats = 25 Points
  add_new_test(prob2, "grow_1", 9, 
    &grow_1);
  add_new_test(prob2, "grow_25", 9, 
    &grow_25);
  add_new_test(prob2, "grow_100", 9, 
    &grow_100);
  add_new_test(prob2, "grow_1000", 9 , 
    &grow_1000);
  add_new_test(prob2, "grow_mem_leak_test", 7,
  	&grow_mem_leak_test);
  add_new_test(prob2, "grow_error", 7, 
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
  
  free(result);
}

void nChars_test_size(int begin, int end){
  int i;
  char message[100];
  char* result;
   
  for(i = begin; i <= end; i++){
    result = nChars(i, 'a');
    sprintf(message, "Testing nChars size = %d, of 'a'", i);
    luke_assert_equals_char_array(message, 'a', i, result);
    free(result);
  }

}

void nChars_1to100(){
	nChars_test_size(1, 100);
}

void nChars_100to500(){
	nChars_test_size(100, 500);
}

void nChars_500to750(){
	nChars_test_size(500, 750);
}

void nChars_750to1000(){
	nChars_test_size(750, 1000);
}

void nChars_mem_leak_test(){
  int i;
  char* result;

  ese_reset_list();
  
  for(i = 1; i <= 1000; i++){
    result = nChars(i, 'a');
    free(result);
  }
  
  assert_equals_int("Memory leaks: ", 0, 
  		ese_malloc_allocated_count());
}

void nChars_error(){
  char* result;

  result = nChars(0, 'a');
  assert_equals_pointer("nChars size = 0", NULL, result);
}

// Grow = 50 Points
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

void grow_mem_leak_test(){
  char* result;
  void* data;
  int i;
  
  ese_reset_list();
  
  for(i = 1; i < 100; i++){
    data = malloc(sizeof(char) * i);
    result = (char*)grow(data, i);
    free(result);
  }
  
  assert_equals_int("Memory leaks: ", 0, 
  		ese_malloc_allocated_count());
}

void grow_error(){
  void* result;
  result = grow(NULL, 5);
  assert_equals_pointer("Grow Error (NULL Input)", NULL, result);
}
