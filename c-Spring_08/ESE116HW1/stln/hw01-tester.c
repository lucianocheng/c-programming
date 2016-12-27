/**
 * Test ESE 116 HW 01, Spring 2008
 *
 * @version 2008 March 3rd
 * @author Luciano Cheng
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
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
#include "hal.h"

#define add_new_test add_new_fork_test

// tester functions' headers - get_user_input()
void test_get_user_input_ADD();
void test_get_user_input_SUB();
void test_get_user_input_MUL();
void test_get_user_input_DIV();
void test_get_user_input_ERR();
void test_get_user_input_EXIT();

// tester functions' headers - calc_result()
void calc_result_ADD();
void calc_result_SUB();
void calc_result_MUL();
void calc_result_DIV();

// tester functions headers - used switch statement
void used_switch_statement();

// Non-testing functions & variables necessary for tests to complete
int integer_from_terminal_array[100];
int integer_from_terminal_array_index = 0;

char character_from_terminal_array[100];
int character_from_terminal_array_index = 0;

int print_result_operand1 = 0;
int print_result_operand2 = 0;
char print_result_operation = 0;
int print_result_result = 0;

int get_integer_from_terminal();
char get_character_from_terminal();
void print_result(int, int, char, int);
void reset_print_result_returns();

// tester main
int main(int argc, char * argv[]) {
	PROBLEM * prob1 = add_new_problem("get_user_input", 1);
	PROBLEM * prob2 = add_new_problem("calc_result", 2);
	PROBLEM * prob3 = add_new_problem("use switch statements", 3);

	add_new_test(prob1, "test_get_user_input_ADD", 10,
		&test_get_user_input_ADD);
	add_new_test(prob1, "test_get_user_input_SUB", 10,
		&test_get_user_input_SUB);
	add_new_test(prob1, "test_get_user_input_MUL", 10,
		&test_get_user_input_MUL);
	add_new_test(prob1, "test_get_user_input_DIV", 10,
		&test_get_user_input_DIV);
	add_new_test(prob1, "test_get_user_input_ERR", 5,
		&test_get_user_input_ERR);
  add_new_test(prob1, "test_get_user_input_EXIT", 5,
    &test_get_user_input_EXIT);

  add_new_test(prob2, "calc_result_ADD", 10,
    &calc_result_ADD);
  add_new_test(prob2, "calc_result_SUB", 10,
    &calc_result_SUB);
  add_new_test(prob2, "calc_result_MUL", 10,
    &calc_result_MUL);
  add_new_test(prob2, "calc_result_DIV", 10,
    &calc_result_DIV);

  add_new_test(prob3, "Switch Statement Used in calc_result()", 10, 
    &used_switch_statement);

	run_all_tests(argc, argv);
	clean_up();	
	return 0;
}

// Functions that are extern'ed by the library testing type for the xml parser
// Must be filled in
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11601; }

// Functions necessary for testing, but not the testing functions
// AKA, Overloads of the functions that the tests call, and associated global variables

int get_integer_from_terminal(){
  printf("%d\n", integer_from_terminal_array[integer_from_terminal_array_index]);
  return integer_from_terminal_array[integer_from_terminal_array_index++];
}

char get_character_from_terminal(){
  printf("%c\n", character_from_terminal_array[character_from_terminal_array_index]);
  return character_from_terminal_array[character_from_terminal_array_index++];
}

void reset_print_result_returns(){
  integer_from_terminal_array_index = 0;
  character_from_terminal_array_index = 0;

  print_result_operand1 = 0;
  print_result_operand2 = 0;
  print_result_operation = '\0';
  print_result_result = 0;
}

void print_result(int operand1, int operand2, char operation, int result){
  print_result_operand1 = operand1;
  print_result_operand2 = operand2;
  print_result_operation = operation;
  print_result_result = result;
}

/** 
 * ----------------------------------------------------
 * Specific Test Functions
 * ----------------------------------------------------
 */

/** Test the user_input Add */
void test_get_user_input_ADD() {
  int return_value = 0;

  reset_print_result_returns();

  // Test 1: Calculate 5 + 10
  character_from_terminal_array[0] = '+';
  integer_from_terminal_array[0] = 5;
  integer_from_terminal_array[1] = 10;
  printf("\n");
  return_value = get_user_input();

  assert_equals_int("Calculate 5 + 10: Print First Operand", 5, print_result_operand1);
  assert_equals_int("Calculate 5 + 10: Print Second Operand", 10, print_result_operand2);
  assert_equals_char("Calculate 5 + 10: Print Operator", '+', print_result_operation);
  assert_equals_int("Calculate 5 + 10: Return Value", USER_CONTINUE, return_value);
}

/** Test the user_input Subtract */
void test_get_user_input_SUB() {
  int return_value = 0;

  reset_print_result_returns();

  // Test 1: Calculate 10 - 5
  character_from_terminal_array[0] = '-';
  integer_from_terminal_array[0] = 10;
  integer_from_terminal_array[1] = 5;
  printf("\n");
  return_value = get_user_input();

  assert_equals_int("Calculate 10 - 5: Print First Operand", 10, print_result_operand1);
  assert_equals_int("Calculate 10 - 5: Print Second Operand", 5, print_result_operand2);
  assert_equals_char("Calculate 10 - 5: Print Operator", '-', print_result_operation);
  assert_equals_int("Calculate 10 - 5: Return Value", USER_CONTINUE, return_value);
}

