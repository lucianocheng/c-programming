#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "packets.h"

/**
 *  READ THIS FIRST
 * 
 *  In networking, messages between various hosts on the network, or various applications
 *  on the computer, are cut up into discrete pieces before being sent across the network.
 *  This way, everybody takes turns sending their packets across the network and 
 *  is able to share the connection.
 *
 *  In this assignment you will construct a program that will cut up an array of
 *  bytes, a 'message', into contiguous packets to be sent across such a network.
 *  The program will read messages from the user, and send them across the 'network' one at a time.
 *
 *  All messages are cut up into packets, and all packets have two parts, a header and a payload.  
 *  The header contains information about the packet's source, destination, size, index, etc.
 *  The payload contains the information to be transmitted.  In our case, this is a fragment of the message.
 *
 *  Our packets will be char arrays of size 16.  Recall that a char has a 'width' of one byte.
 *
 *  Each packet is constructed as follows:
 *  
 *  Header: First 4 chars, where the size of a char is 1 byte
 *    packet[0] = The message index number, given by get_message_number().  Call get_message_number() only
 *                one time for each time pack_message() is called.
 *                Type: a int, cast as a char.  Note that since a char is 1 byte wide
 *                      and (in gcc) a int is 4 bytes wide, we will be losing some precision.
 *                      However, since we are only sending at most 20 messages, we only need
 *                      one byte of space.
 *    packet[1] = The packet index.  Each message is sent across multiple packets.  Indexing
 *                starts as 0 and counts upward.
 *                Type: like above, this is a int cast as a char.  We are losing precision again,
 *                      but since we are only sending 20 packets at most, it is ok.
 *    packet[2] = "More" flag.  
 *                Type: an int, cast as a char.  The 'More' flag is set as true when there exists
 * 						packets with the same message on the network with a higher packet index.
 * 						Effectively, the 'More' flag is TRUE in every packet in the message, except
 * 						for the last packet.
 * 
 *                      The More flag has only two possible values: FALSE if this is the last packet, 
 * 						TRUE otherwise. In the packets.h file we have defined FALSE as 0 and TRUE as 1
 *    packet[3] = number of bytes (chars) of the message stored in this packet
 *                Type: an int, cast as a char.
 *                      Since there are only 12 remaining spots in our in the array, this is a number
 *                      between 1 and 12 inclusive.
 *  
 *  Payload: Last 12 bytes 
 *    packet[4] to packet[15] = this packet's portion of the message
 *                Type: chars.
 * 
 * For convenience, we have defined the following constants in packets.h:
 * 
 * TRUE is defined as the value 1
 * FALSE is defined as the value 0
 * MAX_AVAILABLE_PACKETS is defined as the value 20
 *      MAX_AVAILABLE_PACKETS is the maximum number of packets that can be used for one message
 * MAX_MESSAGE_LEN is defined as the value 240,
 * 	    MAX_MESSAGE_LEN is the maximum number of characters that can be sent as one message.  This
 *      is MAX_AVAILABLE_PACKETS * 12, where 12 is the number of bytes in the payload of one packet
 * MAX_MESSAGES is defined as 120
 * 		MAX_MESSAGES is the maximum number of messages that can be sent through our network
 * PACKET_SIZE is defined as 16
 *      PACKET_SIZE is the size of a packet, in bytes
 * 
 * IMPORTANT NOTE: In the packets.h file are some global variables used to run the simulation.  All
 * these variables end in '_global'.  Under no circumstances are you to read or modify these variables
 * in the code you produce.                           
 */

// ARGGGG - BELOW THIS LINE BE GRADING CODE, DO NOT DELETE
/**
 * The main function is where the program loops accepting repeated messages to send across
 * the network.
 * 
 * 1. Loop until user indicates he wants to exit by typing "X <enter>",
 *    or the maximum number of messages is sent
 * 2. Requests the user to enter input via get_data_from_user()
 * 3. Prints the message the user inputted, and the size of the message
 * 4. Packs the message into packets by calling pack_message()
 * 5. Prints out the configuration of the packets based on the configuration created by pack_message()
 * 6. Randomizes the packet order and adds duplicate packets by calling randomize_packets()
 * 7. Gets the reconstructed message off the network by calling receive_message()
 * 8. Prints the received message, and the size returned by the function
 * 9. Continues in the loop
 */
