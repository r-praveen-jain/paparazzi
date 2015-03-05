/*
 * timing.c
 *
 *  Created on: Feb 27, 2015
 *      Author: Praveen Jain
 */

#include "timing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../parameters.h"

struct itimerval main_timer;
struct timespec delay;

int init_timer(){
	long long freq_microsec = (1000000/MAIN_FREQ);
	// Timer structure for executing loop at MAIN_FREQ Hz
	main_timer.it_value.tv_sec     =  freq_microsec / 1000000;
	main_timer.it_value.tv_usec    =  freq_microsec;
	main_timer.it_interval.tv_sec  =  main_timer.it_value.tv_sec;
	main_timer.it_interval.tv_usec =  main_timer.it_value.tv_usec;
	printf("Timer initialized\n");
	return EXIT_SUCCESS;
}

int set_timer(){
	char res;
	printf("Setting Timer\n");
	res = setitimer(ITIMER_REAL, &main_timer, NULL);
		if(res != 0) {
			perror("Failed to set timer");
			exit(EXIT_FAILURE);
		}
	printf("Timer Set! \n");
	return EXIT_SUCCESS;
}


int delay_ns(long long nanosec){
	char res;
	delay.tv_sec = 0;
	delay.tv_nsec = nanosec;
	res = nanosleep(&delay,NULL);
	if(res == -1){
		perror("Delay interrupted");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

int close_timer(){
	main_timer.it_value.tv_sec     =  0;
	main_timer.it_value.tv_usec    =  0;
	main_timer.it_interval.tv_sec  =  main_timer.it_value.tv_sec;
	main_timer.it_interval.tv_usec =  main_timer.it_value.tv_usec;
	printf("Timer Deleted\n");
	return EXIT_SUCCESS;
}
