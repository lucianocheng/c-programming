/**
 * Test ESE 116 HW 04, Spring 2007
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
#include "roster.h"

#define TRUE 1
#define FALSE 0

// Extra functions / variables required for testing
void luke_assert_equals_string(char*, char*, char*);
void initialize_student_roster(Student[], int);

// Test functions
// AddGrade = 25 Points
void addGrade_toEmptyCheckValue();
void addGrade_toOneCheckValue();
void addGrade_toFullCheckReturn();
void addGrade_toEmptyCheckReturn();
void addGrade_toOneCheckReturn();

// DelStudent = 25 Points
void delStudent_End();
void delStudent_MiddleEarly();
void delStudent_MiddleLate();
void delStudent_Beginning(); 
void delStudent_Error();

// FindStudent = 25 Points
void findStudent_a();
void findStudent_c();
void findStudent_t();
void findStudent_z();
void findStudent_error();

// GetStats = 25 Points
void getStats_Average();
void getStats_Max();

/**
 * Setup tester labels
 */
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11604; }

/** 
 * tester main
 */
int main(int argc, char * argv[]) {
	PROBLEM * prob1 = add_new_problem("AddGrade Function", 1);
	PROBLEM * prob2 = add_new_problem("DelStudent Function", 2);
  PROBLEM * prob3 = add_new_problem("FindStudent Function", 3);
  PROBLEM * prob4 = add_new_problem("GetStats Function", 4);

  // AddGrade = 25 Points
  add_new_test(prob1, "addGrade_toEmptyCheckValue", 5, 
    &addGrade_toEmptyCheckValue);
  add_new_test(prob1, "addGrade_toOneCheckValue", 5, 
    &addGrade_toOneCheckValue);
  add_new_test(prob1, "addGrade_toFullCheckReturn", 5, 
    &addGrade_toFullCheckReturn);
  add_new_test(prob1, "addGrade_toEmptyCheckReturn", 5, 
    &addGrade_toEmptyCheckReturn);
  add_new_test(prob1, "addGrade_toOneCheckReturn", 5, 
    &addGrade_toOneCheckReturn);

  // DelStudent = 25 Points
  add_new_test(prob2, "delStudent_End", 5, 
    &delStudent_End);
  add_new_test(prob2, "delStudent_MiddleEarly", 5, 
    &delStudent_MiddleEarly);
  add_new_test(prob2, "delStudent_MiddleLate", 5, 
    &delStudent_MiddleLate);
  add_new_test(prob2, "delStudent_Beginning", 5, 
    &delStudent_Beginning);
  add_new_test(prob2, "delStudent_Error", 5, 
    &delStudent_Error);


  // FindStudent = 25 Points
  add_new_test(prob3, "findStudent_a", 5, 
    &findStudent_a);
  add_new_test(prob3, "findStudent_c", 5, 
    &findStudent_c);
  add_new_test(prob3, "findStudent_t", 5, 
    &findStudent_t);
  add_new_test(prob3, "findStudent_z", 5, 
    &findStudent_z);
  add_new_test(prob3, "findStudent_error", 5, 
    &findStudent_error);

  // GetStats = 25 Points
  add_new_test(prob4, "getStats_Average", 15, 
    &getStats_Average);
  add_new_test(prob4, "getStats_Max", 10, 
    &getStats_Max);

	run_all_tests(argc, argv);
	clean_up();
	return 0;
}

void luke_assert_equals_string(char* name, char* expected, char* received){
  int result;

  result = !strcmp(expected, received);

  assert_equals_int(name, 1, result);
}

/**
 * Creates an empty student roster, with names ranging from a (ascii 97)
 */
void initialize_student_roster(Student roster[], int size){
  int i = 0;
  
  for(i = 0; i < size; i++){
    roster[i].name[0] = (char)(i+97);
    roster[i].name[1] = '\0';
    roster[i].numGrades = 0;
  }

}

// Test functions
// AddGrade = 25 Points
void addGrade_toEmptyCheckValue(){
  Student roster[10];
  initialize_student_roster(roster, 10);

  addGrade(roster, 2, 100);
  
  assert_equals_int("NumGrades Increased to 1", 1, roster[2].numGrades);
  assert_equals_int("Added Grade is 100", 100, roster[2].grades[0]);
}

void addGrade_toOneCheckValue(){
  Student roster[10];
  initialize_student_roster(roster, 10);

  roster[4].numGrades = 1;
  roster[4].grades[0] = 95;
  addGrade(roster, 4, 98);

  assert_equals_int("NumGrades Increased to 2", 2, roster[4].numGrades);
  assert_equals_int("Added Grade is 98", 98, roster[4].grades[1]);
}

void addGrade_toFullCheckReturn(){
  Student roster[10];
  initialize_student_roster(roster, 10);

  roster[1].numGrades = 2;
  roster[1].grades[0] = 95;
  roster[1].grades[1] = 95;
  
  int result = addGrade(roster, 1, 98);

  assert_equals_int("Full, result should equal FALSE", FALSE, result);
}

