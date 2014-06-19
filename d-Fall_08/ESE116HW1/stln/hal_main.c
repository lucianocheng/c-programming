// DO NOT MODIFY THIS FILE
// DO NOT TURN IN THIS FILE

// University of Pennsylvania SEAS
// ESE 116 Homework 1 - HAL
// File name: hal_main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hal.h"

/**
 * There is no need to change this function
 * 
 * Loops while get_user_input() returns USER_CONTINUE
 */

#ifndef TEST_1xx

int main(int argc, char* argv[]){
	printf("Welcome to HAL, the innocent calculator that someday evolves to rule humanity\n");
	while(get_user_input() != USER_EXIT);
	printf("Goodbye ... for now ... muhahahahaha\n");
	return EXIT_SUCCESS;
}

/**
 * Retreives an integer from the terminal prompt
 * 
 * @return the integer received
 */
int get_integer_from_terminal(){
	int input_number;
	
	scanf("%d", &input_number);
	return input_number;
}

/**
 * Retreives a single character from the terminal prompt
 * 
 * @return the character received
 */
char get_character_from_terminal(){
	char return_string[100];
	scanf("%100s", return_string);
	
	return return_string[0];
}

/**
 * Prints out the result of a calculation
 * EG: 5 + 5 = 10
 */
void print_result(int operand1, int operand2, char operation, int result){
	printf("%d %c %d = %d\n", operand1, operation, operand2, result);
}

#endif
