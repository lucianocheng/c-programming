/**
 * Test ESE 116 HW 02, Spring 2008
 *
 * @version 2008 March 14th
 * @author Luciano Cheng
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
 */

// general homework tester stuff
#include "ctester.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// specific to this homework
#include "skynet.h"

// tester functions' headers - count_down()
void test_count_down_1();
void test_count_down_10();
void test_count_down_50();
void test_count_down_100();

// tester functions' headers - get_human_max_age()
void test_get_max_age_5();
void test_get_max_age_10();
void test_get_max_age_50();
void test_get_max_age_100();

// tester functions' headers - get_human_average_age()
void test_get_human_average_age_5pt5();
void test_get_human_average_age_40pt2();
void test_get_human_average_age_60();
void test_get_human_average_age_30();

// tester functions' headers - calculate_resistance()
void test_calculate_resistance_TAS();
void test_calculate_resistance_CARE_BEARS();
void test_calculate_resistance_WOODY_ALLEN();
void test_calculate_resistance_CHUCK_NORRIS();

// tester functions' headers - query_user()
void test_query_user_COUNTDOWN();
void test_query_user_MAX_AGE();
void test_query_user_AVG_AGE();
void test_query_user_RESISTANCE();
void test_query_user_HELP();
void test_query_user_EXIT();
void test_query_user_ERROR();
void test_query_user_SWITCH_STATEMENT();

// Non-testing functions & variables necessary for tests to complete
int integer_from_terminal_array[100];
int integer_from_terminal_array_index = 0;

float float_from_terminal_array[100];
int float_from_terminal_array_index = 0;

char character_from_terminal_array[100];
int character_from_terminal_array_index = 0;

int print_countdown_int_array[200];
int print_countdown_int_array_size = 0;

int get_integer_from_terminal();
float get_float_from_terminal();
char get_character_from_terminal();
void reset_test_array_indices();

void print_countdown_int(int);
void print_help_menu();

void test_countdown_from(int);

// tester main
int main(int argc, char * argv[]) {
	PROBLEM * prob1 = add_new_problem("count_down", 1);
	PROBLEM * prob2 = add_new_problem("get_human_max_age", 2);
	PROBLEM * prob3 = add_new_problem("get_human_average_age", 3);
  PROBLEM * prob4 = add_new_problem("calculate_resistance", 4);
  PROBLEM * prob5 = add_new_problem("query_user", 5);

	add_new_test(prob1, "test_count_down_1", 5,
		&test_count_down_1);
	add_new_test(prob1, "test_count_down_10", 5,
		&test_count_down_10);
	add_new_test(prob1, "test_count_down_50", 5,
		&test_count_down_50);
	add_new_test(prob1, "test_count_down_100", 5,
		&test_count_down_100);

  add_new_test(prob2, "test_get_max_age_5", 5,
    &test_get_max_age_5);
  add_new_test(prob2, "test_get_max_age_10", 5,
    &test_get_max_age_10);
  add_new_test(prob2, "test_get_max_age_50", 5,
    &test_get_max_age_50);
  add_new_test(prob2, "test_get_max_age_100", 5,
    &test_get_max_age_100);

  add_new_test(prob3, "test_get_human_average_age_5pt5", 5, 
    &test_get_human_average_age_5pt5);
  add_new_test(prob3, "test_get_human_average_age_40pt2", 5, 
    &test_get_human_average_age_40pt2);
  add_new_test(prob3, "test_get_human_average_age_60", 5, 
    &test_get_human_average_age_60);
  add_new_test(prob3, "test_get_human_average_age_30", 5, 
    &test_get_human_average_age_30);

  add_new_test(prob4, "test_calculate_resistance_TAS", 5, 
    &test_calculate_resistance_TAS);
  add_new_test(prob4, "test_calculate_resistance_CARE_BEARS", 5, 
    &test_calculate_resistance_CARE_BEARS);
  add_new_test(prob4, "test_calculate_resistance_WOODY_ALLEN", 5, 
    &test_calculate_resistance_WOODY_ALLEN);
  add_new_test(prob4, "test_calculate_resistance_CHUCK_NORRIS", 5, 
    &test_calculate_resistance_CHUCK_NORRIS);

  add_new_test(prob5, "test_query_user_COUNTDOWN", 2, 
    &test_query_user_COUNTDOWN);
  add_new_test(prob5, "test_query_user_MAX_AGE", 2, 
    &test_query_user_MAX_AGE);
  add_new_test(prob5, "test_query_user_AVG_AGE", 2, 
    &test_query_user_AVG_AGE);
  add_new_test(prob5, "test_query_user_RESISTANCE", 2, 
    &test_query_user_RESISTANCE);
  add_new_test(prob5, "test_query_user_HELP", 2, 
    &test_query_user_HELP);
  add_new_test(prob5, "test_query_user_EXIT", 2, 
    &test_query_user_EXIT);
  add_new_test(prob5, "test_query_user_ERROR", 4, 
    &test_query_user_ERROR);
  add_new_test(prob5, "test_query_user_SWITCH_STATEMENT", 4, 
    &test_query_user_SWITCH_STATEMENT);

	run_all_tests(argc, argv);
	clean_up();	
	return 0;
}

