/*
 * parameters.h
 *
 *  Created on: Feb 27, 2015
 *      Author: praveen
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_


// Defines for UDP Communication with the Drone
#define MAIN_FREQ 10
#ifndef DRONE_IP
#define DRONE_IP 	"192.168.1.1"		// IP Address of the Drone
#endif

#ifndef LAPTOP_IP
#define LAPTOP_IP 	"192.168.1.2"
#endif
#define USE_MYTELEMETRY				// Comment this line to remove the custom telemetry

#define CONTROL_PORT	5555			// Port number for control commands
#define TELEMETRY_PORT  5556


// Defines related to the depacketization of control commands
#define FMAX				  8	// Maximum Thrust  = 8 N
#define FMIN				  0.4	// Minimum Thrust = 0.4 N

#define PHI_MIN				-50     // Minimum roll in degrees
#define PHI_MAX				 50     // Maximum roll in degrees

#define THETA_MIN			-50     // Minimum roll in degrees
#define THETA_MAX			 50     // Maximum roll in degrees

#define PSI_MIN				-50     // Minimum roll in degrees
#define PSI_MAX				 50     // Maximum roll in degrees
#define PSI_REF				  0	// Set reference yaw to zero

#define MAX_CMD_SIZE		         10
#define MAX_CMD				200

#define MY_RAD2DEG(x)	        	((x)*180/3.14159)
#define MY_DEG2RAD(x)			((x)*3.14159/180)


// Polynomial coefficients for conversion from thrust to PPRZ units
#define P3		 -71.2000
#define P2		1751.0000
#define P1		-497.5000

#endif /* PARAMETERS_H_ */
