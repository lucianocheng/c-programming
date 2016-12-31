// University of Pennsylvania SEAS
// ESE 116 Homework 2 - Spring 2008 - SKYNET
// skynet.h

#ifndef SKYNET_H_
#define SKYNET_H_

// Declaration of constants used in skynet.c, similar to the 'final' keyword in java
#define TAS_WITH_POINTY_STICKS 0
#define CARE_BEARS 1
#define WOODY_ALLEN 2
#define CHUCK_NORRIS 3

#define MENU_COUNTDOWN 0
#define MENU_MAX_AGE 1
#define MENU_AVG_AGE 2
#define MENU_RESISTANCE 3
#define MENU_HELP 4
#define MENU_EXIT 5
#define MENU_ERROR 6

// Functions headers (aka, function prototypes).  Functions are defined in skynet.c
int get_integer_from_terminal();
float get_float_from_terminal();
char get_character_from_terminal();
void print_countdown_int(int);
void print_help_menu();
void count_down(int, float, int);
int get_human_max_age();
float get_human_average_age();
int calculate_resistance(int, float);
int query_user();

#endif /*SKYNET_H_*/
