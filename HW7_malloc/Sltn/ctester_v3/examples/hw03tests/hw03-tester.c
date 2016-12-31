/**
 * Test ESE 116 HW 03, Spring 2008
 *
 * @version 2008 March 21st
 * @author JJ Geewax
 *
 * Tests of the tester:
 *	- stubbed implementation provided fails all tests
 *	- (presumably) correct solution passes all tests
 */
 
// general homework tester stuff
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 // specific to this homework
#include "packets.h"
#include "cgrader.h"

// globals:
char test_user_input[MAX_MESSAGE_LEN*2+1];
int test_user_input_index = 0;

// tester functions' headers
void test_get_data_from_user_length();
void test_get_data_from_user_basic();
void test_get_data_from_user_overload_length();
void test_get_data_from_user_overload();

void test_pack_data_length();
void test_pack_data_length_normal();
void test_pack_data_length_oversized();
void test_pack_data_content_short();
void test_pack_data_content_normal();
void test_pack_data_header_short();
void test_pack_data_header_normal();

void test_receive_data_length_short();
void test_receive_data_length_normal();
void test_receive_data_content_short();
void test_receive_data_content_normal();

// Non-testing functions & variables necessary for tests to complete
void reset_test_user_input();
void set_user_input(char *, int);

// tester main
int main(int argc, char * argv[]) {
	PROBLEM * prob1 = add_new_problem("get_data_from_user", 1);
	/* 5+7+6+7 = 25 points */
	add_new_test(prob1, "Get data from user (length)", 5,
		&test_get_data_from_user_length);
	add_new_test(prob1, "Get data from user", 7,
		&test_get_data_from_user_basic);
	add_new_test(prob1, "Get data from user that is too long (length)", 6,
		&test_get_data_from_user_overload_length);
	add_new_test(prob1, "Get data from user that is too long", 7, 
		&test_get_data_from_user_overload);
		
	PROBLEM * prob2 = add_new_problem("pack_message", 2);
	/* 35 points */
	add_new_test(prob2, "Pack data (length)", 5,
		&test_pack_data_length);
	add_new_test(prob2, "Pack data (length) (normal)", 5,
		&test_pack_data_length_normal);
	add_new_test(prob2, "Pack data (length) (oversized)", 5,
		&test_pack_data_length_oversized);
	add_new_test(prob2, "Pack data (short)", 5, 
		&test_pack_data_content_short);
	add_new_test(prob2, "Pack data (normal)", 5,
		&test_pack_data_content_normal);
	add_new_test(prob2, "Pack data header (short)", 5, 
		&test_pack_data_header_short);
	add_new_test(prob2, "Pack data header (normal)", 5, 
		&test_pack_data_header_normal);

	PROBLEM * prob3 = add_new_problem("receive_message", 3);
	/* 40 points */
	add_new_test(prob3, "Receive data (length) (short)", 8,
		&test_receive_data_length_short);
	add_new_test(prob3, "Receive data (length) (normal)", 12,
		&test_receive_data_length_normal);
	add_new_test(prob3, "Receive data content (short)", 8, 
		&test_receive_data_content_short);
	add_new_test(prob3, "Receive data content (long)", 12,
		&test_receive_data_content_normal);


	run_all_tests(argc, argv);
	clean_up();	
	return 0;
}

// Functions that are extern'ed by the library testing type for the xml parser
// Must be filled in
char* ct_get_file_suffix() { return ""; }
PS_TYPE ct_get_problem_set_type() { return HOMEWORK; }
int ct_get_problem_set_num() { return 11603; }

int test_get_char() {
  //printf("%c\n", test_user_input[test_user_input_index]);
  return (int) test_user_input[test_user_input_index++];
}

void reset_test_user_input() {
	test_user_input_index = 0;
	int i = 0;
	for (i = 0; i < MAX_MESSAGE_LEN*2+1; i++) test_user_input[i] = '\0';
}

void set_user_input(char * data, int len) {
	reset_test_user_input();
	int i;
	for(i = 0; i < len; i++) test_user_input[i] = data[i];
	test_user_input[i] = '\0';
}
/** 
 * ----------------------------------------------------
 * Specific Test Functions
 * ----------------------------------------------------
 */

/** Test the user_input Add */
void test_get_data_from_user_length() {
  // Test 1: get user data, make sure the length returns correctly
  char * userdata = "this is my message\nabc";
  // copy the data to our array
  set_user_input(userdata, 23);
  
  char message_storage[MAX_MESSAGE_LEN+1];
  int length = get_data_from_user(message_storage);

  assert_equals_int("Get data from user: Length", 18, length);
}

void test_get_data_from_user_basic() {
	// Test 2: get user data, make sure that the data is the same (would fill only one packet)
	char * userdata = "hello packets!\n"; // 15 chars (inlcuding the newline)
	set_user_input(userdata, 15);
	
	char message_storage[MAX_MESSAGE_LEN+1];
	get_data_from_user(message_storage);
	assert_equals_char_array("Test get data (basic)", userdata, message_storage, 14);
}

