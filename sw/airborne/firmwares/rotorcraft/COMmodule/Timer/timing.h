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
extern struct timespec mydelay;
extern bool event_flag;

int my_init_timer(void);
int my_set_timer(void);
int my_delay_ns(long long nanosec);
int my_close_timer(void);

#endif /* TIMING_H_ */
