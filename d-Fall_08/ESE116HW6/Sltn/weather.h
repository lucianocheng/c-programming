/**
 * weather.h
 *
 * @author upenn ese116 staff
 * @version 2008 April 3
 */

#ifndef WEATHER_H
#define WEATHER_H

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

void makeMetric(WeatherRecord**,int);
void makeImperial(WeatherRecord**,int);
void addOffset(WeatherRecord**,double,double,int);

int getOffset(double*,double*);

#endif
