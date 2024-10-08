/*
 * swTimer.h
 *
 *  Created on: Oct 6, 2024
 *      Author: HP
 */

#ifndef INC_SWTIMER_H_
#define INC_SWTIMER_H_

#include "main.h"
#define NO_OF_TIMER 	10
#define TIMER_CYCLE 	10 //ms
#define ONE_SEC			1000 //ms
#define SCANNING_FREQ 	1 //Hz
#define BLINKY_FREQ 	2 //Hz
// Timer mapping
#define COUNTDOWN 	0
#define SCANNING	1
#define BLINKY 		2
typedef struct {
  uint8_t flag;
  uint16_t counter;
} UserTimer;

void setTimer(int idx, uint16_t duration);
void timerRun(void);
int is_avail(int idx);
#endif /* INC_SWTIMER_H_ */