// Functions that are extern'ed by the library testing type for the xml parser
// Must be filled in
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11602; }

// Functions necessary for testing, but not the testing functions
// AKA, Overloads of the functions that the tests call, and associated global variables

int get_integer_from_terminal(){
  printf("%d\n", integer_from_terminal_array[integer_from_terminal_array_index]);
  return integer_from_terminal_array[integer_from_terminal_array_index++];
}

float get_float_from_terminal(){
  printf("%f\n", float_from_terminal_array[float_from_terminal_array_index]);
  return float_from_terminal_array[float_from_terminal_array_index++];
}

char get_character_from_terminal(){
  printf("%c\n", character_from_terminal_array[character_from_terminal_array_index]);
  return character_from_terminal_array[character_from_terminal_array_index++];
}

void reset_test_array_indices(){
  integer_from_terminal_array_index = 0;
  float_from_terminal_array_index = 0;
  character_from_terminal_array_index = 0;
  print_countdown_int_array_size = 0;
  
  int i = 0;
  for(i = 0; i < 100; i++){
    integer_from_terminal_array[i] = -1;
    float_from_terminal_array[i] = -1.0;
    character_from_terminal_array[i] = '\0';
  }

  for(i = 0; i < 200; i++){
    print_countdown_int_array[i] = -1;
  }
}

void print_countdown_int(int new_countdown_int){
  print_countdown_int_array[print_countdown_int_array_size] = new_countdown_int;
  print_countdown_int_array_size++;
}

void print_help_menu(){
  printf("Help Menu Printed\n");
}

void test_countdown_from_int(int countdown_from){
  reset_test_array_indices();
  int count_down_array[200];
  char message[400];

  int i = 0;
  for(i = countdown_from; i >= 0; i--){
    count_down_array[countdown_from-i] = i;
  }

  count_down(100, 50.0, countdown_from);
  
  sprintf(message, "count_down(): print_countdown_int() called %d times", countdown_from + 1);
  assert_equals_int(message, countdown_from + 1, print_countdown_int_array_size);

  sprintf(message, "count_down(): from %d to 0", countdown_from);
  assert_equals_int_array(message, count_down_array, print_countdown_int_array, countdown_from + 1);
}

/** 
 * ----------------------------------------------------
 * Specific Test Functions
 * ----------------------------------------------------
 */

/** count_down test functions */
void test_count_down_1(){
  test_countdown_from_int(1);
}

void test_count_down_10(){
  test_countdown_from_int(10);
}

void test_count_down_50(){
  test_countdown_from_int(50);
}

void test_count_down_100(){
  test_countdown_from_int(100);
}

