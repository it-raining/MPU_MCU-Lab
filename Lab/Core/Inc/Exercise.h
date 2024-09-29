/*
 * Exercise.h
 *
 *  Created on: Sep 6, 2024
 *      Author: HP
 */

#ifndef INC_EXERCISE_H_
#define INC_EXERCISE_H_

#include "main.h"
#define NUM_0   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin)
#define NUM_1   (SEG_1_Pin | SEG_2_Pin)
#define NUM_2   (SEG_0_Pin | SEG_1_Pin | SEG_3_Pin | SEG_4_Pin | SEG_6_Pin)
#define NUM_3   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_6_Pin)
#define NUM_4   (SEG_1_Pin | SEG_2_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_5   (SEG_0_Pin | SEG_2_Pin | SEG_3_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_6   (SEG_0_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_7   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin)
#define NUM_8   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_9   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_5_Pin | SEG_6_Pin)
#define ALL_SEG (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin)
#define TIMER_CYCLE 10 //ms
typedef enum { RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED } STATE;


void Ex1_Init();
void Ex1_Run();

void Ex2_Init();
void Ex2_Run();

void Ex3_Init();
void Ex3_Run();

void Ex4_Init();
void Ex4_Run();

void Ex5_Init();
void Ex5_Run();

void Ex6_Init();
void Ex6_Run();

void Ex10_Init();
void Ex10_Run();



#endif /* INC_EXERCISE_H_ */