/** Test the user_input Multiply */
void test_get_user_input_MUL() {
  int return_value = 0;

  reset_print_result_returns();

  // Test 1: Calculate 5 * 10
  character_from_terminal_array[0] = '*';
  integer_from_terminal_array[0] = 10;
  integer_from_terminal_array[1] = 20;
  printf("\n");
  return_value = get_user_input();

  assert_equals_int("Calculate 10 * 20: Print First Operand", 10, print_result_operand1);
  assert_equals_int("Calculate 10 * 20: Print Second Operand", 20, print_result_operand2);
  assert_equals_char("Calculate 10 * 20: Print Operator", '*', print_result_operation);
  assert_equals_int("Calculate 10 * 20: Return Value", USER_CONTINUE, return_value);
}

/** Test the user_input Divide */
void test_get_user_input_DIV() {
  int return_value = 0;

  reset_print_result_returns();

  // Test 1: Calculate 5 * 10
  character_from_terminal_array[0] = '/';
  integer_from_terminal_array[0] = 12;
  integer_from_terminal_array[1] = 6;
  printf("\n");
  return_value = get_user_input();

  assert_equals_int("Calculate 5 * 10: Print First Operand", 12, print_result_operand1);
  assert_equals_int("Calculate 5 * 10: Print Second Operand", 6, print_result_operand2);
  assert_equals_char("Calculate 5 * 10: Print Operator", '/', print_result_operation);
  assert_equals_int("Calculate 5 * 10: Return Value", USER_CONTINUE, return_value);
}

/** Test the user_input Error */
void test_get_user_input_ERR() {
  int return_value = 0;

  reset_print_result_returns();

  // Test 1: Send Error via $ as operator
  reset_print_result_returns();
  character_from_terminal_array[0] = '$';
  integer_from_terminal_array[0] = 10;
  integer_from_terminal_array[1] = 20;
  printf("\n");
  return_value = get_user_input();

  assert_equals_int("Error ($ as input): First Operand Not Printed and remains 0", 0, print_result_operand1);
  assert_equals_int("Error ($ as input): Second Operand Not Printed and remains 0", 0, print_result_operand2);
  assert_equals_char("Error ($ as input): Operator Not Printed and remains NULL", '\0', print_result_operation);
  assert_equals_int("Error ($ as input): Return value", USER_CONTINUE, return_value);
}

/** Test the user_input Exit */
void test_get_user_input_EXIT() {
  int return_value = 0;

  reset_print_result_returns();

  // Test 1: Send Error via $ as operator
  reset_print_result_returns();
  character_from_terminal_array[0] = 'X';
  integer_from_terminal_array[0] = 10;
  integer_from_terminal_array[1] = 20;
  printf("\n");
  return_value = get_user_input();

  assert_equals_int("Exit ($ as input): First Operand Not Printed and remains 0", 0, print_result_operand1);
  assert_equals_int("Exit ($ as input): Second Operand Not Printed and remains 0", 0, print_result_operand2);
  assert_equals_char("Exit ($ as input): Operator Not Printed and remains NULL", '\0', print_result_operation);
  assert_equals_int("Exit ($ as input): Return value", USER_EXIT, return_value);
}

/** Test the calc_result ADD */
void calc_result_ADD(){
  assert_equals_int("calc_result: 8 + 8 = 16", 16, calc_result(8, 8, '+'));
  assert_equals_int("calc_result: 5 + -5 = 0", 0, calc_result(5, -5, '+'));
  assert_equals_int("calc_result: 100 + 200 = 300", 300, calc_result(100, 200, '+'));
  assert_equals_int("calc_result: -50 + -40 = -90", -90, calc_result(-50, -40, '+'));
}

/** Test the calc_result SUB */
void calc_result_SUB(){
  assert_equals_int("calc_result: 8 - 8 = 0", 0, calc_result(8, 8, '-'));
  assert_equals_int("calc_result: 20 - 10 = 10", 10, calc_result(20, 10, '-'));
  assert_equals_int("calc_result: 60 - -120 = 180", 180, calc_result(60, -120, '-'));
  assert_equals_int("calc_result: -10 - -20 = 10", 10, calc_result(-10, -20, '-'));
}

/** Test the calc_result MUL */
void calc_result_MUL(){
  assert_equals_int("calc_result: 8 * 8 = 64", 64, calc_result(8, 8, '*'));
  assert_equals_int("calc_result: 5 * -5 = 0", -25, calc_result(5, -5, '*'));
  assert_equals_int("calc_result: -10 * 4 = -40", -40, calc_result(-10, 4, '*'));
  assert_equals_int("calc_result: -40 * -10 = 400", 400, calc_result(-40, -10, '*'));
}

/** Test the calc_result DIV */
void calc_result_DIV(){
  assert_equals_int("calc_result: 8 / 8 = 1", 1, calc_result(8, 8, '/'));
  assert_equals_int("calc_result: 25 / -5 = -5", -5, calc_result(25, -5, '/'));
  assert_equals_int("calc_result: 500 / 200 = 2", 2, calc_result(500, 200, '/'));
  assert_equals_int("calc_result: -50 / -10 = 5", 5, calc_result(-50, -10, '/'));
}

void used_switch_statement(){
  FILE* new_file;
  int found_switch_line = 0;
  int file_opened = 0;
  char temp_line[300];
  new_file = fopen("./hal.c", "r");
  if(new_file != NULL){
    printf("\n     FILE hal.c opened successfully\n");
    file_opened = 1;
    int i = 0;
    for(i = 0; fgets(temp_line, 300, new_file) != NULL; i++){
      if(strstr(temp_line, "switch") != NULL){
        found_switch_line = 1;
        printf("     Switch() statement found on line %d\n", i+1);
        break;
      }
    }
  }

  assert_equals_int("Used Switch Statement, hal.c exists", 1, file_opened);
  assert_equals_int("Used Switch Statement, contains switch()", 1, found_switch_line);
}
