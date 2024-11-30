/*
 * global.h
 *
 *  Created on: Nov 25, 2024
 *      Author: HP
 */
#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
#define ONE_SEC 1000
typedef enum {
	INIT, AUTO, MODIFY_RED, MODIFY_AMBER, MODIFY_GREEN
} MODE;
typedef enum {
	RED, GREEN, AMBER
} STATE;

extern MODE mode;
extern STATE line_1, line_2;
extern uint32_t state_ID;
#endif /* INC_GLOBAL_H_ */