void test_get_data_from_user_overload_length() {
	char * big_data = malloc(sizeof(char) * MAX_MESSAGE_LEN * 2); // twice the size of the max message
	int i = 0;
	for (i = 0; i < MAX_MESSAGE_LEN * 2 - 1; i++) big_data[i] = 'o';
	big_data[MAX_MESSAGE_LEN * 2-1] = '\n'; // then give them a newline
	set_user_input(big_data, MAX_MESSAGE_LEN*2);
	
	char message_storage[MAX_MESSAGE_LEN*2+1];
	int length = get_data_from_user(message_storage);
	assert_equals_int("Test get data that is too big", MAX_MESSAGE_LEN*2-1, length);
}

void test_get_data_from_user_overload() {
	char * big_data = malloc(sizeof(char) * MAX_MESSAGE_LEN * 2); // twice the size of the max message
	int i = 0;
	for (i = 0; i < MAX_MESSAGE_LEN * 2 - 1; i++) big_data[i] = 'o';
	big_data[MAX_MESSAGE_LEN * 2-1] = '\n'; // then give them a newline
	set_user_input(big_data, MAX_MESSAGE_LEN*2);
	
	char message_storage[MAX_MESSAGE_LEN+1];
	get_data_from_user(message_storage);
	assert_equals_char_array("Test get data that is too long", big_data, message_storage, MAX_MESSAGE_LEN);
}

void test_pack_data_length() {
	// this should return the number of packets generated. 
	// with a short message, it should take one packet.
	char * my_data = "short";
	char packet_array[MAX_AVAILABLE_PACKETS][PACKET_SIZE];
	int num_packets = pack_message(my_data, strlen(my_data), packet_array);
	assert_equals_int("Test pack data length (short)", 1, num_packets);
}
void test_pack_data_length_normal() {
	// test something that takes up more than 2 packets
	char * my_data = "12345678901 12345678901 12345678901";
	char packet_array[MAX_AVAILABLE_PACKETS][PACKET_SIZE];
	int num_packets = pack_message(my_data, strlen(my_data), packet_array);
	assert_equals_int("Test pack data length (normal)", 3, num_packets);
}
void test_pack_data_length_oversized() {
	// test too long of a message
	char * my_data = malloc(sizeof(char) * MAX_MESSAGE_LEN * 2); // twice the size of the max message
	int i = 0;
	for(i = 0; i < MAX_MESSAGE_LEN * 2; i++) my_data[i] = '0';
	char packet_array[MAX_AVAILABLE_PACKETS][PACKET_SIZE];
	int num_packets = pack_message(my_data, MAX_MESSAGE_LEN * 2, packet_array);
	assert_equals_int("Test pack data length (oversized)", -1, num_packets);
}
void test_pack_data_content_short() {
	// test a short message's content
	char * my_data = "short";
	char packet_array[MAX_AVAILABLE_PACKETS][PACKET_SIZE];
	pack_message(my_data, strlen(my_data), packet_array);
	assert_equals_char_array("Test pack data short message", packet_array[0]+4, my_data, strlen(my_data));
}
void test_pack_data_content_normal() {
	char * my_data = "12345678901 12345678901 12345678901";
	char packet_array[MAX_AVAILABLE_PACKETS][PACKET_SIZE];
	pack_message(my_data, strlen(my_data), packet_array);
	assert_equals_char_array("Test pack data normal message (1)", packet_array[0]+4, my_data, 11);
	assert_equals_char_array("Test pack data normal message (2)", packet_array[1]+4, my_data, 11);
	assert_equals_char_array("Test pack data normal message (3)", packet_array[2]+4, my_data, 11);
}
void test_pack_data_header_short() {
	message_counter_global = 0;
	char * my_data = "short";
	char packet_array[MAX_AVAILABLE_PACKETS][PACKET_SIZE];
	pack_message(my_data, strlen(my_data), packet_array);
	assert_equals_int("Test pack data header (short) (message index)", 0, packet_array[0][0]);
	assert_equals_int("Test pack data header (short) (packet index)", 0, packet_array[0][1]);
	assert_equals_int("Test pack data header (short) (more flag)", FALSE, packet_array[0][2]);
	assert_equals_int("Test pack data header (short) (data size)", strlen(my_data), packet_array[0][3]);
}
void test_pack_data_header_normal() {
	message_counter_global = 0;
	char * my_data = "12345678901 12345678901 1234567890";
	char packet_array[MAX_AVAILABLE_PACKETS][PACKET_SIZE];
	pack_message(my_data, strlen(my_data), packet_array);
	assert_equals_int("Test pack data header (normal) (message index)", 0, packet_array[0][0]);
	assert_equals_int("Test pack data header (normal) (message index)", 0, packet_array[1][0]);
	assert_equals_int("Test pack data header (normal) (message index)", 0, packet_array[2][0]);

	assert_equals_int("Test pack data header (normal) (more flag)", TRUE, packet_array[0][2]);
	assert_equals_int("Test pack data header (normal) (more flag)", TRUE, packet_array[1][2]);
	assert_equals_int("Test pack data header (normal) (more flag)", FALSE, packet_array[2][2]);

	assert_equals_int("Test pack data header (normal) (packet index)", 0, packet_array[0][1]);
	assert_equals_int("Test pack data header (normal) (packet index)", 1, packet_array[1][1]);
	assert_equals_int("Test pack data header (normal) (packet index)", 2, packet_array[2][1]);

	assert_equals_int("Test pack data header (normal) (data size)", 12, packet_array[0][3]);
	assert_equals_int("Test pack data header (normal) (data size)", 12, packet_array[1][3]);
	assert_equals_int("Test pack data header (normal) (data size)", 10, packet_array[2][3]);
}

