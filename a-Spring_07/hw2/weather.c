/**
 * Weather Reporter main function(s)
 * Collects and calculates weather information
 *
 * @author Mark Fickett
 * @author Jean Griffin
 * @version 2007 Feb 15
 */

#include <stdio.h>
#include <stdlib.h>
#include "weather.h"

#ifndef TEST_1XX
/**
 * Run the Weather Reporter main text UI:
 * Until end of input (EOF),
 * prompt for new weather information and/or
 * calculate stats for existing data.
 */
int main() {
  //WeatherRecord stats;
  WeatherRecord data[MAX_RECORDS];
  int numRecords = 0;
  int keepGoing = TRUE;
  WeatherRecord stats;
  
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
	if (getWeatherRecord(data, numRecords) == TRUE)
	  numRecords++;
      }
      break;
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
#endif

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

/**
 * Prompt for a character.
 * @param prompt a string to prompt with
 * @param legal a string containing all legal char responses
 * @return the character chosen, or '\0' on error.
 */
int promptUserForChoice(){
  char prompt[] = 
    "\nMenu:\n\t(e)nter data\n\t(c)lear data\n\t(p)rint records\n\t(q)uit\n\nEnter choice: ";
  char legalChoices[] = "ecqp";
  int tries, response;
  for(tries = 1; tries <= MAX_PROMPTS; tries++) {
    printf(prompt);
    response = getchar();
    flush();
#ifdef DEBUG
    printf("User chose '%c'\n", response);
#endif
    if (isLegalChoice(response, legalChoices))
      return response;
    printf("Illegal response '%c'. ", response);
    if (tries < MAX_PROMPTS)
      printf("Try again.\n");
    else
      printf("Giving up.\n");
  }
  return '\0';
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
 * Returns a WeatherRecord with the average rainfall and max temperature
 * of the WeatherRecords in the data array (whose number is numRecords).
 * @param data an array of WeatherRecords
 * @param numRecords the number of records to process
 * @return a WeatherRecord with the results
 */
WeatherRecord computeStats(WeatherRecord data[], int numRecords) {
  WeatherRecord stats;
  
  int i;
  double rainfallTotal, tempMax = data[0];
  
  for(i = 0; i < numRecords; i++){
	rainfallTotal+=data[i].rainfall;
	if(data[i].temp > tempMax) tempMax = data[i].temp;
  }
  
  stats.rainfall = rainfallTotal / numRecords;
  stats.temp = tempMax;
  return stats;
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
    //flush();
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
