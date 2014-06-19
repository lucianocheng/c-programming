/**
 * DO NOT MODIFY
 * 
 * packets.h
 * Function headers and constants for packets.c
 */

// Define Constants

// Define TRUE and FALSE and the integers 1 and 0
#define TRUE 1
#define FALSE 0

// Define the maximum length of a message that can be sent across the network
// This is set to be 12 * MAX_AVAILABLE_PACKETS, where 12 bytes of payload are stored in
//      one packet
#define MAX_MESSAGE_LEN 240

// Define the maximum number of packets that can be used by a single message
#define MAX_AVAILABLE_PACKETS 20

// Define the maximum number of messages that can be sent before program must exit
#define MAX_MESSAGES 120

// Define the size of a packet
#define PACKET_SIZE 16

// Global variables, do not set or access these variables in your code
char packet_array_global[MAX_AVAILABLE_PACKETS * 2][PACKET_SIZE];
int packets_sent_global = 0;
int packets_received_global = 0;
int message_counter_global = 0;

// Function headers
void print_all_packets();
int get_message_number();
void randomize_packets();
void reset_packet_array();
char* receive_packet();
int get_data_from_user(char[]);
int pack_message(char[], int, char[][PACKET_SIZE]);
int receive_message(char[]);
