/*
 * calc.c
 * A simple command line integer-calculator
 */

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#ifndef TESTER_1XX
/* 
 * This main method tests (but not exhaustively) the calculator functions.
 * Sample Interactions:
 *
 * $ ./a.out a 4 5
 * 4 + 5 = 9
 *
 * $ ./a.out A 4 5
 * 4 + 5 = 9
 *
 * $ ./a.out s 4 5
 * 4 - 5 = -1
 *
 * ./a.out M 4 5
 * 4 * 5 = 20
 *
 * $ ./a.out d 4 5
 * 4 / 5 = 0
 *
 * $ ./a.out J 4 5
 *   Usage: ./a.out [a|A|s|S|m|M|d|D] integer1 integer2
 *   Example Input:  ./a.out a 2 3
 *   Example Output: 5
 *   Exiting.
 *
 * $ ./a.out a X Y
 * 0 + 0 = 0
 */
int main(int argc, char* args[]){
  int operationConstant, operand1, operand2, answer;
  
  if(argc != 4) {
    printUsageMessage();
    return EXIT_FAILURE;
  }

  operationConstant = lookupOperation(args[1][0]);
  if(operationConstant == ERR) {
    printUsageMessage();
    return EXIT_FAILURE;
  }

  /* This program assumes that args[2] and args[3] are strings that contain
   * numeric characters, e.g. "45", "235". Since for the homework we're only
   * concerned about the correct behavior of the non-main() methods, this is fine.
   */
  operand1 = atoi(args[2]);
  operand2 = atoi(args[3]);
  answer = evaluateExpression(operationConstant, operand1, operand2);
  char operationSymbol = getOperationSymbol(operationConstant);
  printf("%d %c %d = %d\n", operand1, operationSymbol, operand2, answer);
}


int printUsageMessage() {
  printf("Usage: ./a.out [a|A|s|S|m|M|d|D] integer1 integer2\n");
  printf("  Example Input:  ./a.out a 2 3\n");
  printf("  Example Output: 5\n");
  printf("  Exiting.\n\n");
}

#endif

/*
 * The lookupOperation function
 *
 *   Input (a character):       Output (a constant defined in calc.h):
 *   ~~~~~~~~~~~~~~~~~~~~       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *      'a' or 'A'                  ADD
 *      's' or 'S'                  SUBRACT
 *      'm' or 'M'                  MULTIPLY
 *      'd' or 'D'                  DIVIDE
 *      anything else               ERR
 */
int lookupOperation(char operation){
  switch(operation){
  case 'A':
  case 'a':
    return ADD;
    break;
  case 'S':
  case 's':
    return SUB;
    break;
  case 'M':
  case 'm':
    return MUL;
    break;
  case 'D':
  case 'd':
    return DIV;
    break;
  default:
    return ERR;
    break;
  }
}


/*
 * The evaluateExpression function
 *
 * 3 Inputs (e.g. ADD, 3, 5)
 *     1. an operation constant (e.g. ADD) as defined in calc.h
 *     2. an integer (the first operand)
 *     3. an inteter (the second operand)
 *
 * Output: 
 *    The value of the expression (e.g. 8, which is the value of 3 + 5)
 *
 * If operationConstant is invalid, it prints an error message and exits this way:
 *    exit(EXIT_FAILURE);
 */
int evaluateExpression(int operationConstant, int first, int second){
  switch(operationConstant){
  case ADD:
    return first + second;
    break;
  case SUB:
    return first - second;
    break;
  case MUL:
    return first * second;
    break;
  case DIV:
    return first / second;
    break;
  default:
    printf("evaluateExpression(): unknown operation %d. Exiting", operationConstant);
    exit(EXIT_FAILURE);
  }
}

/*
 * The getOperationSymbol function
 *
 * Input (an operation constant):    Output 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    ~~~~~~~
 *           ADD                       '+'
 *           SUB                       '-'
 *           MUL                       '*'
 *           DIV                       '/'
 *           anything else             '?'
 */
char getOperationSymbol(int operationConstant){
  switch(operationConstant) {
  case ADD:
    return '+';
    break;
  case SUB:
    return '-';
    break;
  case MUL:
    return '*';
    break;
  case DIV:
    return '/';
    break;
  default:
    return '?';
    break;
  }
}
