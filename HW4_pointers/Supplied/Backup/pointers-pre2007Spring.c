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
 * Look at the test functions to see how the functions to be
 * completed should behave.
 */
void swap(int *one, int *two);
int  swapTest();

void rotate(double *one, double *two, double *three);
int  rotateTest();

int * pointerToMax(int *p1, int *p2);
int pointerToMaxTest();

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

