/*
 * This file contains several functions, each of which has
 * another function for testing it (e.g. swap() and swapTest()).
 * Supplied: 
 *    - main(), which calls all the test functions
 *    - all the test functions
 *    - swap()
 * To be completed:
 *    - rotate()
 *    - pointerToMax()
 *    - pointerToVowel()
 *    - initWeatherRecord()
 *    - copyWeatherRecord()
 * Look at the test functions to see how the functions to be
 * completed should behave.
 */

typedef struct {
	double temp;
	double rainfall;
} WeatherRecord;

void swap(int *one, int *two);
int  swapTest();

void rotate(double *one, double *two, double *three);
int  rotateTest();

int * pointerToMax(int *p1, int *p2);
int pointerToMaxTest();

char * pointerToVowel(char *x, char *y, char *z, char *w);

void initWeatherRecord(WeatherRecord * rec);
void copyWeatherRecord(WeatherRecord * to, WeatherRecord * from);

char* lastWord(char* string);

#ifndef TEST_1XX
int main(int argc, char* argv[]){
  int numErrors = 0;
  numErrors += swapTest();
  numErrors += rotateTest();
  numErrors += pointerToMaxTest();
  printf("Number of errors: %d\n", numErrors);
}
#endif

/* swapTest()
 * inputs: none
 * output: number of errors
 * Tests swap().
 */
int swapTest(){
  int x = 3;
  int y = 5;
  swap(&x, &y);
  if (x == 5 &&  y == 3)
    return 0;
  else
    return 1;
}


/* swap()
 * inputs: 2 integer pointers
 * output: none
 * action: swaps the integers whose addresses are passed as arguments
 */
void swap(int *one, int *two){
  int temp;
  temp = *one;
  *one = *two;
  *two = temp;
}

/* rotateTest()
 * inputs: none
 * output: number of errors
 * Tests rotate().
 */
int rotateTest(){
  double one = 10.5;
  double two = 100.5;
  double three = 1000.5;
  rotate(&one, &two, &three);
  if (one == 1000.5 && two == 10.5 && three == 100.5)
    return 0;
  else 
    return 1;
}

/* rotate()
 * inputs: 3 double pointers
 * output: none
 * action: rotates the numbers to the right; the
 *         rightmost one becomes the first one.
 */
// WRITE THIS FUNCTION


// Tests pointertoMax(). Returns 0 for success, 1 for failure.
int pointerToMaxTest(){
  int x=10, y=20;
  int *maxptr;
  int errors= 0;
  maxptr = pointerToMax(&x, &y);
  if (maxptr != &y)
    errors++;
  x = 200;
  y = 100;
  maxptr = pointerToMax(&x, &y);
  errors += (maxptr == &x ? 0 : 1);
  return errors;
}

/* pointerToMax()
 * input: 2 integer pointers
 * output: pointer to the larger of the two integers
 *         or the first if they are equal  
 */
// WRITE THIS FUNCTION

/* You are encouraged but not required to write
 * test functions for the following.
 */

/* pointerToVowel()
 * input: four pointers to chars
 * output: pointer to the first vowel (aeiouy), or NULL
 * Feel free to use the string library (see `man string`),
 * though it's not required/essential.
 */
// WRITE THIS FUNCTION

/* initWeatherRecord()
 * Initialize a WeatherRecord, setting rainfall and temp to zero.
 * input: pointer to a WeatherRecord
 * output: none
 * To access members of a pointer-to-struct, use *(structPointer).field
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

