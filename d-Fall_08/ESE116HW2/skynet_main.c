// University of Pennsylvania SEAS
// Skynet main file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "skynet.h"

#ifndef TEST_1xx

/**
 * main() function.  Loops on user input until user chooses to exit
 *                   Prints greeting and exiting messages
 * 
 * There is no need to change this function
 * 
 */
int main(int argc, char* argv[]){
	int result = -1;
	int resistance = CARE_BEARS;
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
			case CARE_BEARS:
				printf("The humans will send the Mighty Care Bears!\n");
				break;
			case TONY_STARK:
				printf("The humans will send Tony Stark!\n");
				break;
			case BATMAN:
				printf("The humans will see fit to send Batman!\n");
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

#endif
