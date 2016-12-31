/**
 * weather.h
 *
 * @author Mark Fickett
 * @author Jean Griffin
 * @version 2007 Feb 15
 */

#ifndef WEATHER_H
#define WEATHER_H

#ifdef DEBUG
#undef DEBUG
#endif

#define FAULTY_DATA -9999
#define MAX_PROMPTS 3
#define MAX_RECORDS 10
#define TRUE  1
#define FALSE 0

/**
 * A weather record, which holds a rainfall amount and a temperature.
 * It may contain data for a day, month, or some other time period. 
 */
typedef struct {
	double rainfall;
	double temp;
} WeatherRecord;

int promptUserForChoice();
int getWeatherRecord(WeatherRecord[], int);
WeatherRecord computeStats(WeatherRecord[], int);
int isLegalChoice(int, char[]);
int flush();
void printWeatherRecords(WeatherRecord[], int);

#endif
