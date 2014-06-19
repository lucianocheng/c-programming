/* Demonstrates an array of structs and pointer to struct.
 * Shows the difference between the "." and the "->" operators.
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct {
  char name[80];
  double average;
  double shoeSize;
} BowlingRecord;        // } BowlingRecord, *BowlingRecordPtr;

int main(){
  BowlingRecord people[2];

  strcpy(people[0].name, "sam");
  people[0].average = 180;
  people[0].shoeSize = 8.5;

  strcpy(people[1].name, "max");
  people[1].average = 50;
  people[1].shoeSize = 12;

  printf("Printing array using the '.' operator:\n");
  int i;
  for (i = 0; i < 2; i++)
    printf("name: %s, average: %.2f, shoe size %.2f\n",
	   people[i].name, people[i].average, people[i].shoeSize);

  /*
  printf("\nPrinting array using the -> operator:\n");
  BowlingRecord *bp;      //   BowlingRecordPtr bp;
  bp = people;
  for (i = 0; i < 2; i++, bp++)
    printf("name: %s, average: %.2f, shoe size %.2f\n",
	   bp->name, bp->average, bp->shoeSize);
  */
}

