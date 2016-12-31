#include <stdio.h>
#include <stdlib.h>

int main(void){
  int x = 3;
  int y = 5;
  int *p = &x;

  printf("x is %d, y is %d, *p is %d\n", x, y, *p);
  printf("&x is %u, &y is %u, p is %u\n", &x, &y, p);
  return EXIT_SUCCESS;
}
