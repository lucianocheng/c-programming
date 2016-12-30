/**
 * Test ESE 116 HW 02, Spring 2007
 *
 * @version 2007 Nov 07
 * @author Luciano Cheng
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
 *  Note:  There is a "memory leak" in this code where
 *         the packet tests don't free the packets they
 *         test with.  For some reason, within the testing
 *         environment, freeing does not work properly. Might
 *         have something to do with contexts or something
 *  EXTRA NOTES FOR THIS HW:
 *
 *  (-5) for use of malloc
 *
 *  (-10) for minor (< 3 errors) modifications required to compile
 *
 *  (-20) for major (> 3 errors) modifications required to compile
 *
 *  (-10) for minor (< 3 errors) modifications to the code to format output
 *
 *  (-20) for major (>3 errors) modifications to the code to format output
 */

// general homework tester stuff

// These #defines don't seem to take effect in the right scope,
// so moved to the Makefile.hw1 definition of the gcc call
// #define TEST_1xx
// #define TEST_1XX
// #define TESTER_1XX

#include "ctester.h"
#include <stdio.h>
#include <stdlib.h>

// specific to this homework
#include "packets.h"
#include " "

#define TRUE 1
#define FALSE 0

// Function declarations from hws
char * pointerToVowel(char *, char *, char *, char *);
char * lastWord(char *);
void   reverse(char *);

// tester functions' headers
// Pointer to Vowel = 20 PTS
void testPointerToVowel_x();
void testPointerToVowel_y();
void testPointerToVowel_z();
void testPointerToVowel_w();
void testPointerToVowel_err();

// Pointer to last word = 20 PTS
void testPointerToLastWord_oneWord();
void testPointerToLastWord_twoWord();
void testPointerToLastWord_threeWord();
void testPointerToLastWord_spaceAndEmpty();
void testPointerToLastWord_null();

// Reverse strings = 18 PTS
// Used Pointer notation = 2 PTS
void testReverse_smallString();
void testReverse_longString();
void testReverse_oddLetters();
void testReverse_evenLetters();
void testReverse_nullAndEmpty();

// Pack Data = 20 PTS
void testPackData_messageNumber();
void testPackData_indexNumber();
void testPackData_moreFlag();
void testPackData_dataSize();
void testPackData_oneChar();
void testPackData_12Char();
void testPackData_25Char();
void testPackData_error();

// Unpack Data = 20 PTS
void testUnPackData_160CharForwardsData();
void testUnPackData_160CharForwardsSize();
void testUnPackData_100CharRandomData();
void testUnPackData_100CharRandomSize();
void testUnPackData_12CharForwardsData();
void testUnPackData_12CharForwardsSize();
void testUnPackData_25CharRandomData();
void testUnPackData_25CharRandomSize();
void testUnPackData_1CharForwardsData();
void testUnPackData_1CharForwardsSize();

void testCurve();

// Get empty packet
char** getEmptyPackets(int);
int makePackets(char[], int, char*[], int);
void testUnpackDataSize(int, int);
void testUnpackDataChars(int, int);
void testPointerToVowel(char, char, char, char, int);

