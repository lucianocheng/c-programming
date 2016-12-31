// University of Pennsylvania SEAS
// ESE 116 Homework 2 - SKYNET

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "skynet.h"

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to begin the countdown of the SkyNet initiation protocol
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. The data for this function is given in the arguments
 *    Look at the printf example on the homework webpage for how to print out a certain decimal precision 
 *    Print out the human data using printf according to the following example:
 *    "Human Average Age: 56.65, Human Maximum Age: 101"
 *    "Beginning Countdown From 55..."
 
 * 2. Countdown from the maximum countdown time to 0.
 * 
 *    YOU MUST USE THE print_countdown_int() FUNCTION FOR THE COUNT DOWN
 * 
 *    When using print_countdown_int(), the output will look like the following example: 
 *    "Countdown: 5"
 *    "Countdown: 4"
 *    "Countdown: 3"
 *    "Countdown: 2"
 *    "Countdown: 1"
 *    "Countdown: 0"
 * 
 */
void count_down(int max_age, float average_age, int count_down_start){
	int i = 0;
	
	printf("Human Average Age: %.2f, Human Maximum Age: %d\n", average_age, max_age);
	printf("Beginning Countdown From %d...\n", count_down_start);
	
	for(i = count_down_start; i >= 0; i--){
		print_countdown_int(i);
	}
}

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to calculate the maximum age of a human, as inputted by the user
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. Print "How many ages?: " using printf
 * 2. Prompt the user for the number of ages by calling get_integer_from_terminal(), 
 *    and saving the inputted number.
 * 2. Loop for the number of times as inputted by the user above
 * 3. For each loop, print "Input an age: ", call get_integer_from_terminal(), 
 *    and keep track of the MAXIMUM age inputted by the user
 * 4. Return the maximum age inputted by the user
 * 
 * NOTE: You can assume the user will not input negative ages
 * NOTE: DO NOT USE get_float_from_terminal() IN THIS FUNCTION
 * 
 * @return the maximum age inputted by the user.
 */
int get_human_max_age(){
	int age_count = 0;
	int i, temp_age;
	int max_age = 0;
	
	printf("How many ages?: ");
	age_count = get_integer_from_terminal();

	for(i = 0; i < age_count; i++){
		printf("Input an age: ");
		temp_age = get_integer_from_terminal();
		if(temp_age > max_age) max_age = temp_age;
	}
	
	return max_age;
}

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to calculate the average age of the human ages inputted by the user
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. Print "How many ages?: "
 * 2. Prompt the user for the number of ages by calling 
 *    calling get_integer_from_terminal(), and saving the inputted number.
 * 2. Loop for the number of times as inputted by the user.
 * 3. For each loop, print "Input an age: ", call get_float_from_terminal(), store the result, 
 *    and keep track of the average age
 * 4. Return the average of the ages inputted by the user
 * 
 * NOTE: Assume the user will not input negative ages
 * NOTE: REMEMBER to use get_float_from_terminal() for entering ages in this function
 * 
 * @return The average human age, as a float
 */
float get_human_average_age(){
	int age_count = 0;
	int i;
	float age_total=0.0;
	
	printf("How many ages?: ");
	age_count = get_integer_from_terminal();

	for(i = 0; i < age_count; i++){
		printf("Input an age: ");
		age_total+=get_float_from_terminal();
	}
	
	return age_total / (float)age_count;
}

/**
 * --- COMPLETE THIS FUNCTION ---
 * 
 * The purpose of this function is to calculate the expected human resistance
 * 
 * CODE THIS FUNCTION TO DO THE FOLLOWING:
 * 1. Return the correct constant based on the human age statistics, according to the following:
 *    Maximum is less than 10 and average is less than 5 ...
 *        --> return CARE_BEARS, which is defined in skynet.h
 *    If above is not true, and Maximum is between 5 and 10 inclusive, or average is less than 25 ...
 *        --> return TONY_STARK, which is defined in skynet.h
 *    If none above are true, and Maximum * average is less than 30.5 ...
 *        --> return BATMAN, which is defined in skynet.h
 *    If none above are true
 *        --> return CHUCK_NORRIS, which is defined in skynet.h
 * 
 * NOTE: The constants you are returning are defined in skynet.h
 */
int calculate_resistance(int max_human_age, float avg_human_age){
	if(max_human_age < 10 && avg_human_age < 5.0) return CARE_BEARS;
	if((max_human_age > 5 && max_human_age < 10) || avg_human_age < 25) return TONY_STARK;
	if(max_human_age * (float)avg_human_age < 30.5) return BATMAN;
	return CHUCK_NORRIS;
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
	printf("QUERY: ");
	switch(get_character_from_terminal()){
	case 'c':                             // Count Down
	case 'C':
		return MENU_COUNTDOWN;
		break;
	case 'm':
	case 'M':
		return MENU_MAX_AGE;
		break;
	case 'a':
	case 'A':
		return MENU_AVG_AGE;
		break;
	case 'r':
	case 'R':
		return MENU_RESISTANCE;
		break;
	case 'h':
	case 'H':
		return MENU_HELP;
		break;
	case 'x':
	case 'X':
		return MENU_EXIT;
		break;
	}
	return MENU_ERROR;
}
