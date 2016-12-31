/*
 * This file contains several incomplete functions that use pointers.
 * Your job is to complete the functions according to the spec provided
 * in the comments. You are encouraged but not required to write test
 * functions to test your code. (See pointers1.c for examples of test
 * functions.)
 *
 * To be completed:
 *    1. pointerToVowel()
 *    2. initWeatherRecord()
 *    3. copyWeatherRecord()
 *    4. lastWord()
 */

typedef struct {
	double temp;
	double rainfall;
} WeatherRecord;

char * pointerToVowel(char *x, char *y, char *z, char *w);
void initWeatherRecord(WeatherRecord * rec);
void copyWeatherRecord(WeatherRecord * to, WeatherRecord * from);
char* lastWord(char* string);

#ifndef TEST_1XX
int main(int argc, char* argv[]){
  int numErrors = 0;

  printf("Number of errors: %d\n", numErrors);
}
#endif


/* You are encouraged but not required to write
 * test functions for the following.
 */

/* pointerToVowel()
 * input: four pointers to lowercase chars
 * output: pointer to the first vowel (aeiouy), or NULL
 * Feel free to use the string library (see `man string`),
 * though it's not required/essential.
 */
// WRITE THIS FUNCTION

/* initWeatherRecord()
 * Initialize a WeatherRecord, setting rainfall and temp to zero.
 * input: pointer to a WeatherRecord
 * output: none
 * To access members of a pointer-to-struct, use (*structPointer).field
 * (dereference the struct-pointer, then access the field desired).
 */
// WRITE THIS FUNCTION

/* copyWeatherRecord()
 * Copy from the 'from' weather record to the 'to' weather record
 * input: two pointers to weather records
 * output: none
 */
// WRITE THIS FUNCTION

/* lastWord()
 * input: 1 string (char pointer)
 * output: string (char pointer) of the last word
 *	in: "hello, world"	out: "world"
 *	in: "welcome to lab"	out: "lab"
 *	in: "ese116"		out: "ese116"
 *	in: "   "		out: ""
 * Since strings are just char pointers, you can accomplish
 * this by returning a pointer to the character after the last space.
 * That is, walk backwards through the string until you hit a space,
 * and then return a pointer to the next-higher-index char.
 * For now, use this syntax: &string[x]
 * which returns a pointer to the character at index x in the string.
 */
// WRITE THIS FUNCTION