// tester main
int main(int argc, char * argv[]) {
	PROBLEM * prob1 = add_new_problem("Pointer to Vowel", 1);
	PROBLEM * prob2 = add_new_problem("Pointer to Last Word", 2);
	PROBLEM * prob3 = add_new_problem("Reverse Strings", 3);
	PROBLEM * prob4 = add_new_problem("Pack Data", 4);
	PROBLEM * prob5 = add_new_problem("Unpack Data", 5);
        PROBLEM * prob6 = add_new_problem("Curve", 6);

	// Pointer to Vowel = 20 PTS
	add_new_test(prob1, "testPointerToVowel_x", 4/2, 
		&testPointerToVowel_x);
	add_new_test(prob1, "testPointerToVowel_y", 4/2, 
		&testPointerToVowel_y);
	add_new_test(prob1, "testPointerToVowel_z", 4/2, 
		&testPointerToVowel_z);
	add_new_test(prob1, "testPointerToVowel_w", 4/2, 
		&testPointerToVowel_w);
	add_new_test(prob1, "testPointerToVowel_err", 4/2,
		&testPointerToVowel_err);

	// Last Word = 20 PTS
	add_new_test(prob2, "testPointerToLastWord_oneWord", 4/2,
		&testPointerToLastWord_oneWord);
	add_new_test(prob2, "testPointerToLastWord_twoWord", 4/2,
		&testPointerToLastWord_twoWord);
	add_new_test(prob2, "testPointerToLastWord_threeWord", 4/2,
		&testPointerToLastWord_threeWord);
	add_new_test(prob2, "testPointerToLastWord_spaceAndEmpty", 4/2,
		&testPointerToLastWord_spaceAndEmpty);
	add_new_test(prob2, "testPointerToLastWord_null", 4/2,
		&testPointerToLastWord_null);

	add_new_test(prob3, "testReverse_smallString", 4/2,
		&testReverse_smallString);
	add_new_test(prob3, "testReverse_longString", 4/2,
		&testReverse_longString);
	add_new_test(prob3, "testReverse_oddLetters", 4/2,
		&testReverse_oddLetters);
	add_new_test(prob3, "testReverse_evenLetters", 4/2,
		&testReverse_evenLetters);
	add_new_test(prob3, "testReverse_nullAndEmpty", 4/2,
		&testReverse_nullAndEmpty);

	add_manual_grade(prob3, "used pointer notation", 2/2, FALSE);

        
	// Pack Data = 20 PTS
	add_new_test(prob4, "testPackData_messageNumber", 2/2,
		&testPackData_messageNumber);
	add_new_test(prob4, "testPackData_indexNumber", 2/2,
		&testPackData_indexNumber);
	add_new_test(prob4, "testPackData_nextFlag", 2/2,
		&testPackData_moreFlag);
	add_new_test(prob4, "testPackData_dataSize", 2/2,
		&testPackData_dataSize);
	add_new_test(prob4, "testPackData_oneChar", 4/2,
		&testPackData_oneChar);
	add_new_test(prob4, "testPackData_12Char", 2/2,
		&testPackData_12Char);
	add_new_test(prob4, "testPackData_25Char", 2/2,
		&testPackData_25Char);
	add_new_test(prob4, "testPackData_error", 4/2,
		&testPackData_error);
	
	// Unpack Data = 20 PTS
	add_new_test(prob5, "testUnPackData_160CharForwardsData", 2/2, 
		testUnPackData_160CharForwardsData);
	add_new_test(prob5, "testUnPackData_160CharForwardsSize", 2/2,
		testUnPackData_160CharForwardsSize);
	add_new_test(prob5, "testUnPackData_100CharRandomData", 2/2, 
		testUnPackData_100CharRandomData);
	add_new_test(prob5, "testUnPackData_100CharRandomSize", 2/2,
		testUnPackData_100CharRandomSize);
	add_new_test(prob5, "testUnPackData_12CharForwardsData", 2/2, 
		testUnPackData_12CharForwardsData);
	add_new_test(prob5, "testUnPackData_12CharForwardsSize", 2/2, 
		testUnPackData_12CharForwardsSize);
	add_new_test(prob5, "testUnPackData_25CharRandomData", 2/2, 
		testUnPackData_25CharRandomData);
	add_new_test(prob5, "testUnPackData_25CharRandomSize", 2/2, 
		testUnPackData_25CharRandomSize);
	add_new_test(prob5, "testUnPackData_1CharForwardsData", 2/2, 
		testUnPackData_1CharForwardsData);
	add_new_test(prob5, "testUnPackData_1CharForwardsSize", 2/2, 
		testUnPackData_1CharForwardsSize);

        add_new_test(prob6, "curve", 49, testCurve);

	run_all_tests(argc, argv);
	clean_up();
	return 0;
}

