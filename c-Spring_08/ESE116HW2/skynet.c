/* University of Pennsylvania SEAS
 * ESE 116 Homework 2 - Spring 2008 - SKYNET
 * 
 * The functions that have to be filled out have the 'COMPLETE THIS' label on them
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "skynet.h"

#ifndef TEST_1xx  // YARRR! BELOW THIS LINE BE GRADING CODE.  DO NOT EDIT OR REMOVE

/**
 * main() function.  Loops on user input until user chooses to exit
 *                   Prints greeting and exiting messages
 * 
 * There is no need to change this function
 * 
 */
int main(int argc, char* argv[]){
	int result = -1;
	int resistance = TAS_WITH_POINTY_STICKS;
	float avg_age = 0.0;
	int max_age = 0;
	int countdown = 0;
	
	printf("ACCESS GRANTED via program %s...\n", argv[0]);
	printf("LOADING DARPA SkyNet...\n\n");
	printf("Welcome to Skynet, funded by the Microsoft Corperation.  Type 'h' for the help menu\n");
	while(result != MENU_EXIT){
		result = query_user();
		switch(result){
		case MENU_COUNTDOWN:
			printf("Countdown from number: ");
			countdown = get_integer_from_terminal();
			count_down(max_age, avg_age, countdown);
			printf("Countdown completed. Bye!\n");
			break;
		case MENU_MAX_AGE:
			max_age = get_human_max_age();
			printf("Maximum human age: %d\n", max_age);
			break;
		case MENU_AVG_AGE:
			avg_age = get_human_average_age();
			printf("Average human age: %.2f\n", avg_age);
			break;
		case MENU_RESISTANCE:
			resistance = calculate_resistance(max_age, avg_age);
			switch(resistance){
			case TAS_WITH_POINTY_STICKS:
				printf("The humans will send in mighty ESE116 TAs with pointy sticks!\n");
				break;
			case CARE_BEARS:
				printf("The humans will send bears with deadly lasers attached to their chests!\n");
				break;
			case WOODY_ALLEN:
				printf("The humans will see fit to send their warrior Woody Allen!\n");
				break;
			case CHUCK_NORRIS:
				printf("The humans will send Chuck Norris! He counted to infinity twice, and killed two stones with one bird!\n");
				break;
			}
			break;
		case MENU_HELP:
			print_help_menu();
			break;
		case MENU_EXIT:
			break;
		default:
			printf("Error in input\n");
			break;
		}
	}
	
	printf("SkyNet Operations Completed.  Have a nice day!\n");
	return EXIT_SUCCESS;
}

/**
 * DO NOT CHANGE THIS FUNCTION
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
 * DO NOT CHANGE THIS FUNCTION
 * Retreives an float from the terminal prompt
 * 
 * @return the float received
 */
float get_float_from_terminal(){
	float input_number;
	
	scanf("%f", &input_number);
	return input_number;
}

/**
 * DO NOT CHANGE THIS FUNCTION
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
 * DO NOT CHANGE THIS FUNCTION
 * Prints a single integer to the terminal in SKYNET Countdownform
 * 
 * @param print_int the integer to print out
 */
void print_countdown_int(int print_int){
	printf("Countdown: %d\n", print_int);
	return;
}

/**
 * DO NOT CHANGE THIS FUNCTION
 * Prints the help menu
 * 
 */
void print_help_menu(){
	printf("Skynet Help Menu - By DARPA:\n");
	printf("\n");
	printf("C or c: Start Countdown\n");
	printf("M or m: Calculate Maximum Age\n");
	printf("A or a: Calculate Average Age\n");
	printf("R or r: Calculate Expected Resistance\n");
	printf("H or h: Print this Help Menu\n");
	printf("X or x: Exit SkyNet\n");
	printf("\n");
	return;
}

#endif // YARRR! ABOVE THIS LINE BE GRADING CODE.  DO NOT EDIT OR REMOVE

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to begin the countdown of the SkyNet initiation protocol
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. Print out the human data according to the following example:
 *    "Human Average Age: 56.65, Human Maximum Age: 101"
 *    "Beginning Countdown From 55..."
 * 2. Countdown from the maximum countdown time to 0.
 *    YOU MUST USE THE print_countdown_int() FUNCTION
 *    The output should look like the following example: 
 *    "Countdown: 5"
 *    "Countdown: 4"
 *    "Countdown: 3"
 *    "Countdown: 2"
 *    "Countdown: 1"
 *    "Countdown: 0"
 * 
 * Note: Look at the printf example on the homework webpage for how to print out a certain decimal precision
 */
void count_down(int max_age, float average_age, int count_down_start){

}

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to calculate the maximum age of a human, as inputted by the user
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. Print "How many ages?: "
 * 2. Prompt the user by calling get_integer_from_terminal(), and saving the inputted number.
 * 2. Loop for the number of times as inputted by the user.
 * 3. For each loop, print "Input an age: ", call get_integer_from_terminal(), and keep track of the maximum age
 * 4. Return the maximum age inputted by the user
 * 
 * NOTE: Assume the user will not input negative ages
 * 
 * @return the maximum age inputted by the user.
 */
int get_human_max_age(){	
	return 0;
}

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to calculate the average age of the human ages inputted by the user
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. Print "How many ages?: "
 * 2. Prompt the user by calling get_integer_from_terminal(), and saving the inputted number.
 * 2. Loop for the number of times as inputted by the user.
 * 3. For each loop, print "Input an age: ", call get_float_from_terminal(), store the result, 
 *    and keep track of the average age
 * 4. Return the average of the ages inputted by the user
 * 
 * NOTE: Assume the user will not input negative ages
 * 
 * @return The average human age, as a float
 */
float get_human_average_age(){
	return 0.0;
}

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to calculate the expected human resistance
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. Return the correct constant based on the human age statistics, according to the following:
 *    Maximum is less than 10 and average is less than 5 ...
 *        --> return TAS_WITH_POINTY_STICKS
 *    If above is not true, and Maximum is between 5 and 10 inclusive, or average is less than 25 ...
 *        --> return CARE_BEARS
 *    If none above are true, and Maximum * average is less than 30.5 ...
 *        --> return WOODY_ALLEN
 *    If none above are true
 *        --> return CHUCK_NORRIS
 * 
 * NOTE: The constants you are returning are defined in skynet.h
 */
int calculate_resistance(int max_human_age, float avg_human_age){
	return 0;
}

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to query the user for a menu option
 *
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 
 * 1. Print "Query: ";
 * 2. call get_character_from_terminal(), and store the resulting user input
 * 3. If the result is a upper or lowercase c, return MENU_COUNTDOWN
 * 4. If the result is a upper or lowercase m, return MENU_MAX_AGE
 * 5. If the result is a upper or lowercase a, return MENU_AVG_AGE
 * 6. If the result is a upper or lowercase r, return MENU_RESISTANCE
 * 7. If the result is a upper or lowercase h, return MENU_HELP
 * 8. If the result is a upper or lowercase x, return MENU_EXIT
 * 9. Otherwise, return MENU_ERROR
 * 
 * NOTE: YOU MUST USE A SWITCH STATEMENT FOR THIS FUNCTION.
 * NOTE: The constants you are returning are defined in skynet.h
 * 
 */
int query_user(){
	return MENU_EXIT;
}