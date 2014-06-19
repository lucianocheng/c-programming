/* The strings program
   This program reads data from STDIN.  It parses the data into words,
   eliminates duplicate words, and prints out the words and their length
   to STDOUT.
   
   Compile line: gcc -Wall -o strings strings.c
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
  The main function of strings.c should do the following:
  1. Call getWord repeatedly until getWord returns 0
  2. For each new word that main pulls from STDIN using getWord, main should
     compare the new word with the word it pulled right before it.  

     If the new word and the previous word are not the same, main should 
     find the length of the new word, and call printWord using the new word 
     and it's length as parameters.
     
     If the new word and the previous word are the same, main should not call
     printWord.
  3. When getWord returns 0, main should return EXIT_SUCCESS

  NOTE: When calling getWord, you must pass the size of the array you declared.
        For our purposes, a size of 256 should be sufficient.
*/
int main(int argc, char* argv[]){
  
  return EXIT_SUCCESS;
}

/*
  The getWord function of strings should do the following
  1. Call getchar() until it returns a character that isn't a space or an enter
     (to get rid of multiple spaces between words)
  2. If getchar returns EOF, return 0;
  2. Use getchar() to get characters from STDIN until a space, enter, or EOF is
     reached or until the number of characters reaches size - 1.  Store these
     characters in newString.  Add a null character ('\0') at the end of newString.
  3. If the number of characters reached size - 1, call getchar() until a space,
     enter, or EOF is reached.
  4. If no EOF was reached, return 1;
  
  NOTE: The character for ENTER is '\n'
*/
int getWord(char newString[], int size){
  
  return 1;
}

/*
  The printWord function printf's (prints to STDOUT) the word and length of the word
*/
int printWord(char printString[], int length){
  printf("'%s', Length: %d\n", printString, length);
}
