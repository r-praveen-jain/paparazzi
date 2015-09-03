/*
 * parameters.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Praveen Jain (r.praveen.jain@gmail.com)
 * Description: All the defines related to execution of external controller are defined.
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_


// Defines for UDP Communication with the Drone

#ifndef DRONE_IP
#define DRONE_IP 	"192.168.1.1"		// IP Address of the Drone
#endif

#ifndef LAPTOP_IP
#define LAPTOP_IP 	"192.168.1.2"		// IP Address of the External computer/laptop (change accordingly)
#endif

#define USE_MYTELEMETRY					// Comment this line to remove the custom telemetry (not recommended)

#define CONTROL_PORT	5555			// Port number for receiving control commands
#define TELEMETRY_PORT  5556			// Port number for sending telemetry data

#define MAX_CMD_SIZE		12			// TODO: Check the actual value of the number
#define MAX_CMD				200			// TODO: Remove if not needed

#define MY_RAD2DEG(x)	      	((x)*180/3.14159)
#define MY_DEG2RAD(x)			((x)*3.14159/180)

// TODO: Consider removing. Note: The following defines are not used, maybe is used in future experiments
// Defines related to the depacketization of control commands
#define FMAX				  8		// Maximum Thrust  = 8 N
#define FMIN				  0.4	// Minimum Thrust = 0.4 N

#define PHI_MIN				-5      // Minimum roll in degrees
#define PHI_MAX				 5      // Maximum roll in degrees

#define THETA_MIN			-5      // Minimum roll in degrees
#define THETA_MAX			 5      // Maximum roll in degrees

#define PSI_MIN				-5      // Minimum roll in degrees
#define PSI_MAX				 5      // Maximum roll in degrees
#define PSI_REF				 0	    // Set reference yaw to zero

// TODO: Consider removing if not needed
// Polynomial coefficients for conversion from thrust to PPRZ units
#define P3		 -71.2000
#define P2		1751.0000
#define P1		-497.5000

#endif /* PARAMETERS_H_ */
