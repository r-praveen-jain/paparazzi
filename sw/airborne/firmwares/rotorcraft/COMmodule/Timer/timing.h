/*
 * timing.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Praveen Jain
 */

#ifndef TIMING_H_
#define TIMING_H_

#include <sys/time.h>
#include <stdbool.h>
extern struct itimerval main_timer;
extern struct timespec delay;
extern bool event_flag;

int init_timer();
int set_timer();
int delay_ns(long long nanosec);
int close_timer();

#endif /* TIMING_H_ */
