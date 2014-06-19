#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * nChars(int, char);
void nCharsTest();
void * grow(void *, int);
void growTest();

#ifndef TEST_1xx
int main(int argc, char* args[]){
  nCharsTest();
  growTest();
}
#endif

char * nChars(int n, char c){
  char *p; 
  if (n < 1){return NULL;}

  p = (char *)calloc(n,sizeof(char));
  if (p == NULL) {return NULL;}

  int i;
  for (i = 0; i < n; i++){
    *(p+i) = c;
  }

   return p;
}

void nCharsTest(){

  char *q = nChars(0,'a');
  
  // Testing for NULL input
  if (q != NULL){
    printf("n less than one, but does not return NULL\n");
    free(q);
    return;
  }

  // Testing for improper memory allocation
char *p = nChars(10,'a');
  int i;
  if (p != NULL){
    for (i = 0; i < 10; i++){
      if (*(p+i) != 'a'){
	printf("Memory allocation failed, but does not return NULL\n");
	free(p);
	return;
      }
    }
  }

  printf("All tests passed1\n");
 
  free(p);
  free(q);
  return;
  
}

void * grow(void *source, int sizeOfSource){
  
  if (source == NULL){
    return NULL;}
  
  void *p = malloc(2*sizeOfSource);
  if (p == NULL){
    return NULL;}

  p = memcpy(p,source,sizeOfSource);

  free(source);
  
  return p;
  
}


void growTest(){
  

  // Testing a NULL Input
  int*g = NULL;
  void *x = grow(g,sizeof(int));
  if (x != NULL){
    printf("Original Source is Null, but does not return NULL\n");
    free(x);
    return;
  }

  // Testing the memory allocation for chars
   char *c = (char*)calloc(8,sizeof(char));
  if (c == NULL){return;}

  char *y = grow(c,(8*sizeof(char)));
  if (y != NULL){
    int i;
    for (i = 0; i < 16; i++){
      if (*(y+1) != 0){
	printf("Memory allocation failed, but does not return NULL\n");
	free(y);
	return;
      }
    }
  }

  // Just copying, printing and testing proper working
    int *p = (int*)malloc(2*sizeof(int));
    if (p == NULL){return;}

    *p = 13;
    *(p+1) = 15;

    int *q = grow(p,(2*sizeof(int)));
    
    printf("%d,%d,%d,%d\n", *q, *(q+1), *(q+2), *(q+3));

    printf("All tests passed2\n");
	
    free(x);
    free(y);	  
    free(c);
    free(p);
    free(q);

  
 return;
    
}
  

