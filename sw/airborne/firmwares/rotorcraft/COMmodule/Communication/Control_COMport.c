/*
 * Control_COMport.c
 *
 *  Created on: Feb 27, 2015
 *      Author: praveen
 */

#include "Control_COMport.h"
//#include "../parameters.h"
#include "firmwares/rotorcraft/autopilot.h" //for autopilot_motors_on
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Global Variables
mysocket_t laptop_control, drone_control;
#ifdef USE_MYTELEMETRY
mysocket_t laptop_telemetry, drone_telemetry;
#endif
myrefcommand_t myrefcommand = {.thrust = 0, .phi = 0, .theta = 0, .psi = 0};

unsigned int myseqnum = 0;

//Function definition
int my_init_socket(void){
	char res;
	laptop_control.addr.sin_family = MYDOMAIN;
	inet_aton(LAPTOP_IP, &laptop_control.addr.sin_addr);
	laptop_control.addr.sin_port = htons(CONTROL_PORT);
	laptop_control.addr_len = sizeof(laptop_control.addr);

	drone_control.addr.sin_family = MYDOMAIN;
	inet_aton(DRONE_IP, &drone_control.addr.sin_addr);
	drone_control.addr.sin_port = htons(CONTROL_PORT);
	drone_control.addr_len = sizeof(drone_control.addr);

	drone_control.sockfd = socket(MYDOMAIN,TYPE,PROTOCOL);
	res =  bind(drone_control.sockfd, (struct sockaddr *) &drone_control.addr, drone_control.addr_len);
		if (res == -1){
			perror("Control Socket binding failed");
			exit(EXIT_FAILURE);
		}

#ifdef USE_MYTELEMETRY
	laptop_telemetry.addr.sin_family = MYDOMAIN;
	inet_aton(LAPTOP_IP, &laptop_telemetry.addr.sin_addr);
	laptop_telemetry.addr.sin_port = htons(TELEMETRY_PORT);
	laptop_telemetry.addr_len = sizeof(laptop_telemetry.addr);

	drone_telemetry.addr.sin_family = MYDOMAIN;
	inet_aton(DRONE_IP, &drone_telemetry.addr.sin_addr);
	drone_telemetry.addr.sin_port = htons(TELEMETRY_PORT);
	drone_telemetry.addr_len = sizeof(drone_telemetry.addr);

	drone_telemetry.sockfd = socket(MYDOMAIN,TYPE,PROTOCOL);
	res =  bind(drone_telemetry.sockfd, (struct sockaddr *) &drone_telemetry.addr, drone_telemetry.addr_len);
		if (res == -1){
			perror("Telemetry Socket binding failed");
			exit(EXIT_FAILURE);
		}

#endif
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
				myrefcommand.phi    = ((int16_t)(*(ptr+1)<<8) | *(ptr+2))/1000.0; // In radians - floating point
				ptr += 2;
				myrefcommand.theta  = ((int16_t)(*(ptr+1)<<8) | *(ptr+2))/1000.0; // In radians - floating point
				ptr += 2;
				myrefcommand.psi    = ((int16_t)(*(ptr+1)<<8) | *(ptr+2)); // optitrack heading command
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
	unsigned char ControlCommand[12]; // 12 is MAX_CMD_SIZE. Dirty implementation
	int return_flag = 0;
	printf("Blocked\n");
	n = recvfrom(drone_control.sockfd, ControlCommand, 12,0, (struct sockaddr *)&laptop_control.addr, &laptop_control.addr_len);
	if (n < 0){
		perror("Could not receive control command\n");
		exit(EXIT_FAILURE);
	}
	return_flag = depacketizeControlCommand(ControlCommand);
        return return_flag;
}

#ifdef USE_MYTELEMETRY
int my_SendPacket(char *packet, uint16_t numBytes){
	char n;
	unsigned char tempbuf[numBytes];
	memcpy(tempbuf, packet, numBytes);
	n = sendto(drone_telemetry.sockfd, packet, numBytes,0, (struct sockaddr *)&laptop_telemetry.addr, laptop_telemetry.addr_len);
	if (n < 0){
		perror("Could not send control command\n");
		exit(EXIT_FAILURE);
	}
	return n;
}
#endif
int my_close_socket(void){
	char res;
	res = close(drone_control.sockfd);
	if(res == -1){
		perror("Error Closing Socket");
		exit(EXIT_FAILURE);
	}
#ifdef USE_MYTELEMETRY
	res = close(drone_telemetry.sockfd);
	if(res == -1){
		perror("Error Closing Socket");
		exit(EXIT_FAILURE);
	}
#endif
	return EXIT_SUCCESS;
}