/**
 * Setup tester labels
 */
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11602; }

char** getEmptyPackets(int size){
  char** newPackets;
  int i;

  newPackets = (char**)malloc(sizeof(char*) * size);
  for(i = 0; i < size; i++){
    newPackets[i] = (char*)malloc(sizeof(char) * 12);
  }
  
  return newPackets;
}

int makePackets(char data[], int dataSize, char* packetArray[], int randPackets){
  int packetIndex = 0;
  int j = 0, i = 0;
  int msgNumber = getMsgNumber();
  int dataLeft = dataSize;
  char* tempPacket;

  int packetsNeeded = (dataSize / 12) + ((dataSize % 12 == 0) ? 0 : 1);

  if(dataSize >= 256) return -1;

  for(packetIndex = 0; packetIndex < packetsNeeded; packetIndex++){

    packetArray[packetIndex][0] = (char)msgNumber;
    packetArray[packetIndex][1] = (char)packetIndex;
    packetArray[packetIndex][2] = (char)((packetIndex == packetsNeeded-1) ? FALSE : TRUE);
    packetArray[packetIndex][3] = (char)((packetIndex == packetsNeeded-1) ? (dataSize - (packetsNeeded-1)*12) : 12);

    for(j = 0; j < 12 && j < dataLeft; j++){
      packetArray[packetIndex][j + 4] = (char)data[((packetIndex)*12) + j];
    }
    dataLeft-=j;
  }
  
  // Randomize if randPackets == 1;
  if(randPackets){
    srand(111111);
    for(i = 0; i < packetsNeeded; i++){
      for(j = 0; j < packetsNeeded; j++){
        if(rand() % 2 == 0){
          tempPacket = packetArray[i];
          packetArray[i] = packetArray[j];
          packetArray[j] = tempPacket;
        }
      }
    }
  }

  return packetsNeeded;
}

void testUnpackDataChars(int size, int randomized){
  char dataSent[256];
  char dataReceived[256];
  int i = 0;
  int notEqualAt = -1;

  for(i = 0; i < size; i++){
    dataSent[i] = (char)i;
  }

  packetArray = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  packetsSent = makePackets(dataSent, size, packetArray, randomized);
  packetsReceived = 0;

  unpackData(dataReceived);

  for(i = 0; i < size && notEqualAt == -1; i++){
    if(dataSent[i] != dataReceived[i]) notEqualAt = i;
  }

  assert_equals_int("Data != received equal at (should be -1)", -1, notEqualAt);
}

void testUnpackDataSize(int size, int randomized){
  char dataSent[256];
  char dataReceived[256];
  char message[30];
  int result = 0;
  int i = 0;
  
  for(i = 0; i < size; i++){
    dataSent[i] = (char)i;
  }

  packetArray = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  packetsSent = makePackets(dataSent, size, packetArray, randomized);
  packetsReceived = 0;

  result = unpackData(dataReceived);

  sprintf(message, "Data size should be %d", size);
  assert_equals_int(message, size, result);
}

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

// Pointer to last word = 20 PTS
void testPointerToLastWord_oneWord(){
  char test0[20] = "hello";
  char test1[20] = "goodbye";

  assert_equals_pointer("test 'hello'", &test0[0],
			lastWord(test0));
  assert_equals_pointer("test 'goodbye'", &test1[0],
			lastWord(test1));
}

void testPointerToLastWord_twoWord(){
  char test0[40] = "hello my";
  char test1[40] = "name Luke";

  assert_equals_pointer("test 'hello my'", &test0[6],
			lastWord(test0));
  assert_equals_pointer("test 'name Luke'", &test1[5],
			lastWord(test1));
}

void testPointerToLastWord_threeWord(){
  char test0[40] = "hello my name";
  char test1[40] = "abracadabra is name";

  assert_equals_pointer("test 'hello my name'", &test0[9],
			lastWord(test0));
  assert_equals_pointer("test 'abracadabra is name'", &test1[15],
			lastWord(test1));
}

