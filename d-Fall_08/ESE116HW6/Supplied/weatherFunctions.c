/**
 * weatherFunctions.c
 *
 * @author upenn ese116 staff
 * @version 2008 April 3
 */

#include <stdio.h>
#include <stdlib.h>
#include "weather.h"

/**
 * Prompt for a character.
 * @param prompt a string to prompt with
 * @param legal a string containing all legal char responses
 * @return the character chosen, or '\0' on error.
 */
int promptUserForChoice(){

  // ADJUST CODE BELOW
  char prompt[] =
    "\nMenu:\n\t(e)nter data\n\t(c)lear data\n\t(p)rint records\n\t(q)uit\n\nEnter choice: ";
  char legalChoices[] = "ecqp";
  // ADJUST CODE ABOVE

  int tries, response;
  for(tries = 1; tries <= MAX_PROMPTS; tries++) {
    printf(prompt);
    response = getchar();
    flush();
    printf("User chose '%c'\n", response);
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




/**
 * Returns a WeatherRecord with the average rainfall and max temperature
 * of the WeatherRecords in the data array (whose number is numRecords).
 * @param data an array of WeatherRecords
 * @param numRecords the number of records to process
 * @return a WeatherRecord with the results
 */
WeatherRecord computeStats(WeatherRecord data[], int numRecords) {
  WeatherRecord stats;

  // FIX CODE BELOW
  stats.rainfall  = FAULTY_DATA;
  stats.temp      = FAULTY_DATA;
  // FIX CODE ABOVE

  return stats;

}

/**
 * Given an array of WeatherRecords, correct them all take the given offsets in measurement.
 */
void addOffset( WeatherRecord* wr[], double rainOffset, double tempOffset, int numRecords  ){

}

/**
 * This function adjusts numRecords worth WeatherRecords in wr so that each entry is recorded in metric units (Celsius and centimeters).
 * The assumption is that all WetherRecords are in Imperial units to start. (Fahrenheit and inches)
 * Use precision of three significant figures (aka, x.xx, .yyy, ttt0)
 */

void makeMetric( WeatherRecord* wr[], int numRecords ){

  // Code to make all wr's have metric units!

}

/**
 * This function adjusts numRecords worth WeatherRecords in wr so that each entry is recorded in imperial units (Fahrenheit and inches)
 * The assumption is that all WetherRecords are in metric units to start. (Celsius and centimeters).
 * Use precision of three significant figures (aka, x.xx, .yyy, ttt0)
 */

void makeImperial( WeatherRecord* wr[], int numRecords ){

  // Code to make all wr's have metric units!

}