int main(int argc, char* argv[]) {

	int sent_message_size = 0;
	int response_message_size = 0;
	char sent_message[MAX_MESSAGE_LEN];
	char response_message[MAX_MESSAGE_LEN];
	int i = 0;
	printf("-----------------------\n");
	printf("Packets Program Started\n");
	printf("-----------------------\n");
	
	while(message_counter_global < MAX_MESSAGES){

		// Reset the message information for this message
		reset_packet_array();
		sent_message_size = 0;
		response_message_size = 0;
		
		// Get the message from the user
		printf("\nEnter your message then hit ENTER. Hit 'X' then ENTER to exit:\n");
		while(sent_message_size <= 0){
			sent_message_size = get_data_from_user(sent_message);
			if(sent_message_size <= 0 || sent_message_size > MAX_MESSAGE_LEN){
				printf("Error: Invalid message size: %d\n", sent_message_size);
				sent_message_size = 0;
			}
		}
		
		// If the message is only a 'x' or 'X', break out of the loop
		if((sent_message[0] == 'X' || sent_message[0] == 'x') && sent_message_size == 1){
			break;
		}

		// Print out the message information
		printf("\nMessage To Send: '");
		for(i = 0; i < sent_message_size; i++){
			printf("%c", sent_message[i]);
		}
		printf("'\n");
		printf("Message Size: %d\n", sent_message_size);

		// Pack the data to send across the simulated network
		packets_sent_global = pack_message(sent_message, sent_message_size, packet_array_global);

		if(packets_sent_global > 0){
			
			// Print out the packets before randomizing them
			print_all_packets();
			
			// Randomize the packets, create duplicates to simulate network
			printf("\nRandomizing Packet Order and Creating Duplicates... ");
			randomize_packets(packets_sent_global);
			printf("Done\n\n");
			
			// Get the message received
			response_message_size = receive_message(response_message);
	
			printf("Message Received: '");
			for (i = 0; i < response_message_size; i++) {
				printf("%c", response_message[i]);
			}
			printf("'\n");
			printf("Message Size: %d\n", response_message_size);
		}
	}

	printf("\nPACKETS program completed\n");
	return EXIT_SUCCESS;
}

/**
 * This function prints out all the packets in their current configuration in
 * packets_sent_global
 */
void print_all_packets(){
	int i = 0;
	int j = 0;
	
	printf("Packets Set: \n");
	for(i = 0; i < packets_sent_global; i++){
		printf("  Packet %5d: ", i);
		for(j = 0; j < PACKET_SIZE; j++){
			if(j == 2){
				printf("[%s]", ((int)packet_array_global[i][j] == TRUE) ? " TRUE" : "FALSE");
			}
			else if(j < 4){
				printf("[%5d]", (int)packet_array_global[i][j]);
			}
			else{
				printf("[%c]", (char)packet_array_global[i][j]);
			}
		}
		printf("\n");
	}
}

/**
 * This function blanks the packet array (the packets on the 'network'), 
 * and sets the global variables back to their intial values
 */
void reset_packet_array(){
	int i;
	int j;
	
	for(i = 0; i < MAX_AVAILABLE_PACKETS; i++){
		for(j = 0; j < PACKET_SIZE; j++){
			packet_array_global[i][j] = ' ';
		}
	}
	
	packets_sent_global = 0;
	packets_received_global = 0;
}

/**
 * This function returns the current msg number, and auto-increments
 */
int get_message_number() {
	return message_counter_global++;
}

/**
 * Returns a single packet that was sent on the 'network'.  All the 'packets' have already
 * been put on the 'network' via the pack_message() function.
 * 
 * Note, a char* is a pointer that points to a character variable location in memory.
 * When a char* points to a char array, it points to the first element in that array.
 * In the case of this program, all char*'s (if properly used) can be treated as arrays,
 * since they should only be pointed to arrays.
 * 
 * @return a packet, a char array of size 16 formatted as above
 */
char* receive_packet(){
	char* tempPacket;
	
	if(packets_received_global < 0 || packets_received_global >= 32766){
		printf("Fatal Error: Packet received count is %d\n", packets_received_global);
		printf("     This number is invalid.\n");
		printf("     You either manually modified packets_received_global, or you requested\n");
		printf("     too many packets from the system.");
		exit(EXIT_FAILURE);
	}
	
	tempPacket = packet_array_global[packets_received_global % (packets_sent_global * 2)];
	packets_received_global++;
	
	return tempPacket;
}

/**
 * Randomize the packet order in the packet array (network), and create duplicates duplicates.
 * This is to simulate the packets being sent across a network.
 * 
 */
void randomize_packets(){
	int i = 0;
	int j = 0;
	int k = 0;
	char temp_char;
	
	// Duplicate the packets
	for(i = 0; i < packets_sent_global; i++){
		for(j = 0; j < PACKET_SIZE; j++){
			packet_array_global[i+packets_sent_global][j] = packet_array_global[i][j];
		}
	}
	
	// Seed the random number generator based on the wall clock
	srand(time(NULL));
	
	// Mix the packets up randomly
	for(i = 0; i < packets_sent_global * 2; i++){
		for(j = 0; j < packets_sent_global * 2; j++){
			if(rand() % 2 == 0){
				for(k = 0; k < PACKET_SIZE; k++){
					temp_char = packet_array_global[i][k];
					packet_array_global[i][k] = packet_array_global[j][k];
					packet_array_global[j][k] = temp_char;
				}
			}
		}
	}
} 
// ARGGGG - ABOVE THIS LINE BE GRADING CODE, DO NOT MODIFY OR DELETE

