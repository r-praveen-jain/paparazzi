/*
 * Control_COMport.c
 *
 *  Created on: Feb 27, 2015
 *      Author: praveen
 */

#include "Control_COMport.h"
#include "../parameters.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// Global Variables
socket_t laptop, drone;
int seqnum = 0;
int init_socket(){
	char res;
	laptop.addr.sin_family = DOMAIN;
	inet_aton(LAPTOP_IP, &laptop.addr.sin_addr);
	laptop.addr.sin_port = htons(CONTROL_PORT);
	laptop.addr_len = sizeof(laptop.addr);

	drone.addr.sin_family = DOMAIN;
	inet_aton(DRONE_IP, &drone.addr.sin_addr);
	drone.addr.sin_port = htons(CONTROL_PORT);
	drone.addr_len = sizeof(drone.addr);

	drone.sockfd = socket(DOMAIN,TYPE,PROTOCOL);
	res =  bind(drone.sockfd, (struct sockaddr *) &drone.addr, drone.addr_len);
		if (res == -1){
			perror("Socket binding failed");
			exit(EXIT_FAILURE);
		}
	return EXIT_SUCCESS;
}


int ReceiveControlCommand(){
	char n = 0;
//	char ControlCommand[255];
//	n = recvfrom(drone.sockfd, ControlCommand, strlen(ControlCommand),0, (struct sockaddr *)&laptop.addr, &laptop.addr_len);
//	if (n < 0){
//		perror("Could not send control command\n");
//		exit(EXIT_FAILURE);
//	}
	printf("Thread Working\n");
	return n;
}


int close_socket(){
	char res;
	res = close(drone.sockfd);
	if(res == -1){
		perror("Error Closing Socket");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
