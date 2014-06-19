#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "packets.h"

/**
 * COMPLETE THIS FUNCTION
 * 
 * This function reads in the message to send across the network.
 * It MUST use getchar() and only getchar() to read information from the keyboard
 * It MUST write at most MAX_MESSAGE_LEN characters into message[]
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
	int i = 0;
	int temp;
	
	for(i = 0; (temp = getchar()) != '\n'; i++){
		if(i < MAX_MESSAGE_LEN){
			message[i] = (char)temp;
		}
	}
	
	return i;
}

/**
 * COMPLETE THIS FUNCTION
 * 
 * The purpose of pack_message() is that it must cut up the message and store it in 
 * the 16 character "packets" in packet_array.  It must make each packet follow the 
 * format described on the homework page.
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
 * Note: You must use the MINIMUM number of packets needed for a given message
 * Note: The packets you use must be contiguous and start at index 0
 * Note: YOU MUST RETURN the NUMBER OF PACKETS YOU USED, or else your program will throw
 *       weird errors.
 * 
 * @param message The char array holding the message to be formatted into packet_array, then
 *                sent across the network
 * @param message_length The length of the message stored in the parameter message
 * @param packet_array The packets to be filled according to the format above, that will be 
 *                     'transmitted' across the 'network'
 */
int pack_message(char message[], int message_length, char packet_array[][PACKET_SIZE]) {
	int packet_index = 0;
	int j = 0;
	int message_num = get_message_number();
	int message_left = message_length;
	int packets_needed = (message_length / 12) + ((message_length % 12 == 0) ? 0 : 1);

	if (message_length >= 256)
		return -1;

	for (packet_index = 0; packet_index < packets_needed; packet_index++) {

		packet_array[packet_index][0] = (char)message_num;
		packet_array[packet_index][1] = (char)packet_index;
		packet_array[packet_index][2]
				= (char)((packet_index == packets_needed-1) ? FALSE : TRUE);
		packet_array[packet_index][3]
				= (char)((packet_index == packets_needed-1) ? (message_length - packet_index * 12)
						: 12);

		for (j = 0; j < 12 && j < message_left; j++) {
			packet_array[packet_index][j + 4] = (char)message[((packet_index)*12) + j];
		}
		message_left-=j;
	}

	return packets_needed;
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
 * When you call receive_packet(), you will pass to it an array of chars of size 16 that
 * you have previously declared.  When receive_packet() returns, the array you passed
 * to it will contain the values of the next packet.
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
 * When you have reconstructed the message by reading in all the necessary packets, 
 * 
 * Hint: Your code will most likely use the constant MAX_AVAILABLE_PACKETS
 * Note: You can make no assumptions about the nature of the incoming payloads.
 * 	     IE, sending payloads with just NULL values is valid
 * 
 * @param return_message the array that the message will be written to.
 * @return the size of the message written to return_message
 */
int receive_message(char return_message[]) {
	char temp_packet[16];
	int packet_numbers_received[MAX_AVAILABLE_PACKETS];
	int current_packet_index = 0;
	int current_packet_hasmore = FALSE;
	int current_packet_datalength = 0;
	int message_size = 0;
	int last_packet_index = -1;
	int i = 0;
	int packets_completed = TRUE;
	
	// Clear the packet_numbers_received[]
	for(i = 0; i < MAX_AVAILABLE_PACKETS; i++){
		packet_numbers_received[i] = FALSE;
	}
	
	while(1){
		
		receive_packet(temp_packet);
		
		if(last_packet_index != -1){
			
			// Check to see if complete
			packets_completed = TRUE;
			for(i = 0; i < last_packet_index; i++){
				if(packet_numbers_received[i] == FALSE){
					packets_completed = FALSE;
					break;
				}
			}
			
			// If complete, return
			if(packets_completed){
				return message_size;
			}
		}
		
		current_packet_index = (int)temp_packet[1];
		current_packet_hasmore = (int)temp_packet[2];
		current_packet_datalength = (int)temp_packet[3];
				
		if(current_packet_hasmore == FALSE){
			last_packet_index = current_packet_index;
			message_size = current_packet_index * 12 + current_packet_datalength;
		}
		
		for(i = 0; i < (int)temp_packet[3]; i++){
			return_message[i+(current_packet_index*12)] = temp_packet[i+4];
		}

		packet_numbers_received[current_packet_index] = TRUE;
	}

	return message_size;
}
