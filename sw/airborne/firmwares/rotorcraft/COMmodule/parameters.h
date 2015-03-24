/*
 * parameters.h
 *
 *  Created on: Feb 27, 2015
 *      Author: praveen
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

// Defines related to the controller
//#define DEBUG_MODE
// Defines for UDP Communication with the Drone
#define MAIN_FREQ				10					// Frequency in Hertz

#define LOCALHOST				"127.0.0.1"

#ifdef DEBUG_MODE
#define DRONE_IP	LOCALHOST
#define LAPTOP_IP	LOCALHOST
#else
#define DRONE_IP				"192.168.1.1"		// IP Address of the Drone
#define LAPTOP_IP				"192.168.1.2"
#endif

#define CONTROL_PORT			5555				// Port number for control commands


// Defines related to the depacketization of control commands
#define FMAX				  8	// Maximum Thrust  = 8 N
#define FMIN				  0.4	// Minimum Thrust = 0.4 N

#define PHI_MIN				-45     // Minimum roll in degrees
#define PHI_MAX				 45     // Maximum roll in degrees

#define THETA_MIN			-45     // Minimum roll in degrees
#define THETA_MAX			 45     // Maximum roll in degrees

#define PSI_MIN				-10     // Minimum roll in degrees
#define PSI_MAX				 10     // Maximum roll in degrees
#define PSI_REF				  0	// Set reference yaw to zero

#define MAX_CMD_SIZE		          7
#define MAX_CMD				200

#define MY_RAD2DEG(x)	        	((x)*180/3.14159)
#define MY_DEG2RAD(x)			((x)*3.14159/180)


#endif /* PARAMETERS_H_ */