/**
 * COMPLETE THIS FUNCTION
 * 
 * This function reads in the message to send across the network.
 * It MUST use getchar() and only getchar() to read information from the keyboard
 * 
 * This function should do the following:
 * 
 * 1. Read in characters from getchar() until a newline is read from getchar()
 * 2. Store the characters you read in the array message[] up to, but not 
 * 	  including, the newline, or up to the point where message[] is full.  
 * 	  The message[] array is of size MAX_MESSAGE_LEN
 * 3. Return the total number of characters received by getchar().
 * 
 * Note: The character for enter is the same as a newline, and can be written as '\n'
 * Note: Even if a user inputs more characters than MAX_MESSAGE_LEN, you should return
 *       the total number of characters read in by getchar(), excluding the newline
 * 
 * @param message The array where the message is written to, according to the description above
 * @return the bytes read in by getchar() until a '\n' is reach, according to the description above
 */
int get_data_from_user(char message[]){
	return 0;
}

/**
 * COMPLETE THIS FUNCTION
 * 
 * The purpose of pack_message() is that it must cut up the message and store it in 
 * the 16 character "packets" in packet_array.  It must make each packet follow the 
 * format above.
 * 
 * pack_message() is given the following parameters:
 * 		message: An array of chars called 'message' that contains the message to be sent
 * 		message_length: An integer that is the length of the message stored in message[]
 * 		packet_array: An array of packets, where a packet is a char array of size 16, 
 * 		represented as a two dimensional array of characters
 * 
 * The array of packets is accessed as a two-dimensional array in the following format:
 *     packet_array[(packet index number i)][(byte inside packet at index i)]
 *     IE, char (byte) index 1 of packet 3 is accessed using the syntax: packet_array[3][1]
 * 
 * You cannot use more then MAX_AVAILABLE_PACKETS packets, or send more then MAX_MESSAGE_LEN
 * chars within a single message.  If message_length is > MAX_MESSAGE_LEN, you are to return
 * -1 and not format any packets.
 *
 * Othwerwise, this function should format the packets in packet_array, and
 * return the number of packets used.
 * 
 * Note: Assume that message_length > 0
 * Note: You must use the minimum number of packets needed for a given message
 * Note: The packets you use must be contiguous and start at index 0
 * 
 * @param message The char array holding the message to be formatted into packet_array, then
 *                sent across the network
 * @param message_length The length of the message stored in the parameter message
 * @param packet_array The packets to be filled according to the format above, that will be 
 *                     'transmitted' across the 'network'
 */
int pack_message(char message[], int message_length, char packet_array[][PACKET_SIZE]) {
	return 0;
}

/**
 * COMPLETE THIS FUNCTION
 * 
 * The purpose of this function is to retrieve the packets put on the 'network'
 * by pack_message(), and use those packets to reconstruct the message that was 
 * sent across the 'network'.
 * 
 * receive_message() is given the following parameters:
 * 		return_message: an array of char's which upon completion will have the 
 * 					    original message reconstructed as a single character array.
 * 
 * This function must call receive_packet() repeatidly until it receives all the packets
 * necessary to reconstruct the message.
 * 
 * Calling receive_packet() retrieves 1 packet from the network, where a packet
 * is a 16 character array, formatted as above.
 * 
 * Because the packets have been sent across the network, the packets will not be
 * received in the same order that you sent them.  You therefore will have to reconstruct
 * the message from out of order packets using the information stored in each packet header.
 *
 * Additionally, because copies of packets may have been routed differently, or packets
 * may have been assumed lost by the sender and resent, there is no gaurentee
 * that receive_packet() will not return the same packet twice.
 * 
 * Finally, even if all packets from the message have been returned, receive_packet() will
 * always return a packet of the message when called.  You must use the information within
 * the packets you are receiving to figure out when to stop calling receive_packet()
 *
 * When you have reconstructed the message by reading in all the necessary packets, make
 * sure that the message has been written into return_message, and to return the length
 * of the message
 * 
 * Hint: There can be at most MAX_AVAILABLE_PACKETS unique packets on the network for 
 *       the given message.  This also means that the packet indexes for a given message
 *       can go from 0 to at most MAX_AVAILABLE_PACKETS - 1
 * Note: You can make no assumptions about the nature of the data inside the incoming payloads.
 * 	     IE, sending payloads with just NULL values is valid
 * 
 * @param return_message the array that the message will be written to.
 * @return the size of the message written to return_message
 */
int receive_message(char return_message[]) {
	return 0;
}