void test_receive_data_length_short() {
	message_counter_global = 1;
	packets_sent_global = 1;
	packets_received_global = 1;
	char * my_data = "short";
	int i;
	for(i = 0; i < PACKET_SIZE; i++) packet_array_global[0][i] = '\0';
	packet_array_global[0][0] = (char) 0;
	packet_array_global[0][1] = (char) 0;
	packet_array_global[0][2] = (char) FALSE;
	packet_array_global[0][3] = (char) strlen(my_data);
	strncpy(packet_array_global[0]+4, my_data, 12);
	randomize_packets();
      	char return_message[MAX_MESSAGE_LEN*2];
	int length = receive_message(return_message);
	assert_equals_int("Test receive message length (short)", strlen(my_data), length);
}

void test_receive_data_length_normal() {
  message_counter_global = 0;
  packets_sent_global = 3;
  packets_received_global = 3;
  
  char * my_data = "12345678901 12345678901 12345678901";
  int i, p;
  for(p = 0; p < 3; p++) for(i = 0; i < PACKET_SIZE; i++) packet_array_global[p][i] = '\0';
  packet_array_global[0][0] = 0;
  packet_array_global[0][1] = 0;
  packet_array_global[0][2] = TRUE;
  packet_array_global[0][3] = 12;
  strncpy(packet_array_global[0]+4, my_data, 12);
  packet_array_global[1][0] = 0;
  packet_array_global[1][1] = 1;
  packet_array_global[1][2] = TRUE;
  packet_array_global[1][3] = 12;
  strncpy(packet_array_global[1]+4, my_data+12, 12);
  packet_array_global[2][0] = 0;
  packet_array_global[2][1] = 2;
  packet_array_global[2][2] = FALSE;
  packet_array_global[2][3] = 11;
  strncpy(packet_array_global[2]+4, my_data+24, 11);
  char return_message[MAX_MESSAGE_LEN*2];
  randomize_packets();
  int length = receive_message(return_message);
  assert_equals_int("Test receive message length (normal)", strlen(my_data), length);
}

void test_receive_data_content_short() {
  	message_counter_global = 1;
	packets_sent_global = 1;
	packets_received_global = 1;
	char * my_data = "short";
	int i;
	for(i = 0; i < PACKET_SIZE; i++) packet_array_global[0][i] = '\0';
	packet_array_global[0][0] = (char) 0;
	packet_array_global[0][1] = (char) 0;
	packet_array_global[0][2] = (char) FALSE;
	packet_array_global[0][3] = (char) strlen(my_data);
	strncpy(packet_array_global[0]+4, my_data, 12);
	randomize_packets();
      	char return_message[MAX_MESSAGE_LEN*2];
	receive_message(return_message);
	assert_equals_char_array("Test receive message (short)", my_data, return_message, strlen(my_data));
}

void test_receive_data_content_normal() {
  message_counter_global = 0;
  packets_sent_global = 3;
  packets_received_global = 3;
  
  char * my_data = "12345678901 12345678901 12345678901";
  int i, p;
  for(p = 0; p < 3; p++) for(i = 0; i < PACKET_SIZE; i++) packet_array_global[p][i] = '\0';
  packet_array_global[0][0] = 0;
  packet_array_global[0][1] = 0;
  packet_array_global[0][2] = TRUE;
  packet_array_global[0][3] = 12;
  strncpy(packet_array_global[0]+4, my_data, 12);
  packet_array_global[1][0] = 0;
  packet_array_global[1][1] = 1;
  packet_array_global[1][2] = TRUE;
  packet_array_global[1][3] = 12;
  strncpy(packet_array_global[1]+4, my_data+12, 12);
  packet_array_global[2][0] = 0;
  packet_array_global[2][1] = 2;
  packet_array_global[2][2] = FALSE;
  packet_array_global[2][3] = 11;
  strncpy(packet_array_global[2]+4, my_data+24, 11);
  char return_message[MAX_MESSAGE_LEN*2];
  randomize_packets();
  receive_message(return_message);
  assert_equals_char_array("Test receive message (normal)", my_data, return_message, strlen(my_data));
}
