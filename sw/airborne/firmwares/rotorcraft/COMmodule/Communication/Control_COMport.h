/*
 * Control_COMport.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Praveen Jain (r.praveen.jain@gmail.com)
 * Description: Header file needed to establish communication with the external controller
 */

#ifndef CONTROL_COMPORT_H_
#define CONTROL_COMPORT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "../parameters.h"


#define MYDOMAIN 		AF_INET			// used in socket() function call
#define TYPE 			SOCK_DGRAM		// used in socket() function call
#define PROTOCOL 		0			    // used in socket() function call
#define BACKLOG			5			    // used in listen() function call


typedef struct mysocket_t {
	int sockfd;
	struct sockaddr_in addr;
	socklen_t addr_len;
} mysocket_t;

typedef struct myrefcommand_t{
	double thrust;
	double phi;			// roll
	double theta;	    // pitch
	double psi;			// psi	
} myrefcommand_t;		// Structure to store the depacketized control command

// Global Variables
extern mysocket_t laptop_control, drone_control; // sockets to receive control commands

#ifdef USE_MYTELEMETRY
extern mysocket_t laptop_telemetry, drone_telemetry; // sockets to send telemetry data
#endif
extern myrefcommand_t myrefcommand; // Structure variable used to store the depacketized control command
extern unsigned int myseqnum;		// Sequence number of the control command received. Could be used to detect packet loss.

int my_init_socket(void);								// Initialize socket connections with external controller
int my_ReceiveControlCommand(void);						// Function to receive the control commands from external controller
int my_SendPacket(char *packet, uint16_t numBytes);		// Function to send data pointed by *packet of size numBytes
int my_close_socket(void);								// Close all socket connections


#endif /* CONTROL_COMPORT_H_ */
