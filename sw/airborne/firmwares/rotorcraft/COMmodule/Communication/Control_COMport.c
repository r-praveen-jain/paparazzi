/*
 * Control_COMport.c
 *
 *  Created on: Feb 27, 2015
 *      Author: praveen
 */

#include "Control_COMport.h"
#include "../parameters.h"
#include "firmwares/rotorcraft/autopilot.h" //for autopilot_motors_on
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// Global Variables
mysocket_t laptop, drone;
myrefcommand_t myrefcommand = {.thrust = 0, .phi = 0, .theta = 0};

unsigned int myseqnum = 0;

//Function definition
int my_init_socket(void){
	char res;
	laptop.addr.sin_family = MYDOMAIN;
	inet_aton(LAPTOP_IP, &laptop.addr.sin_addr);
	laptop.addr.sin_port = htons(CONTROL_PORT);
	laptop.addr_len = sizeof(laptop.addr);

	drone.addr.sin_family = MYDOMAIN;
	inet_aton(DRONE_IP, &drone.addr.sin_addr);
	drone.addr.sin_port = htons(CONTROL_PORT);
	drone.addr_len = sizeof(drone.addr);

	drone.sockfd = socket(MYDOMAIN,TYPE,PROTOCOL);
	res =  bind(drone.sockfd, (struct sockaddr *) &drone.addr, drone.addr_len);
		if (res == -1){
			perror("Socket binding failed");
			exit(EXIT_FAILURE);
		}
	return EXIT_SUCCESS;
}

// Static function used in my_ReceiveControlCommand function

static inline int depacketizeControlCommand(unsigned char *cmd){
	unsigned char *ptr = cmd; // Why another pointer variable called ptr and why not use cmd. Good question!
	int return_flag;
	if (*ptr == 0xFF){
		ptr++;
		switch (*ptr){
			case 0xFE: // if control command
				myseqnum = (*(ptr+1)<<8) | *(ptr+2); // Compute sequence number. Can do something useful with it	
				ptr += 2; 
			 	myrefcommand.thrust = (*(ptr+1)<<8) | *(ptr+2); // In PPRZ units
				ptr += 2;
				myrefcommand.phi    = ((*(ptr+1)<<8) | *(ptr+2))/1000; // In radians - floating point
				ptr += 2;
				myrefcommand.theta  = ((*(ptr+1)<<8) | *(ptr+2))/1000; // In radians - floating point
				return_flag = EXIT_SUCCESS;				
				break;
			case 0xFF: //if autopilot_motors_on
				myseqnum = (*(ptr+1)<<8) | *(ptr+2); // Compute sequence number. Can do something useful with it	
				ptr += 2;
				if(*(ptr+1) == 0){autopilot_motors_on = 0;}
				else if(*(ptr+1) == 255){autopilot_motors_on = 1;}
				return_flag = EXIT_SUCCESS;
				break;
			default: return_flag = EXIT_FAILURE;
				break;
		}
	}
	else{
		return_flag = EXIT_FAILURE;
	}
	return return_flag;
}


int my_ReceiveControlCommand(void){
	char n = 0;
	unsigned char ControlCommand[10]; // 10 is arbitrary. Dirty implementation
	int return_flag = 0;
	printf("Blocked\n");
	n = recvfrom(drone.sockfd, ControlCommand, 10,0, (struct sockaddr *)&laptop.addr, &laptop.addr_len);
	if (n < 0){
		perror("Could not receive control command\n");
		exit(EXIT_FAILURE);
	}
	//printf("%d %d %d %d %d %d %d %d\n", n, ControlCommand[0], ControlCommand[1], ControlCommand[2], ControlCommand[3], ControlCommand[4], ControlCommand[5], ControlCommand[6]);
	return_flag = depacketizeControlCommand(ControlCommand);
        return return_flag;
}


int my_close_socket(void){
	char res;
	res = close(drone.sockfd);
	if(res == -1){
		perror("Error Closing Socket");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
