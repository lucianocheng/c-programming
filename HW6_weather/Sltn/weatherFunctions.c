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
  char prompt[] = 
    "\nMenu:\n\t(e)nter data\n\t(c)lear data\n\t(p)rint records\n\t(s)stats\n\t(m)etric\n\t(i)mperial\n\t(o)ffset\n\t(q)uit\n\nEnter choice: ";
  char legalChoices[] = "ecqpsmio";
  int tries, response;
  for(tries = 1; tries <= MAX_PROMPTS; tries++) {
    printf(prompt);
    response = getchar();
    flush();
    #ifdef DEBUG
    printf("User chose '%c'\n", response);
    #endif
    if (isLegalChoice(response, legalChoices)){
      return response;
    }
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
  stats.rainfall  = FAULTY_DATA;
  stats.temp      = FAULTY_DATA;

  double sum;
  double max;
  sum = data[0].rainfall;
  max = data[0].temp;
#ifdef DEBUG
  fprintf(stderr, "getStats (datum 0): rainfall=%f temp=%f\n", sum, max);
#endif
  int i;
  for (i = 1; i < numRecords; i++) {
#ifdef DEBUG
    fprintf(stderr, "getStats (datum %d): rainfall=%f temp=%f\n", i, data[i].rainfall, data[i].temp);
#endif
    sum += data[i].rainfall;
    if (data[i].temp > max) {
      max = data [i].temp;
#ifdef DEBUG
      fprintf(stderr, "getStats: new high temp %f\n", max);
#endif
    }
  }
  stats.rainfall = sum / numRecords;
  stats.temp = max;
  return stats;
}

/**
 * Given an array of WeatherRecords, correct them all take the given offsets in measurement.
 */
void addOffset( WeatherRecord* wr[], double rainOffset, double tempOffset, int numRecords  ){
  ///////////// Answer!
 int i = 0;
  for(i=0; i < numRecords; i++ ){
    wr[i]->rainfall += rainOffset;
    wr[i]->temp += tempOffset;
  }
  ///////////////
}

/**
 * This function adjusts numRecords worth WeatherRecords in wr so that each entry is recorded in metric units (Celsius and centimeters).
 * The assumption is that all WetherRecords are in Imperial units to start. (Fahrenheit and inches)
 * Use precision of three significant figures (aka, x.xx, .yyy, ttt0)
 */

void makeMetric( WeatherRecord* wr[], int numRecords ){

  // Code to make all wr's have metric units!
  /////// TAKE THIS OUT; IT'S THE ANSWER////////
  int i = 0;
  for(i=0; i < numRecords; i++ ){
    wr[i]->rainfall *= 2.54;
    wr[i]->temp = (wr[i]->temp-32)*(((double)5)/9);
  }
  //////////////////////////////////////////////

}

/**
 * This function adjusts numRecords worth WeatherRecords in wr so that each entry is recorded in imperial units (Fahrenheit and inches)
 * The assumption is that all WetherRecords are in metric units to start. (Celsius and centimeters).
 * Use precision of three significant figures (aka, x.xx, .yyy, ttt0)
 */

void makeImperial( WeatherRecord* wr[], int numRecords ){

  // Code to make all wr's have metric units!
  /////// TAKE THIS OUT; IT'S THE ANSWER////////
  int i = 0;
  for(i=0; i < numRecords; i++){
    wr[i]->rainfall *= 1/2.54;
    wr[i]->temp = 32+(((double)9)/5)*wr[i]->temp;
  }
  //////////////////////////////////////////////

}
