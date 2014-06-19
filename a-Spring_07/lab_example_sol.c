// Luke's Small example progam
/*
Assignment: In the area labeled "INSERT CODE HERE", write a if-else chain to do one of the following
	based on the value of inputNumber:
	
	Any Number < 0: have the computer print 'You shouldn't be so negative'
	0: have the computer print 'Chuck Norris Can Divide By Zero'
	1: have the computer print 'He is ... the one'
	2: have the computer print 'The name of the program is <print program name>'
	3: have the computer print 'There are <insert argument count> arguments'
	Any Other Number: have the computer print 'I CAN'T COUNT THAT HIGH!'

	TEST COMMAND LINE EXAMPLE:
	
	lcheng@bash#> ./testprogram 0
	Chuck Norris Can Divide By Zero
	
	HINT: Remember, the name of the program is passed as an argument
	DOUBLE HINT: To compile the program, use:
		gcc -o (program name) (source file name)

*/

#include <stdio.h> 

int main(int argc, char * argv[]){
  int inputNumber;
  
  // Return error if no arguments run with program
  if(argc < 2){
	printf("You didn't add a argument\n");
	return -1;
  }
  
  // Get integer value of first argument
  inputNumber = atoi(argv[1]);
  
  // **** INSERT CODE HERE ****
  
  if(inputNumber < 0){
	printf("You shouldn't be so negative\n");
  }
  else if(inputNumber == 0){
	printf("Chuck Norris Can Divide By Zero\n");
  }
  else if(inputNumber == 1){
	printf("He is ... the one\n");
  }
  else if(inputNumber == 2){
	printf("The name of the program is %s\n", argv[0]);
  }
  else if(inputNumber == 3){
	printf("There are %d arguments\n", argc);
  }
  else{
	printf("I CAN'T COUNT THAT HIGH!\n");
  }
  
  // **** END CODE ****
  
  return 0;
}
