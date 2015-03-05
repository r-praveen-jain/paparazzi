/*
 * kbhit.h
 *
 *  Created on: Jan 10, 2015
 *      Author: praveen
 */

#ifndef KBHIT_H_
#define KBHIT_H_

#include <sys/select.h>
#include <termios.h>

void   init_keyboard(void);
void   close_keyboard(void);
int    kbhit(void);
int    readchar(void);


#endif /* KBHIT_H_ */
