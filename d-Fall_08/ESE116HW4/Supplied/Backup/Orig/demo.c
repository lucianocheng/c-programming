
int main(){
  int x = 5;
  int y = 10;
  int z = 15;
  printf("x is %d,  &x is %d \n", x, &x);
  printf("y is %d, &y is %u \n", y, &y);
  printf("z is %d, &z is %u \n", z, &z);

 
  // The "type" of p is "pointer to int", of "int pointer", or "int *",
  // which means it can hold the address of an int.
  int *p;
  printf("\nExecuting: p = &x;\n");
  p = &x;
  printf("p is %u, &p is %u, *p is %d  \n", p, &p, *p);  

  printf("\nExecuting: p = &y;\n");
  p = &y;
  printf("p is %u, &p is %u, *p is %d  \n", p, &p, *p);  

  // Uncomment the lines below to see what happens
  p = 10; // mistake;
  printf("p is %u, &p is %u, *p is %d  \n", p, &p, *p);  

  /*
  printf("\n\n");
  printf("Experiments with the sizeof operator which reports #bytes:\n");
  printf("sizeof(int) is %d\n", sizeof(int));
  printf("sizeof(char) is %d\n", sizeof(char));
  printf("sizeof(float) is %d\n", sizeof(float));
  printf("sizeof(double) is %d\n", sizeof(double));
  printf("\n");
  printf("sizeof(int *) is %d\n", sizeof(int *));
  printf("sizeof(char *) is %d\n", sizeof(char *));
  printf("sizeof(float *) is %d\n", sizeof(float *));
  printf("sizeof(double *) is %d\n", sizeof(double *));
  printf("\n");
  printf("sizeof(int **) is %d\n", sizeof(int **));
*/

}
