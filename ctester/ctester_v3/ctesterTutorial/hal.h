// DO NOT MODIFY THIS FILE
// DO NOT TURN IN THIS FILE

// University of Pennsylvania SEAS
// ESE 116 Homework 1 - HAL
// File name: hal.h

#ifndef HAL_H_
#define HAL_H_

// Declaration of constants used in hal.c, similar to the 'final' keyword in java
#define USER_EXIT 0
#define USER_CONTINUE 1

// Functions headers (aka, function prototypes).

// Defined in hal_main.c, do NOT modify these
void print_result(int, int, char, int);
int get_integer_from_terminal();
char get_character_from_terminal();

// Defined in hal.c, you fill in these functions and turn them in
int get_user_input();
int calc_result(int, int, char);

#endif /*HAL_H_*/