void testPointerToLastWord_spaceAndEmpty(){
  char test0[30] = "     ";
  char test1[10] = " ";
  char test2[10] = "";

  assert_equals_pointer("test '     '", NULL,
			lastWord(test0));
  assert_equals_pointer("test ' '", NULL,
			lastWord(test1));
  assert_equals_pointer("test ''", NULL,
			lastWord(test2));
}

void testPointerToLastWord_null(){
  char *test = NULL;
  
  assert_equals_pointer("test NULL", NULL,
			lastWord(test));
}

// Reverse strings = 18 PTS
// Used Pointer notation = 2 PTS
void testReverse_smallString(){
  char test0[30] = "the quick brown";
  char test1[30] = "1234!@#$";

  reverse(test0);
  assert_equals_string("test 'the quick brown'", 
		       "nworb kciuq eht", test0);
  reverse(test1);
  assert_equals_string("test '1234!@#$", "$#@!4321",
		       test1);
}

void testReverse_longString(){
  char test0[80] = "abcdefghijklmnopqrstuvwxyz 1234567890";
  char test1[80] = "!@#$%^&*() aabbccddeeffgghhiijjkkllmm";
  
  reverse(test0);
  assert_equals_string("test 'abcdefghijklmnopqrstuvwxyz 1234567890'",
		       "0987654321 zyxwvutsrqponmlkjihgfedcba", test0);

  reverse(test1);
  assert_equals_string("test '!@#$%^&*() aabbccddeeffgghhiijjkkllmm",
		       "mmllkkjjiihhggffeeddccbbaa )(*&^%$#@!", test1);
}

void testReverse_oddLetters(){
  char test0[20] = "a";
  char test1[20] = "abc";
  char test2[20] = "abcde";
  char test3[20] = "abcdefg";

  reverse(test0);
  assert_equals_string("test 'a'", "a", test0);
  
  reverse(test1);
  assert_equals_string("test 'abc'", "cba", test1);

  reverse(test2);
  assert_equals_string("test 'abcde'", "edcba", test2);

  reverse(test3);
  assert_equals_string("test 'abcdefg'", "gfedcba", test3);
}

void testReverse_evenLetters(){
  char test0[20] = "ab";
  char test1[20] = "abcd";
  char test2[20] = "abcdef";
  char test3[20] = "abcdefgh";

  reverse(test0);
  assert_equals_string("test 'ab'", "ba", test0);

  reverse(test1);
  assert_equals_string("test 'abcd'", "dcba", test1);
  
  reverse(test2);
  assert_equals_string("test 'abcdef'", "fedcba", test2);
  
  reverse(test3);
  assert_equals_string("test 'abcdefgh'", "hgfedcba", test3);
}

void testReverse_nullAndEmpty(){
  char test0[20] = "";
  char *test1 = NULL;
  int result;

  reverse(test0);
  result = !strcmp("", test0);
  assert_equals_int("test empty string result", 1, result);

  reverse(test1);
  assert_equals_pointer("test NULL", NULL, test1);
}

// Pack Data = 20 PTS
void testPackData_messageNumber(){
  char data1[] = "abcdefg";
  char data2[] = "efghijk";
  char data3[] = "lmnopqr";
  int dataSize = 7;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  packData(data1, dataSize, newPackets);
  assert_equals_int("test '0'", 0, (int)newPackets[0][0]);

  packData(data2, dataSize, newPackets);
  assert_equals_int("test '1'", 1, (int)newPackets[0][0]);

  packData(data3, dataSize, newPackets);
  assert_equals_int("test '2'", 2, (int)newPackets[0][0]);
}

