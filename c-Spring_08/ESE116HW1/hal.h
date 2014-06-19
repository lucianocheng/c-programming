// University of Pennsylvania SEAS
// ESE 116 Homework 1 - Spring 2007 - HAL
// hal.c

#ifndef HAL_H_
#define HAL_H_

// Declaration of constants used in hal.c, similar to the 'final' keyword in java
#define USER_EXIT 0
#define USER_CONTINUE 1

// Functions headers (aka, function prototypes).  Functions are defined in hal.c
int get_user_input();
int calc_result(int, int, char);
void print_result(int, int, char, int);
int get_integer_from_terminal();
char get_character_from_terminal();

#endif /*HAL_H_*/
