#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "testPointerToVowel.h"
#include "cgrader.h"
#include "pointers.h"

extern char * pointerToVowel(char *, char *, char *, char *);

void testPointerToVowel(char x, char y, char z, char w, int index){
  
  char* passPointer;
  char message[100];

  if(index == 0) passPointer = &x;
  else if(index == 1) passPointer = &y;
  else if(index == 2) passPointer = &z;
  else if(index == 3) passPointer = &w;
  else passPointer = NULL;
  
  sprintf(message, "passing %c, %c, %c, %c", x, y, z, w);

  assert_equals_pointer(message, passPointer, pointerToVowel(&x, &y, &z, &w));
}

// Pointer to Vowel = 20 PTS
void testPointerToVowel_x(){
  testPointerToVowel('a', 'b', 't', 'r', 0);
  testPointerToVowel('e', 'h', 'a', 'z', 0);
  testPointerToVowel('i', 'u', 'b', 'z', 0);
  testPointerToVowel('o', 'z', 'i', 'y', 0);
  testPointerToVowel('u', 'u', 'i', 'r', 0);
  testPointerToVowel('y', 'i', 't', 'u', 0);
}

void testPointerToVowel_y(){
  testPointerToVowel('z', 'a', 't', 'r', 1);
  testPointerToVowel('x', 'e', 'a', 'z', 1);
  testPointerToVowel('g', 'i', 'b', 'z', 1);
  testPointerToVowel('g', 'o', 'i', 'y', 1);
  testPointerToVowel('s', 'u', 'i', 'r', 1);
  testPointerToVowel('t', 'y', 't', 'u', 1);
}

void testPointerToVowel_z(){
  testPointerToVowel('z', 'z', 'a', 'r', 2);
  testPointerToVowel('x', 'x', 'e', 'z', 2);
  testPointerToVowel('g', 'z', 'i', 'z', 2);
  testPointerToVowel('g', 'z', 'o', 'y', 2);
  testPointerToVowel('s', 'z', 'u', 'r', 2);
  testPointerToVowel('t', 'z', 'y', 'u', 2);
}

void testPointerToVowel_w(){
  testPointerToVowel('z', 'z', 'z', 'a', 3);
  testPointerToVowel('x', 'n', 'n', 'e', 3);
  testPointerToVowel('g', 'n', 'h', 'i', 3);
  testPointerToVowel('g', 'h', 'h', 'o', 3);
  testPointerToVowel('s', 'h', 'h', 'u', 3);
  testPointerToVowel('t', 'h', 'h', 'y', 3);
}

void testPointerToVowel_err(){
  testPointerToVowel('z', 'z', 't', 'z', -1);
  testPointerToVowel('x', 'z', 'r', 't', -1);
  testPointerToVowel('g', 'z', 't', 'm', -1);
  testPointerToVowel('g', 'z', 't', 't', -1);
  testPointerToVowel('g', 'z', 'n', 't', -1);
  testPointerToVowel('g', 'z', 't', 'x', -1);
}

