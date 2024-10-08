/*
 * global.h
 *
 *  Created on: Oct 4, 2024
 *      Author: HP
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#define NO_OF_7SEG 4 //fixed

typedef enum {
	INIT, AUTO, MODIFY
} MODE;
typedef enum {
	RED, GREEN, AMBER
} STATE;
extern MODE mode;
extern uint8_t led_buffer[NO_OF_7SEG];
extern uint8_t red_light;
extern uint8_t amber_light;
extern uint8_t green_light;
extern STATE line_1, line_2;

#endif /* INC_GLOBAL_H_ */