void testPackData_indexNumber(){
  char data[] = "0123456789ab0123456789ab0123456789ab0123456789ab";
  int dataSize = 48;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  packData(data, dataSize, newPackets);
  assert_equals_int("test index '0'", 0, (int)newPackets[0][1]);
  assert_equals_int("test index '1'", 1, (int)newPackets[1][1]);
  assert_equals_int("test index '2'", 2, (int)newPackets[2][1]);
  assert_equals_int("test index '3'", 3, (int)newPackets[3][1]);
}

void testPackData_moreFlag(){
  char data[] = "0123456789ab0123456789ab0123456789ab0123456789ab";
  int dataSize = 48;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  packData(data, dataSize, newPackets);
  assert_equals_int("test more '1'", 1, (int)newPackets[0][2]);
  assert_equals_int("test more '1'", 1, (int)newPackets[1][2]);
  assert_equals_int("test more '1'", 1, (int)newPackets[2][2]);
  assert_equals_int("test more '0'", 0, (int)newPackets[3][2]);

}

void testPackData_dataSize(){
  char data[] = "0123456789ab0123456789ab012";
  int dataSize = 27;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  packData(data, dataSize, newPackets);
  assert_equals_int("test dataSize '12'", 12, (int)newPackets[0][3]);
  assert_equals_int("test dataSize '12'", 12, (int)newPackets[1][3]);
  assert_equals_int("test dataSize '3'", 3, (int)newPackets[2][3]);

}

void testPackData_oneChar(){
  char data[] = "a";
  int dataSize = 1;
  int result = 0;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  result = packData(data, dataSize, newPackets);
  
  assert_equals_int("test 1 chars (1 pkt used)", 1, result);
  assert_equals_char_array("test data 'a'", data, &newPackets[0][4], 1);
}

void testPackData_12Char(){
  char data[] = "aaaaaaaaaaaa";
  int dataSize = 12;
  int result = 0;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  result = packData(data, dataSize, newPackets);
  assert_equals_int("test 12 chars (1 pkt used)", 1, result);
  assert_equals_char_array("test data 'a'x12", data, &newPackets[0][4], 12);
}

void testPackData_25Char(){
  char data[] = "aaaaaaaaaaaabbbbbbbbbbbbb";
  int dataSize = 25;
  int result = 0;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  result = packData(data, dataSize, newPackets);
  assert_equals_int("test 25 chars (3 pkts used)", 3, result);
  assert_equals_char_array("test data 'a'x12", data, &newPackets[0][4], 12);
  assert_equals_char_array("test data 'b'x12", data+12, &newPackets[1][4], 12);
  assert_equals_char_array("test data 'b'", data+24, &newPackets[2][4], 1);
}

void testPackData_error(){
  char data[300];
  int dataSize = 300;
  int result = 0;
  int i = 0;

  char** newPackets = getEmptyPackets(MAX_AVAILABLE_PACKETS);
  for(i = 0; i < 300; i++){
    data[i] = 'a';
  }

  result = packData(data, dataSize, newPackets);
  assert_equals_int("test error", -1, result);

}

void testUnPackData_160CharForwardsData(){
  testUnpackDataChars(160, FALSE);
}

void testUnPackData_160CharForwardsSize(){
  testUnpackDataSize(160, FALSE);
}

void testUnPackData_100CharRandomData(){
  testUnpackDataChars(100, TRUE);
}

void testUnPackData_100CharRandomSize(){
  testUnpackDataSize(100, TRUE);
}

void testUnPackData_12CharForwardsData(){
  testUnpackDataChars(12, FALSE);
}

void testUnPackData_12CharForwardsSize(){
  testUnpackDataSize(12, FALSE);
}

void testUnPackData_25CharRandomData(){
  testUnpackDataChars(25, TRUE);
}

void testUnPackData_25CharRandomSize(){
  testUnpackDataSize(25, TRUE);
}

void testUnPackData_1CharForwardsData(){
  testUnpackDataChars(1, FALSE);
}

void testUnPackData_1CharForwardsSize(){
  testUnpackDataSize(1, FALSE);
}

void testCurve(){
}
