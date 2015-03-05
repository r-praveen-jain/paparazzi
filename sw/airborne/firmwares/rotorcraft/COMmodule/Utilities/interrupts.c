/*
 * interrupts.c
 *
 *  Created on: Feb 27, 2015
 *      Author: praveen
 */

#include "interrupts.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int register_interrupt(int sig, void (*signal_handler)()){
	signal(sig, signal_handler);
	return EXIT_SUCCESS;
}

int clear_interrupt(int sig){
	signal(sig, SIG_IGN);
	return EXIT_SUCCESS;
}



