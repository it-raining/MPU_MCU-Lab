/*
 * Exercises.h
 *
 *  Created on: Sep 7, 2024
 *      Author: HP
 */

#ifndef INC_EXERCISES_H_
#define INC_EXERCISES_H_

#include "main.h"
#define NUM_0   (SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin)
#define NUM_1   (SEG1_Pin | SEG2_Pin)
#define NUM_2   (SEG0_Pin | SEG1_Pin | SEG3_Pin | SEG4_Pin | SEG6_Pin)
#define NUM_3   (SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG6_Pin)
#define NUM_4   (SEG1_Pin | SEG2_Pin | SEG5_Pin | SEG6_Pin)
#define NUM_5   (SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin | SEG6_Pin)
#define NUM_6   (SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin)
#define NUM_7   (SEG0_Pin | SEG1_Pin | SEG2_Pin)
#define NUM_8   (SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin)
#define NUM_9   (SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin | SEG6_Pin)
#define ALL_SEG (SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin)
#define ALL_ROW (ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin)
#define ALL_EN  (ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin)
#define TIMER_CYCLE 10 //ms

typedef struct {
  int flag;
  uint16_t counter;
} UserTimer;
void timerRun();

void Ex1_Init();
void Ex1_Run(); // Present the source code in the HAL_TIM_PeriodElapsedCallback

void Ex2_Init();
void Ex2_Run(); // Present the source code in the HAL_TIM_PeriodElapsedCallback

void Ex3_Init();
void Ex3_Run(); // Present the source code in the HAL_TIM_PeriodElapsedCallback

void Ex4_Init();
void Ex4_Run(); // Present the source code in the HAL_TIM_PeriodElapsedCallback

void Ex5_Init();
void Ex5_Run();

void Ex7_Init();
void Ex7_Run();
void Ex7_TI();

void Ex8_Init();
void Ex8_Run();
void Ex8_TI();

void Ex9_Init();
void Ex9_Run();

void Ex10_Init();
void Ex10_Run();

#endif /* INC_EXERCISES_H_ */
