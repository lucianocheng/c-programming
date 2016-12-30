
#include <stdlib.h>
#include <stdio.h>

struct bowlingRecord {
  char name[80];
  double average;
  double shoeSize;
};

void printBowlingRecord(struct bowlingRecord br);

int main(){
  // Create a struct variable called person1; initialize it; print it
  struct bowlingRecord person1;

  strcpy(person1.name, "sam");
  person1.average = 180;
  person1.shoeSize = 8.5;

  printf("person1: name: %s, average: %.2f, shoe size: %.2f\n", 
	 person1.name, person1.average, person1.shoeSize);

  // Create a struct variable called person2; copy person1's data in to it
  // using the assignment operator; print it
  struct bowlingRecord person2;
  person2 = person1;
  printf("person2 after 'person2 = person1':" );
  printBowlingRecord(person2);

  // Change person2's data. See that it just changes person2, not person1.
  strcpy(person2.name, "jo");
  person2.average = 90;
  person2.shoeSize = 10;
  printf("\nAfter changing person2:\n" );
  printf("person1: " );
  printBowlingRecord(person1);
  printf("person2: " );
  printBowlingRecord(person2);

}

void printBowlingRecord(struct bowlingRecord br){
  printf("name: %s, average: %.2f, shoe size: %.2f\n", 
	 br.name, br.average, br.shoeSize);
}