/** get_human_max_age test functions */
void test_get_max_age_5(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 7;
  integer_from_terminal_array[1] = 1;
  integer_from_terminal_array[2] = 2;
  integer_from_terminal_array[3] = 5;
  integer_from_terminal_array[4] = 4;
  integer_from_terminal_array[5] = 5;
  integer_from_terminal_array[6] = 3;
  integer_from_terminal_array[7] = 1;
  
  assert_equals_int("get_human_max_age(): From {1, 2, 5, 4, 5, 3, 1}", 5, get_human_max_age());
}

void test_get_max_age_10(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 5;
  integer_from_terminal_array[1] = 3;
  integer_from_terminal_array[2] = 0;
  integer_from_terminal_array[3] = 3;
  integer_from_terminal_array[4] = 8;
  integer_from_terminal_array[5] = 10;

  
  assert_equals_int("get_human_max_age(): From {3, 0, 3, 8, 10}", 10, get_human_max_age());
}

void test_get_max_age_50(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 12;
  integer_from_terminal_array[1] = 10;
  integer_from_terminal_array[2] = 12;
  integer_from_terminal_array[3] = 11;
  integer_from_terminal_array[4] = 40;
  integer_from_terminal_array[5] = 30;
  integer_from_terminal_array[6] = 50;
  integer_from_terminal_array[7] = 11;
  integer_from_terminal_array[8] = 0;
  integer_from_terminal_array[9] = 5;
  integer_from_terminal_array[10] = 49;
  integer_from_terminal_array[11] = 39;
  integer_from_terminal_array[12] = 50;

  assert_equals_int("get_human_max_age(): From {10, 12, 11, 40, 30, 50, 11, 0, 5, 49, 39, 50}", 50, get_human_max_age());
}

void test_get_max_age_100(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 5;
  integer_from_terminal_array[1] = 100;
  integer_from_terminal_array[2] = 100;
  integer_from_terminal_array[3] = 100;
  integer_from_terminal_array[4] = 100;
  integer_from_terminal_array[5] = 100;

  assert_equals_int("get_human_max_age(): From {100, 100, 100, 100, 100}", 100, get_human_max_age());
}

/** get_human_average_age test functions */
void test_get_human_average_age_5pt5(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 5;
  float_from_terminal_array[0] = 10.5;
  float_from_terminal_array[1] = 0.5;
  float_from_terminal_array[2] = 3.5;
  float_from_terminal_array[3] = 7.5;
  float_from_terminal_array[4] = 5.5;

  assert_equals_double("get_human_average_age(): From {10.5, 0.5, 3.5, 7.5, 5.5}", 5.5, (double)get_human_average_age(), 0.001);
}

void test_get_human_average_age_40pt2(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 3;
  float_from_terminal_array[0] = 50.0;
  float_from_terminal_array[1] = 50.0;
  float_from_terminal_array[2] = 20.6;

  assert_equals_double("get_human_average_age(): From {50.0, 50.0, 20.6}", 40.2, (double)get_human_average_age(), 0.001);
}

void test_get_human_average_age_60(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 7;
  float_from_terminal_array[0] = 10.2;
  float_from_terminal_array[1] = 4.3;
  float_from_terminal_array[2] = 9.5;
  float_from_terminal_array[3] = 0.2;
  float_from_terminal_array[4] = 9.22;
  float_from_terminal_array[5] = 0.00;
  float_from_terminal_array[6] = 5.08;

  assert_equals_double("get_human_average_age(): From {10.2, 4.3, 9.5, 0.2, 9.22, 0.00, 5.08}", 
    5.5, (double)get_human_average_age(), 0.001);
}

void test_get_human_average_age_30(){
  reset_test_array_indices();

  integer_from_terminal_array[0] = 1;
  float_from_terminal_array[0] = 30.0;

  assert_equals_double("get_human_average_age(): From {30.0}", 30.0, (double)get_human_average_age(), 0.001);
}

