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


#define DOMAIN 			AF_INET			// used in socket() function call
#define TYPE 			SOCK_DGRAM		// used in socket() function call
#define PROTOCOL 		0				// used in socket() function call
#define BACKLOG			5				// used in listen() function call

typedef struct socket_t {
	int sockfd;
	struct sockaddr_in addr;
	socklen_t addr_len;
} socket_t;


// Global Variables
extern socket_t laptop, drone;
extern int seqnum;

int init_socket();
int ReceiveControlCommand();
int close_socket();


#endif /* CONTROL_COMPORT_H_ */
