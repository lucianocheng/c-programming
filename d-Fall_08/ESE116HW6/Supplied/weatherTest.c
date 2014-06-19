/**
 * WeatherTest 
 * Collects and calculates weather information
 *
 * @author upenn ese116 staff
 * @version 2008 April 3
 */

#include <stdio.h>
#include <stdlib.h>
#include "weather.h"

// Prompt the user to add data to or make queries on a weather database.
int main() {
  WeatherRecord data[MAX_RECORDS];
  WeatherRecord* pointers[MAX_RECORDS];
  int numRecords = 0;
  int keepGoing = TRUE;
  WeatherRecord stats;
  double myrain1;
  double mytemp1;
  while (keepGoing == TRUE) {
    int choice = promptUserForChoice();
    switch (choice) {
    case 'c': // clear
      numRecords = 0;
      printf("Records cleared.\n");
      break;
    case 'p': // print
      printWeatherRecords(data, numRecords);
      break;
    case 's': // stats 
      if (numRecords == 0)
	printf("No records yet. ");
      else {
	stats = computeStats(data, numRecords);
	printf("Average rainfall: %5.2f, High Temperature: %5.2f",
	       stats.rainfall, stats.temp);
      }
      break;
    case 'e': // enter data
      if (numRecords >= MAX_RECORDS) 
	printf("Can not enter more data; database is full with %d records.\n",
                                      MAX_RECORDS);
      else {
	if (getWeatherRecord(data, numRecords) == TRUE){
	  numRecords++;
	  pointers[numRecords-1] = &(data[numRecords-1]);
	}
      }
      break;

      /////////ADDED FOR WEATER CORRECTION
    case 'i': // enter data
      makeImperial( pointers, numRecords );
      break;
    case 'm': // enter data
      makeMetric( pointers, numRecords );
      break;
    case 'o': // enter data
      getOffset( &myrain1, &mytemp1 );
      addOffset( pointers, myrain1, mytemp1, numRecords );
      break;
      ///////////////////////

    case '\0':
    case 'q':
      keepGoing = FALSE;
      break;
    default:
      printf("Bad option: %c. Try again\n", choice);
      flush();
      break;
    }
    printf("\n");
  }
  printf("Goodbye!\n");
  return EXIT_SUCCESS;
}


void printWeatherRecords(WeatherRecord records[], int numRecords) {
  if (numRecords == 0){
    printf("No records yet.");
    return;
  }
  printf("\nPrinting %d records:\n", numRecords);
  printf("\t\t         Rain   Temp\n");
  int i = 0;
  for ( ; i < numRecords; i++){
    printf("\t\t[%3d]: \t%5.2f   %5.2f\n", i, records[i].rainfall, records[i].temp);
  }
  return;
}


int isLegalChoice(int response, char legalChars[]){
  int i = 0;
  char choice = (char)response;
  for (i = 0; legalChars[i] != '\0'; i++) {
    if (choice == legalChars[i]) {
      #ifdef DEBUG
      fprintf(stderr, "isLegalChoice(): choice is %c:  TRUE\n", choice);
      #endif
      return TRUE;
    }
  }
#ifdef DEBUG
  fprintf(stderr, "isLegalChoice():  FALSE");
#endif
  return FALSE;
}


/**
 * Prompt for the user to input data for a weather record.
 * @return 0 on success,
 *	-1 on failure such as EOF that should cause program termination
 *	// 1 on failure such as bad user input that might cause retry
 */
int getWeatherRecord(WeatherRecord data[], int nextRecord) {
  WeatherRecord record;
  record.rainfall = FAULTY_DATA;
  record.temp   = FAULTY_DATA;
  int numTries = 0;
  int numDataItemsRcvd;
  do {
    printf("Enter rainfall and temperature with just a space in between: ");
    numDataItemsRcvd = scanf("%lf %lf", &record.rainfall, &record.temp);
    flush();
    numTries++;
    if (numDataItemsRcvd < 2 ) {
      printf("Data input error.");
      if (numTries < MAX_PROMPTS)
	printf(" Try again.\n\n");
    }
  }while (numDataItemsRcvd != 2 && numTries < MAX_PROMPTS);
  if (numTries > MAX_PROMPTS) {
    printf("Giving up effort to collect weather record data.");
    return 0;  // failure; 0 records added
  }
  else {
    fprintf(stderr, "Successfully added record #%d.", nextRecord + 1);
    data[nextRecord] = record;
    return 1;  // success; 1 record added
  }
}

int flush() {
  int c;
  while (!( (c = getchar()) == '\n' || c == EOF)) {
    ;
  }
  return c;
}

int getOffset( double* rain, double* temp ) {
  *rain = FAULTY_DATA;
  *temp = FAULTY_DATA;
  int numTries = 0;
  int numDataItemsRcvd;
  do {
    printf("Enter rainfall and temperature offsets with just a space in between: ");
    numDataItemsRcvd = scanf("%lf %lf", rain, temp);
    flush();
    numTries++;
    if (numDataItemsRcvd < 2 ) {
      printf("Data input error.");
      if (numTries < MAX_PROMPTS)
	printf(" Try again.\n\n");
    }
  }while (numDataItemsRcvd != 2 && numTries < MAX_PROMPTS);
  if (numTries > MAX_PROMPTS) {
    printf("Giving up effort to collect weather record offset data.");
    return 0;  // failure; 0 records added
  }
  else {
    fprintf(stderr, "Successfully got offsets!\n");
    return 1;  // success; 1 record added
  }
}
