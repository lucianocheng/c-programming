/*
	Part 1: Create A bowling database:
	
	Create a program that takes input from the command line and creates a array of
	of BowlingRecords
	
	The program first reads in the data from input, loads it into the array, and
	prints out the data from the database.
	
	COMPILE LINE:
		gcc -Wall -o bowling bowling.c

	TEST COMMAND LINE EXAMPLE (Copy and paste to test):
	
	$> ./bowling Luke 80 14.5 Mark 160 12 Jean 200 10.5
	name: Luke, average: 80, shoe size: 14.500000
	name: Mark, average: 160, shoe size: 12.000000
	name: Jean, average: 200, shoe size: 10.500000
	
	$> ./bowling Bender 300 20 Leela 100 13.5 Fry 10 10.2
	name: Bender, average: 300, shoe size: 20.000000
	name: Leela, average: 100, shoe size: 13.500000
	name: Fry, average: 10, shoe size: 10.200000

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_RECORDSIZE 10
#define EXIT_SUCCESS 0

/* Create a struct called bowlingRecord (typedef'd as BowlingRecord)
   with 3 member variables:
		A char array of size 80, called name
		A integer, called average
		A double, called shoeSize
*/

typedef struct bowlrecord {
  char name[80];
  int average;
  double shoeSize;
} BowlingRecord;

void printBowlingRecord(BowlingRecord);

int main(int argc, char* argv[]){

	int recordCount;

	if(((argc - 1) % 3 != 0) || (argc - 1) / 3 > 10 || argc <= 1){
		printf("Input error: Must input data in sets of 3, and no more than 10 sets\n");
		return -1;
	}
	
	recordCount = (argc - 1) / 3;
	
	// Create an array of BOWLING_RECORDs of size MAX_RECORDSIZE called recordList
	BowlingRecord recordList[MAX_RECORDSIZE];
	
	/* Create a for loop to initilize all values in recordList as follows:
		Average: 0
		shoeSize: 0
		name: "None"
	*/
	int i = 0;
	for(i = 0; i < MAX_RECORDSIZE; i++){
		recordList[i].average = 0;
		recordList[i].shoeSize = 0;
		strcpy(recordList[i].name, "None");
	}

	// Create a for loop to loop through the input arguments in argv and put the data
	//     in the struct array
	// REMEMBER: The first argument in argv is the program name
	// The arguments in argv are in sets of three, so they are {NAME, AVERAGE, SHOE SIZE}
	// Use atoi (alpha to integer) and atof (alpha to float) to turn the arguments into numbers when necessary
	// Note: For the for loop, it is recommend you use two counter, one for the argument index,
	//       one for the object array index
	i = 1;
	int j = 0;
	for(j = 0; i < argc && j < MAX_RECORDSIZE; j++){
		strcpy(recordList[j].name, argv[i]);
		i++;
		recordList[j].average = atoi(argv[i]);
		i++;
		recordList[j].shoeSize = atof(argv[i]);
		i++;
	}
	
	// Create a for loop to loop through all the records, and print off the data
	// use the "Print Bowling Record" function
	for(i = 0; i < recordCount; i++){
		printBowlingRecord(recordList[i]);
	}

	return EXIT_SUCCESS;

}

/*
	Create a function that printf's the data from a BOWLING_RECORD struct
	in the following format:
		
		name: <name>, average: <average>, shoe size: <shoeSize>
		
		Example:
		name: Fry, average: 10, shoe size: 10.2
*/
void printBowlingRecord(BowlingRecord br){
  printf("name: %s, average: %d, shoe size: %f\n", br.name, br.average, br.shoeSize);
}