void addGrade_toEmptyCheckReturn(){
  Student roster[10];
  initialize_student_roster(roster, 10);
  
  int result = addGrade(roster, 5, 98);

  assert_equals_int("Empty, result should equal TRUE", TRUE, result);
}

void addGrade_toOneCheckReturn(){
  Student roster[10];
  initialize_student_roster(roster, 10);
  
  roster[7].numGrades = 1;
  roster[7].grades[0] = 95;

  int result = addGrade(roster, 7, 98);

  assert_equals_int("Only 1, result should equal TRUE", TRUE, result);
}


// DelStudent = 25 Points
void delStudent_End(){
  Student roster[3];
  initialize_student_roster(roster, 3);

  delStudent(roster, 3, 2);

  luke_assert_equals_string("First Student is 'a'", "a", roster[0].name);
  luke_assert_equals_string("Second Student is 'b'", "b", roster[1].name);
}

void delStudent_MiddleEarly(){
  Student roster[4];
  initialize_student_roster(roster, 4);

  delStudent(roster, 4, 1);

  luke_assert_equals_string("First Student is 'a'", "a", roster[0].name);
  luke_assert_equals_string("Second Student is 'c'", "c", roster[1].name);
  luke_assert_equals_string("Third Student is 'd'", "d", roster[2].name);
}

void delStudent_MiddleLate(){
  Student roster[4];
  initialize_student_roster(roster, 4);

  delStudent(roster, 4, 2);

  luke_assert_equals_string("First Student is 'a'", "a", roster[0].name);
  luke_assert_equals_string("Second Student is 'b'", "b", roster[1].name);
  luke_assert_equals_string("Third Student is 'd'", "d", roster[2].name);
}

void delStudent_Beginning(){
  Student roster[3];
  initialize_student_roster(roster, 3);

  delStudent(roster, 3, 0);

  luke_assert_equals_string("First Student is 'b'", "b", roster[0].name);
  luke_assert_equals_string("Second Student is 'c'", "c", roster[1].name);
}

void delStudent_Error(){
  Student roster[3];
  initialize_student_roster(roster, 3);

  delStudent(roster, 3, 6);

  luke_assert_equals_string("First Student is 'a'", "a", roster[0].name);
  luke_assert_equals_string("Second Student is 'b'", "b", roster[1].name);
  luke_assert_equals_string("Third Student is 'c'", "c", roster[2].name);
}


// FindStudent = 25 Points
void findStudent_a(){
  Student roster[26];
  initialize_student_roster(roster, 26);

  int result = findStudent(roster, 26, "a");

  assert_equals_int("Student 'a' index 0", 0, result); 
}

void findStudent_c(){
  Student roster[26];
  initialize_student_roster(roster, 26);

  int result = findStudent(roster, 26, "c");

  assert_equals_int("Student 'c' index 2", 2, result); 
}

void findStudent_t(){
  Student roster[26];
  initialize_student_roster(roster, 26);

  int result = findStudent(roster, 26, "t");

  assert_equals_int("Student 't' index 19", 19, result); 
}

void findStudent_z(){
  Student roster[26];
  initialize_student_roster(roster, 26);

  int result = findStudent(roster, 26, "z");

  assert_equals_int("Student 'z' index 25", 25, result); 
}

void findStudent_error(){
  Student roster[26];
  initialize_student_roster(roster, 26);

  int result = findStudent(roster, 26, "gah");

  assert_equals_int("Student 'gah' returns -1", -1, result); 
}


// GetStats = 25 Points
void getStats_Average(){
  Student roster[10];
  GradeStats result;
  initialize_student_roster(roster, 10);

  roster[0].grades[0] = 100;
  roster[0].numGrades = 1;

  roster[3].grades[0] = 50;
  roster[3].grades[1] = 50;
  roster[3].numGrades = 2;

  roster[5].grades[0] = 0;
  roster[5].grades[1] = 0;
  roster[5].numGrades = 2;

  roster[7].grades[0] = 100;
  roster[7].numGrades = 1;

  result = getStats(roster, 10);

  assert_equals_double("Average should be 50", 50.0, result.averageGrade, 0.001); 
}

void getStats_Max(){
  Student roster[10];
  GradeStats result;
  initialize_student_roster(roster, 10);

  roster[0].grades[0] = 80;
  roster[0].numGrades = 1;

  roster[3].grades[0] = 20;
  roster[3].grades[1] = 21;
  roster[3].numGrades = 2;

  roster[5].grades[0] = 0;
  roster[5].grades[1] = 0;
  roster[5].numGrades = 2;

  roster[7].grades[0] = 81;
  roster[7].numGrades = 1;

  result = getStats(roster, 10);

  assert_equals_int("Max should be 81", 81, result.maxGrade); 
}
