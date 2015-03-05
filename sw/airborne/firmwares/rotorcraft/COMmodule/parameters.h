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
#define LAPTOP_IP				"192.168.209.30"
#endif

#define CONTROL_PORT			5555				// Port number for control commands

#endif /* PARAMETERS_H_ */
