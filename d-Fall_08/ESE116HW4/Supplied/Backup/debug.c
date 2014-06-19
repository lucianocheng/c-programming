#include <stdio.h>
#include <stdlib.h>

void doubleIt(int x);

typedef struct {
  double temp;
  double rainfall;
} WeatherRecord;

void foo1(WeatherRecord wr);

int main(){
  // Problem 1: 
  // Given an int num that equals 5, make pointer ptr point to it. 
  // Change x's value to 10 using the pointer.
  int num = 5;
  int *ptr = num;
  *ptr = 10;
  printf("Problem 1: num is %d (Should print 10)\n", num); 

  // Problem 2:
  // Given a double d1 whose value is 5, make pointer p point to it.
  // Print the value of d1 by using the pointer.
  double d1 = 5;
  double *p = &d1;
  printf("Problem 2: The double that p points to is %.2f (Should print 5.00)\n", p);


  // Problem 3: Given 2 integer pointers, p1 pointing to x, p2 pointing to y.
  int x = 5;
  int y = 10;
  int *p1 = &x;
  int *p2 = &y;
  // Now make p2 point to x and p1 point to y, without touching x or y.
  p1 = p2;
  p2 = p1;
  printf("Problem 3: %d %d (Should print 10 5)\n", *p1, *p2); 

  // Problem 4: We want to write a function that doubles the variable num. 
  //            Adjust all the code necessary to accomplish this task. The
  //            return type of doubleIt() should remain void.
  int val = 12;
  doubleIt(val);  
  printf("Problem 4: After calling doubleIt(), val is %d (Should print 24)\n", val);


  /* Problem 5:
   * Believe it or not, when a struct is passed to a C function, a COPY of the
   * ENIRE structure is passed to it (put on the stack). Likewise when a C
   * function returns a struct. This is very different from the way that Java 
   * handles the passing of objects to a method (and returning them), where
   * only a reference is passed, not a copy of the object. Note that copying structs
   * onto and off of the stack takes a lot of time and space!
   *
   * We supply foo1() which takes a WeatherRecord struct. We supply it to
   * show you that it gets a copy of the struct passed to it. When foo1()
   * doubles the temp and rainfall, it just changes the copy, not the original
   * struct defined in main()
   * 
   * You'll write foo2() which accepts a struct pointer, which can (and should)
   * change the struct defined in main().
   */

  WeatherRecord w, w2;
  w.temp = 70;
  w.rainfall = 1;
  foo1(w);
  printf("Problem 5: After foo1()\n");
  printf("w.temp = %.1f, w.rainfall = %.1f (Should print 70.0 1.0)\n", 
                                           w.temp, w.rainfall);
  /* TODO: 
   *  Write foo2() which should  a struct pointer and changes the original 
   *  WeatherRecord. 
   */
  // TODO: Uncomment the line below.
  // foo2(&w);
  printf("Problem 5: After foo2()\n");
  printf("w.temp = %.1f, w.rainfall = %.1f (Should print 140.0 2.0)\n", 
                                            w.temp, w.rainfall);
  return EXIT_SUCCESS;
}


void doubleIt(int x){
  x = 2 * x;
}


// This function gets a COPY of the structure passed to it.
void foo1(WeatherRecord wr){
  wr.temp *= 2;
  wr.rainfall *= 2;
  printf("In foo(): wr.temp = %.1f, wr.rainfall = %.1f (Should print 140.0 2.0)\n", 
                                                       wr.temp, wr.rainfall);
}

/* Write foo2() here. Its parameter should be a pointer to a Weather record.
 * If its parameter is called p, then use this notation:
 *         (*p).temp =
 *         (*p).rainfall =
 */

