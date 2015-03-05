/*
 * interrupts.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Praveen jain
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

//typedef void (*sighandler_t)(int);

int register_interrupt(int sig, void (*signal_handler)());
int clear_interrupt(int sig);


#endif /* INTERRUPTS_H_ */