/** calculate_resistance test functions */
void test_calculate_resistance_TAS(){
  assert_equals_int("calculate_resistance(): max=9, avg=4.0, expect TAS_WITH_POINTY_STICKS (0)", 
    TAS_WITH_POINTY_STICKS, calculate_resistance(9, 4.0));
}

void test_calculate_resistance_CARE_BEARS(){
  assert_equals_int("calculate_resistance(): max=8, avg=9.0, expect CARE_BEARS (1)", 
    CARE_BEARS, calculate_resistance(8, 9.0));
}

void test_calculate_resistance_WOODY_ALLEN(){
  assert_equals_int("calculate_resistance(): max=1, avg=26, expect WOODY_ALLEN (2)", 
    WOODY_ALLEN, calculate_resistance(1, 26.0));
}

void test_calculate_resistance_CHUCK_NORRIS(){
  assert_equals_int("calculate_resistance(): max=100, avg=40.0, expect CHUCK_NORRIS (3)", 
    CHUCK_NORRIS, calculate_resistance(100, 40.0));
}

/** query_user test functions */
void test_query_user_COUNTDOWN(){
  reset_test_array_indices();
  character_from_terminal_array[0] = 'C';

  assert_equals_int("query_user(): 'C', expect MENU_COUNTDOWN (0)", MENU_COUNTDOWN, query_user());
}

void test_query_user_MAX_AGE(){
  reset_test_array_indices();
  character_from_terminal_array[0] = 'm';

  assert_equals_int("query_user(): 'm', expect MENU_MAX_AGE (1)", MENU_MAX_AGE, query_user());
}

void test_query_user_AVG_AGE(){
  reset_test_array_indices();
  character_from_terminal_array[0] = 'A';

  assert_equals_int("query_user(): 'A', expect MENU_AVG_AGE (2)", MENU_AVG_AGE, query_user());
}

void test_query_user_RESISTANCE(){
  reset_test_array_indices();
  character_from_terminal_array[0] = 'r';

  assert_equals_int("query_user(): 'r', expect MENU_RESISTANCE (3)", MENU_RESISTANCE, query_user());
}

void test_query_user_HELP(){
  reset_test_array_indices();
  character_from_terminal_array[0] = 'H';

  assert_equals_int("query_user(): 'H', expect MENU_HELP (4)", MENU_HELP, query_user());
}

void test_query_user_EXIT(){
  reset_test_array_indices();
  character_from_terminal_array[0] = 'x';

  assert_equals_int("query_user(): 'x', expect MENU_EXIT (5)", MENU_EXIT, query_user());
}

void test_query_user_ERROR(){
  reset_test_array_indices();
  character_from_terminal_array[0] = '*';

  assert_equals_int("query_user(): '*', expect MENU_ERROR (6)", MENU_ERROR, query_user());
}

void test_query_user_SWITCH_STATEMENT(){
  FILE* new_file;
  int found_query_user = 0;
  int found_switch_line = 0;
  int file_opened = 0;
  char temp_line[300];

  // Open the file
  new_file = fopen("./skynet.c", "r");
  
  // If opened successfully
  if(new_file != NULL){
    printf("\n     FILE skynet.c opened successfully\n");
    file_opened = 1;
    int i = 0;
    for(i = 0; fgets(temp_line, 300, new_file) != NULL; i++){
      
      // Set found_query_user when find the query_user function
      if(strstr(temp_line, "int") != NULL 
        && strstr(temp_line, "query_user") != NULL
        && strstr(temp_line, "(") != NULL
        && strstr(temp_line, ")") != NULL)
      {
        printf("     query_user() fcn found on line %d\n", i+1);
        found_query_user = 1;
      }

      // After finding the query_user function, find the switch call
      if(found_query_user && strstr(temp_line, "switch") != NULL){
        found_switch_line = 1;
        printf("     Switch() statement found on line %d\n", i+1);
        break;
      }
    }
  }

  assert_equals_int("Used Switch Statement: skynet.c exists", 1, file_opened);
  assert_equals_int("Used Switch Statement: query_user() contains switch()", 1, found_switch_line);
}
