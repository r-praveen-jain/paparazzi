/*
 * Control_COMport.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Praveen Jain
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
#define PROTOCOL 		0			// used in socket() function call
#define BACKLOG			5			// used in listen() function call

typedef struct mysocket_t {
	int sockfd;
	struct sockaddr_in addr;
	socklen_t addr_len;
} mysocket_t;

typedef struct myrefcommand_t{
	double thrust;
	double phi;			// roll
	double theta;			// pitch
	double psi;			// psi	
} myrefcommand_t;				// Structure to store the depacketized control command

// Global Variables
extern mysocket_t laptop_control, drone_control; // sockets to receive control commands

#ifdef USE_MYTELEMETRY
extern mysocket_t laptop_telemetry, drone_telemetry;
#endif
extern myrefcommand_t myrefcommand;
extern unsigned int myseqnum;

int my_init_socket(void);
int my_ReceiveControlCommand(void);
int my_SendPacket(char *packet, uint16_t numBytes);
int my_close_socket(void);


#endif /* CONTROL_COMPORT_H_ */
