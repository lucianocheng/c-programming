// University of Pennsylvania SEAS
// ESE 116 Homework 1 - HAL
// File name: hal.c


#include <stdio.h>
#include <stdlib.h>

#include "hal.h"

/**
 * COMPLETE THIS FUNCTION
 * 
 * This function should accept user input for calculating *, /, + and - operations.
 * When the user does not request an exit (x or X), the function should return USER_CONTINUE,
 * which is defined in hal.h.  When the user requests an exit, it should return USER_EXIT.
 * 
 * This function should do exactly the following:
 * 1. Print "Enter an operator: " to the terminal, and call get_character_from_terminal()
 * 2. Store the returned character from get_character_from_terminal(), 
 * 3. If the character is NOT a '+', '-', '*', '/', 'x' or 'X', print "Error: Invalid Operator <newline>", and
 *    return the value USER_CONTINUE
 * 5. If the character read in is a 'x' or 'X', return the value USER_EXIT, which is defined in hal.h
 * 6. Print "Enter the first operand: ", call get_integer_from_terminal(), and store the return value
 * 7. Print "Enter the second operand: ", call get_integer_from_terminal(), and store the return value
 * 8. Call calc_result with the parameters you stored, and save the result in a variable.
 * 9. Call print_result() with the operand, operator, and result parameters.  This will print the result to the
 *    terminal.
 * 10. Return the value USER_CONTINUE, which is defined in hal.h
 * 
 * Notes:
 * 1. Do not worry about invalid operand (integer) input; assume the user always inputs valid integers
 * 2. Do NOT use getchar(); use get_interger_from_terminal() and get_character_from_terminal() for input 
 *    ONLY.
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
 * This function MUST use a SWITCH STATEMENT to execute the correct operation on the two
 * operands, then return the result.
 * 
 * If the operator is not a supported operation, the function should return -1.
 * This is good practice in case another programmer decides to use the function in his own code.
 * 
 * Under NO circumstances should this function call get_character_from_terminal() or 
 * get_integer_from_terminal(), the function should calculate the result based solely
 * on the parameters (operand1, operand2, and operator).
 * 
 * Notes:
 * 1. The only operations supported are add (+), multiply (*), subtract (-) and divide (/)
 * 2. We only want integer divison
 *    eg: 5 / 6 should return 0
 *        5 / 2 should return 2
 * 3. Assume the operands are valid inputs
 * 4. Do not worry about results being bigger then an integer (integer wrap-around)
 * 5. Do not worry about divide by zero; assume that the division operands will not cause this problem
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
