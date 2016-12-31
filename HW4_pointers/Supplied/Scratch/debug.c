
int main(){
  // Problem 1: 
  // Given an int num that equals 5, make pointer ptr point to it. 
  // Change x's value to 10 using the pointer.
  int num = 5;
  int *ptr = num;
  *ptr = 10;
  printf("num is %d\n", num); // should print 10

  // Problem 2:
  // Given a double d1 whose value is 5, make pointer p point to it.
  // Print the value of d1 by using the pointer.
  double d1 = 5;
  double *p = &d1;
  printf("Problem 1: The double that p points to is %f\n", p); // should print 5.0


  // Problem 3: Given 2 integer pointers, p1 pointing to x, p2 pointing to y.
  int x = 5;
  int y = 10;
  int *p1 = &x;
  int *p2 = &y;
  // ... now make p2 point to x and p1 point to y, without touching x or y.
  // Correct the code below:
  p1 = p2;
  p2 = p1;
  printf("Problem 2: %d %d\n", *p1, *p2); // should print "10 5"

}
