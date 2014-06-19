#include <stdio.h>
#include <stdlib.h>

int findA(char[]);

int main(int argc, char* argv[]){
  char oldString[] = {'H', 'e', 'l', 'l', 'o', '\n'};









 






  printf("Calling findNull, will seg fault now\n");
  findA(oldString); 

  printf("Program complete\n");

  return EXIT_SUCCESS;
}

int findA(char newArray[]){
  int i = 0;
  while(newArray[i] != 'A' || newArray[i+1] != 'A'){  
    i++;
  }
  printf("Found at: %d\n", i);
  return i;
}

