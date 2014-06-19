#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "packets.h"

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

#ifndef TEST_1xx

int main(int argc, char* argv[]) {

	// Set Local Variables
	int sent_message_size = 0;
	int response_message_size = 0;
	char sent_message[MAX_MESSAGE_LEN];
	char response_message[MAX_MESSAGE_LEN];
	int i = 0;
	
	// Set Global Variables
	packets_sent_global = 0;
	packets_received_global = 0;
	message_counter_global = 0;
	
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

		printf("Packets used to send the message: %d\n\n", packets_sent_global);
		
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
		else{
			printf("Error: No packets used ... does pack_message() return the right value?\n");
		}
	}

	printf("\nPACKETS program completed\n");
	return EXIT_SUCCESS;
}
#endif

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
 */
void receive_packet(char tempPacket[]){
	
	int i = 0;
	
	if(packets_received_global < 0 || packets_received_global >= 32766){
		printf("Fatal Error: Packet received count is %d\n", packets_received_global);
		printf("     This number is invalid.\n");
		printf("     You either manually modified packets_received_global, or you requested\n");
		printf("     too many packets from the system.");
		exit(EXIT_FAILURE);
	}
	
	for(i = 0; i < 16; i++){
		tempPacket[i] = packet_array_global[packets_received_global % (packets_sent_global * 2)][i];
	}
	
	packets_received_global++;
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
