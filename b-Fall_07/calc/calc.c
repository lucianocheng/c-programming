/**
 * A simple command line integer-calculator
 *
 * @version 2007-10-03
 */

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#ifndef TEST_1xx
/* 
 * Usage (where % is the unix shell prompt): 
 *        % ./calc [a|A|s|S|m|M|d|D] integer1 integer2
 *
 * Example:
 *        % ./calc a 2 3
 *        2 + 3 = 5
 */
int main(int argc, char* args[]){
  int operand1, operand2, answer;
  char operator;
  
  if(argc != 4) {
    printUsageMessage();
    return EXIT_FAILURE;
  }

  /* The expression "args[1][0]" means "the 0th (first) character
   * of the second command line argument (the character array at args[1])".
   */
  operator = lookupOperator(args[1][0]);
  if(operator == '?') {
    printUsageMessage();
    return EXIT_FAILURE;
  }

  /* This program assumes that args[2] and args[3] are strings that contain
   * numeric characters, e.g. "45", "235". Since for the homework we're only
   * concerned about the correct behavior of the non-main() methods, this is fine.
   */
  operand1 = atoi(args[2]);
  operand2 = atoi(args[3]);
  answer = evaluateExpression(operator, operand1, operand2);
  printf("%d %c %d = %d\n", operand1, operator, operand2, answer);
}

#endif

int printUsageMessage() {
  printf("Usage: ./calc [a|A|s|S|m|M|d|D] integer1 integer2\n");
  printf("  Example Input:  ./calc a 2 3\n");
  printf("  Example Output: 5\n");
  printf("  Exiting.\n\n");
}


/*
 * lookupOperator() 
 *
 *   Input            Output 
 *   ~~~~~~~~~~       ~~~~~~
 *   'a' or 'A'       '+'
 *   's' or 'S'       '-'
 *   'm' or 'M'       '*'
 *   'd' or 'D'       '/'
 *   anything else    '?'
 */
// PUT CODE FOR lookupOperator() HERE
char lookupOperator(char input){
	return '?'
}


/*
 * The evaluateExpression function
 *
 * Input: 
 *     1. an operator (e.g. '+', '-', '*', '/')
 *     2. an integer (the first operand)
 *     3. an inteter (the second operand)
 *
 * Output: 
 *    The value of the expression (e.g. 8 if the inputs are '+', 3, 5)
 *
 * If operator is invalid, calls the printUsageMessage() and exit(EXIT_FAILURE).
 */
// PUT CODE FOR evaluateExpression() HERE
int evaluateExpression(char a, int b, int c){
	return 1;
}

