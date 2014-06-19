/* Demo of the pointer operators & and *. */
#include <stdio.h>
#include <stdlib.h>

int main(){
  int x = 5;
  int y = 10;
  int z = 15;
  printf("x is %d, &x is %d \n", x, &x);
  printf("y is %d, &y is %u \n", y, &y);
  printf("z is %d, &z is %u \n", z, &z);

 
  // The "type" of p is "pointer to int", or "int pointer", or "int *",
  // which means it is intended to hold the address of an int.
  int *p;
  printf("\nExecuting: p = &x;\n");
  p = &x;
  // We're using %u, which means 'unsigned', to print addresses so that
  // when they're printed they all show up as positive numbers. You can
  // replace the %u with %d; then values printed may be negative. On
  // many systems the highest bit of an int is a flag that is 0 if positive
  // and 1 if negative.
  printf("p is %u, &p is %u, *p is %d  \n", p, &p, *p);  

  printf("\nExecuting: p = &y;\n");
  p = &y;
  printf("p is %u, &p is %u, *p is %d  \n", p, &p, *p);  

  printf("\nExecuting: p = 10; // C isn't typesafe here; the compiler MAY warn.\n");
  p = 10; // A common mistake. p's type is "int *" so it should only be assigned
          // an address of an int, but C allows an int to be assigned to it -
          // neither a compiler nor a runtime error occurs. C is not "typesafe" here.
  printf("p is %u, &p is %u, *p is %d  \n", p, &p, *p);  
}
