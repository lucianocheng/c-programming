// University of Pennsylvania SEAS
// ESE 116 Homework 1 - Spring 2007 - HAL

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
 * 
 * @return the character received
 */
void print_result(int operand1, int operand2, char operation, int result){
	printf("%d %c %d = %d\n", operand1, operation, operand2, result);
}

#endif

/**
 * COMPLETE THIS FUNCTION
 * 
 * This function should accept user input for calculating *, /, + and - operations.
 * When the user does not request an exit (x or X), the function should return USER_CONTINUE,
 * which is defined in hal.h.  When the user requests an exit, it should return USER_EXIT.
 * 
 * This function must write the approperate value to result_graded, defined in hal.h.  The details of what to
 * store in this variable is described below
 * 
 * This function should specifically do the following:
 * 1. Print "Enter an operator: " to the terminal, and call get_character_from_terminal()
 * 2. Store the returned character from get_character_from_terminal(), 
 * 3. If the character is not a '+', '-', '*', '/', 'x' or 'X', print "Error: Invalid Operator <newline>" and
 *    return the value USER_CONTINUE
 * 5. If the character read in is a 'x' or 'X', return the value USER_EXIT
 * 6. Print "Enter the first operand: ", call get_integer_from_terminal(), and store the return value
 * 7. Print "Enter the second operand: ", call get_integer_from_terminal(), and store the return value
 * 8. Call calc_result with the parameters you stored, and store the result.
 *    Also, copy this value to the global variable result_graded defined in hal.h (for grading purposes)
 * 9. Call print_result() with the operand, operator, and result parameters.  This will print the result to th
 *    terminal.
 * 10. Return the value USER_CONTINUE
 * 
 * Notes:
 * 1. Do not worry about invalid operand (integer) input, assume the user always inputs valid integers
 */
int get_user_input(){
	char operator;
	int first_operand, second_operand, result;
	
	printf("Enter an operator: ");
	operator = get_character_from_terminal();
	
	if(operator!='+' && operator!='-' && operator!='*' && operator!='/' && operator!='x' && operator!='X'){
		printf("Error: Invalid Operator '%c'\n", operator);
		return USER_CONTINUE;
	}
	
	if(operator=='x' || operator=='X'){
		return USER_EXIT;
	}
	
	printf("Enter the first operand: ");
	first_operand = get_integer_from_terminal();
	
	printf("Enter the second operand: ");
	second_operand = get_integer_from_terminal();
	
	result = calc_result(first_operand, second_operand, operator);

	print_result(first_operand, second_operand, operator, result);
	
	return USER_CONTINUE;
}

/**
 * COMPLETE THIS FUNCTION
 * 
 * This function should use a SWITCH STATEMENT to execute the correct operation on the two
 * operands, then return the result.
 * 
 * If the operator is not a supported operation, the function should return -1.
 * This is good practice in case another programmer decides to use the function in his own code.
 * 
 * Notes:
 * 1. The only operations supported are add (+), multiply (*), subtract (-) and divide (/)
 * 2. We only want integer divison
 *    EG: 5 / 6 should return 0
 * 3. Assume the operands are valid inputs
 * 4. Do not worry about integer wrap-around
 * 5. Do not worry about divide by zero, assume that the division operands will not cause this problem
 */
int calc_result(int operand1, int operand2, char operator){
	
	switch(operator){
	case '+':
		return operand1 + operand2;
		break;
	case '-':
		return operand1 - operand2;
		break;
	case '*':
		return operand1 * operand2;
		break;
	case '/':
		return operand1 / operand2;
		break;
	}
	
	return -1;
}
