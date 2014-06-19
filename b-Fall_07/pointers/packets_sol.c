#include "packets.h"
#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAX_MESSAGE_LEN 256
#define MAX_AVAILABLE_PACKETS 100
#define MAX_MESSAGES 20
#define PACKET_SIZE 16

/*
  In networking, data between various hosts on the network, or various applications
  on the computer, are cut up into discrete pieces before being sent across the network.
  This way, everybody takes turns sending their packets across the network and 
  is able to share the connection.

  In this assignment you will construct a program that will cut up an array of
  bytes into contiguous packets to be sent across such a network.

  All packets have two parts, called a header and a payload.  
  The header contains information about the packet's source, destination, size, index, etc.
  The payload contains the information to be transmitted.

  Our packets will be char arrays of size 16.  Recall that a char is one byte big.

  Each packet is constructed as follows:
  
  Header: First 4 chars (bytes)
    packet[0] = The message index number, given by getMsgNumber().  Call getMsgNumber only
                one time for each time packData() gets called.
                Type: a int, cast as a char.  Note that since a char is 1 byte wide
                      and (in gcc) a int is 4 bytes wide, we will be losing some precision.
                      However, since we are only sending at most 20 messages, we only need
                      one byte of space.
    packet[1] = The packet index.  Your data is sent across multiple packets.  Indexing
                starts as 0 and counts upward.
                Type: again, this is a int cast as a char.  We are losing precision again,
                      but since we are only sending 100 packets at most, it is ok.
    packet[2] = "More" flag.  
                Type: an int, cast as a char.
                      Only two possible values: FALSE if this is the last packet, TRUE otherwise
    packet[3] = number of bytes(chars) of data stored in this packet
                Type: an int, cast as a char.
                      Since there are only 12 remaining spots in our in the array, this is a number
                      between 1 and 12 inclusive.  Again, we will be losing precision, but since
					  the numbers we are storing in there are so small, it doesn't matter
  
  Payload: Last 12 bytes
    packet[4] to packet[15] = chars from the data array
                Type: chars.

  # Don't forget to compile with warnings, using the -Wall flag
  # The data being given to you is not gaurenteed to be a null-terminated string. Therefore, the
    strlib functions will not work on it.
  # The packets must be formatted as stated above, our tester will be checking this format.  Do not
       use the header in the packet for anything other than the data specified
  # To test this program after compilation, redirect a file with data to be sent into it:
       gcc packets.c -Wall -o packets
       ./packets < test_data.txt
  # Tester scripts will be released this weekend to run tests on your code.  Please test it before
    turning it in, as sometimes very small bugs will make large differences and cost a lot of
	points.
  # The global packetsReceived, packetsSent, and msgNumberCounter variables are for tester purposes
    only, you are not allowed to modify them or access them in your functions.  Also, you are not
	allowed to access packetArray directly in your unpackData function.
*/

char** packetArray;
int packetsReceived = 0;
int packetsSent = 0;
int msgNumberCounter = 0;

/**
 * 1. Main reads in data from stdin until 256 chars or EOF
 * 2. Sends data to packData, gets a array of byte arrays back
 * 3. Randomizes packet order, to simulate being sent across a network
 * 4. Main calls unpack with a array as a parameter.
 * 5. When unpack finishes, that array will have the original data in it.
 */

#ifndef TEST_1xx
int main(int argc, char* argv[]){

  char temp;
  char data[MAX_MESSAGE_LEN];
  char receivedData[MAX_MESSAGE_LEN];
  char* tempPacket;

  int dataSize = 0, i = 0, j = 0;
  int receivedDataSize;

  // Construct the data
  for(i = 0; ((temp = getchar()) != EOF) && i < MAX_MESSAGE_LEN; i++){
    data[i] = temp;
  }
  dataSize = i;

  printf("Data Sent: ");
  for(i = 0; i < dataSize; i++){
    printf("%c", data[i]);
  }
  printf("\n");

  // Construct the array of packets
  packetArray = (char**)malloc(sizeof(char*) * MAX_AVAILABLE_PACKETS);
  for(i = 0; i < MAX_AVAILABLE_PACKETS; i++){
    packetArray[i] = (char*)malloc(sizeof(char) * PACKET_SIZE);
  }

  // Pack the data
  packetsSent = packData(data, dataSize, packetArray);

  if(packetsSent == -1) exit(EXIT_FAILURE);

  // Randomize the packet order
  srand(101010);
  for(i = 0; i < packetsSent; i++){
    for(j = 0; j < packetsSent; j++){
      if(rand() % 2 == 0){
        tempPacket = packetArray[i];
        packetArray[i] = packetArray[j];
        packetArray[j] = tempPacket;
      }
    }
  }

  receivedDataSize = unpackData(receivedData);

  printf("Data Received: ");
  for(i = 0; i < receivedDataSize; i++){
    printf("%c", receivedData[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
#endif

/**
 * int packData()
 * 
 * packdata() is given a array of char's with the data to be sent,
 * a integer datasize that has the size of the data array, and
 * a array of packets, where a packet is a char array of size 16
 * 
 * packdata() must cut up the data and store it in the 16 character "packets" 
 * in packetArray according to the format above.
 * 
 * You cannot use more then 100 packets, or send more then 256 chars of
 * data across the network.  If datasize is > 256, you are to return
 * -1 and not format any packets.
 *
 * Othwerwise, this function should format the packets in packetArray, and
 * return the number of packets used. 
 */
int packData(char data[], int dataSize, char* packetArray[]){
  int packetIndex = 0;
  int j = 0;
  int msgNumber = getMsgNumber();
  int dataLeft = dataSize;

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
  
  return packetsNeeded;
}


/**
 * int unPackData()
 * 
 * unPackdata() is given a array of char's which upon completion will have the,
 * original message reconstructed as a single character array.
 * 
 * Calling receivePacket will return 1 packet from the network, where a packet
 * is a 16 character array, formatted as above.
 * 
 * Because the packets have been sent across the network, the packets will not be
 * received in the same order that you sent them.  You therefore will have to reconstruct
 * the message from out of order packets using the information stored in each packet header.
 *
 * When all packets have been received, receivePacket() will return NULL
 *
 * When you have read in all packets, return the total length of the data you read in
 */
int unpackData(char data[]){
  char* tempPacket = NULL;
  int curPacketIndex = 0;
  int i = 0;
  int dataSizeCounter = 0;

  while((tempPacket = receivePacket()) != NULL){
    curPacketIndex = (int)tempPacket[1];

    for(i = 0; i < (int)tempPacket[3]; i++){
      data[i+(curPacketIndex*12)] = tempPacket[i+4];
    }
    dataSizeCounter+=(int)tempPacket[3];
  }

  return dataSizeCounter;
}

/**
 * returns the current msg number, for testing purposes
 */
int getMsgNumber(){
  return msgNumberCounter++;
}
/**
 * returns a single packet that was sent.  Returns NULL if no packets remaining
 */
char* receivePacket(){
  char* tempPacket;

  if(packetsReceived >= packetsSent) return NULL;
  else{
    tempPacket = packetArray[packetsReceived];
    packetsReceived++;
    return tempPacket;
  }
}
